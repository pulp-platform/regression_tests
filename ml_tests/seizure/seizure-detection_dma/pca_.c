/*
 * pca_.c
 *
 *  Created on: 20 gen 2016
 *      Author: Fabio
 */

#include "hwPerf.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "pca_.h"
#include "dat.h"
#include <omp.h>
#include "init.h"
#include "math_fns.h"
#include "pulp.h"

#define SIGN(a, b) ((b) >= 0.0 ? fAbs(a) : -fAbs(a))
#define MAX(x,y) ((x)>(y)?(x):(y))


 /*set the number of cores to execute the application*/

 int PCA(int lunghezza_finestra, int numero_canali, float output[][256]){ 
         
         float p[channels+1];
         float *rv1;
	 #if HWPERFMALLOC
	 perf_start();
         #endif
	 float *a = plp_alloc_l1((int)(channels*channels*sizeof(float)));
         float *v = plp_alloc_l1((int)(channels*channels*sizeof(float)));
	 //printf("malloc %x %x \n",a,v);
	 #if HWPERFMALLOC
	 perf_stop();
	 printf("STOP alloc\n"); perf_print_all();
         #endif
         float w[channels]; //eigenvalues
         float explained[channels];
         float anorm;
         int i, k; 
         rv1=p;

         #if HWPERF_FUNC
	 perf_stop();
	 printf("START PCA\n"); perf_print_all();
	 perf_start();
         #endif

         mean_covariance(datiInput2, a);  //compute mean value for all channels and substract mean value from datas 
 
         #if HWPERF_FUNC
	 perf_stop();
	 printf("COVARIANCE\n"); perf_print_all();
	 perf_start();
         #endif

         anorm=householder(a, rv1, w);  //Householder reduction to bidiagonal form
       
         #if HWPERF_FUNC
	 perf_stop();
	 printf("HOUSEHOLDER\n"); perf_print_all();
	 perf_start();
         #endif

         accumulate(v, a, rv1);  //accumulate the right-hand transformation
   
         #if HWPERF_FUNC
	 perf_stop();
	 printf("ACCUMULATE\n"); perf_print_all();
	 perf_start();
         #endif

         diagonalize(w, rv1, v, anorm);

         #if HWPERF_FUNC
	 perf_stop();
	 printf("DIAGONALIZE\n"); perf_print_all();
	 perf_start();
         #endif

         /*compute the k components*/
         
         float totalvar=0.0f;
         float vartotspiegata=0.0f;
         
         
         for(i=0; i<channels; i++)
                 
                 totalvar=totalvar+w[i]; 
         
         
         
         
         for(i=0; i<channels; i++)
                 
	   explained[i]=fDiv((100.0f*w[channels-i-1]),totalvar);
         
         
         
         
         i=channels;
         
         while(vartotspiegata<90){
                 
                 i=i-1;
                 vartotspiegata=vartotspiegata+explained[i];
                 
         }
         
         if(vartotspiegata>90){
                 
                 i=i+1;
                 vartotspiegata=vartotspiegata-explained[i];
                 
         }
         #if HWPERF
	 perf_stop();
	 #endif
         printf("\nexplained variance:\n%d\ncomponents: %d\n", (int)vartotspiegata,(channels-i));
         k=channels-i;
         printf("Number of components we consider: %d\n", k);
         #if HWPERF
	 perf_start();
	 #endif
         //CALCOLO K PC
         
         //k_comp=k;
         int k_comp=9;
      
         PC(datiInput2, output, v);

         #if HWPERF_FUNC
	 perf_stop();
	 printf("END PC\n"); perf_print_all();
	 perf_start();
         #endif

 	 #if HWPERFFREE
	 perf_start();
         #endif

	 // free L1 memory
	 l1free(v);
	 l1free(a);
	 v = NULL;
	 a = NULL;

         #if HWPERFFREE
	 perf_stop();
	 printf("FREE\n"); perf_print_all();
         #endif

         return k_comp;
         
 }

/*compute mean value for al channels and substract mean value from datas*/
void mean_covariance(float datiInput[][256], float a[channels*channels]){
        
        float *datainput;
	#if HWPERFMALLOC
	perf_start();
        #endif
	datainput = plp_alloc_l1((int)(window*channels*sizeof(float)));
	//printf("malloc %x \n",datainput);
        #if HWPERFMALLOC
	perf_stop();
	printf("STOP alloc\n"); perf_print_all();
        #endif
	int dma_id0 = memcpy_async(datainput, datiInput, window*channels*4);
	memcpy_wait(dma_id0);
        int i, j, k;
        #pragma omp parallel default(none) private( i, k, j) shared(a, datainput) num_threads(CORE)
        {
                
                float temp=0.0f;
                #pragma omp for 
                
                for (j = 0; j < channels; j++){ 
                        
                        
                        float mean = 0.0f;
                        
                        for (i = 0; i < window; i++){
                                mean = mean + datainput[j*window+i];
                        }
                        mean = fDiv(mean,window);
                        for (i = 0; i < window; i++){
                                datainput[j*window+i] -= mean;
                        }
                }
               
                #pragma omp barrier

                /*compute covariance matrix*/   
                #pragma omp for collapse(2)
                for(i=0; i < channels; i++){
                        for(j=0; j < channels; j++){
                                
                                
                                for(k=0; k < window; k++){
                                        temp+=datainput[i*window+k]*datainput[j*window+k];
                                }
                                a[i*channels+j]=temp; 
                                temp=0.0f; 
                        }
                }
                
        }//omp

	// copy data back..
	int dma_id1 = memcpy_async(datiInput,datainput, window*channels*4);
	memcpy_wait(dma_id1);
        

#if HWPERFFREE
	perf_start();
#endif
	l1free(datainput);
	datainput = NULL;
#if HWPERFFREE
	perf_stop();
	printf("FREE\n"); perf_print_all();
#endif

}

/* Householder reduction to bidiagonal form */
float householder(float a[channels*channels], float rv1[channels], float w[channels]){
        
        int i, its, j, jj, k, l, nm;
        float c, f, h, s, x, y, z, flag;
        float anorm = 0.0f, g = 0.0f;
        #pragma omp parallel default(none) private(s, g, k) shared(f, rv1, i, l, a, h, w, anorm) num_threads(CORE)       
        {
               
                for (i = 0; i < channels; i++)
                {
                         
                        // left-hand reduction 
                        #pragma omp master
                        {
                                l = i + 1;
                                rv1[i] = g;
                                g = 0.0f;
                                s = 0.0f;
                        }//master
                       
                        #pragma omp barrier                                                                                                                                                                     //#pragma omp barrier
                        
                        if (i < channels)
                        {
                                #pragma omp master
                                {
                                        
                                        for (k = i; k < channels; k++)
                                        {
                                                s += (a[k*channels+i] * a[k*channels+i]);
                                        }
                                            
                                        f = a[i*channels+i];
                                        g = -SIGN(fSqrt(s), f); 
                                        h = f * g - s;
                                        a[i*channels+i] = (f - g);
                                
                                }//master
                               

                                                      
                                #pragma omp barrier                                             
                                if (i != channels - 1)
                                {                     
                                        #pragma omp for private(f)                            
                                        for (j = l; j < channels; j++) 
                                        {       
                                                s = 0.0f;
                                                for ( k = i; k < channels; k++)
                                                         s += (a[k*channels+i] * a[k*channels+j]);
                                                                                
                                                f = fDiv(s, h);
                                                                                
                                                for (k = i; k < channels; k++)
                                                        a[k*channels+j]+= (f * a[k*channels+i]);
                                        }
                                }
                                   
                        }
                        
                       
                        #pragma omp master
                        {
                              
                                w[i] = g; 
                                g = 0.0f;
                                s = 0.0f;
                             
                        }//master
                       
                        
                        if (i < channels && i != channels - 1)
                        {
                    
                                        #pragma omp master
                                        {
                                                                                
                                                        for (k = l; k < channels; k++)
                                                        {
                                                                s += (a[i*channels+k] * a[i*channels+k]);
                                                        }
                                                       
                                                        f = a[i*channels+l];
                                                        g = -SIGN(fSqrt(s), f);
                                                        h = f * g - s;
                                                        h=fDiv(1.0f, h); 
                                                        a[i*channels+l] = (f - g);
                                                                         
                                                        for (k = l; k < channels; k++)
                                                                rv1[k] = a[i*channels+k] * h;
                                        }//master 
                                       
                                        #pragma omp barrier
                                        if (i !=channels - 1)
                                        {
                                                              
                                                #pragma omp for                        
                                                for (j = l; j < channels; j++)
                                                {
                                                        s = 0.0f;
                                                                        
                                                        for ( k = l; k < channels; k++)
                                                                s += (a[j*channels+k] * a[i*channels+k]);
                                                                        
                                                                        
                                                         for (k = l; k < channels; k++)
                                                                 a[j*channels+k]+= (s * rv1[k]);
                                                                        
                                                 }
                                         }

                        }

                        #pragma omp master
                        {
                                anorm = MAX(anorm, (fAbs(w[i]) + fAbs(rv1[i])));  
                        }     

                }
                
        }//omp

        return anorm;
}


/* accumulate the right-hand transformation */
void accumulate(float v[channels*channels], float a[channels*channels], float rv1[channels]){
       
       int i, j, k, l;
       float s;
       float g = 0.0f;
       #pragma omp parallel default(none) shared( a, v, g, l, rv1, i, j) private(k, s) num_threads(CORE) 
        {
                
                for (i = channels - 1; i >= 0; i--)
                {
                        if (i <channels - 1)
                        {
                              
                                 if (g)
                                 {  

                                        #pragma omp for //nowait 
                                        for (j = l; j < channels; j++)
					  v[j*channels+i] = fDiv(fDiv(a[i*channels+j], a[i*channels+l]), g); 
                                        
                                        
                                        /* double division to avoid underflow */

                                        #pragma omp for //nowait
                                        for (j = l; j < channels; j++)
                                        {
                                                s = 0.0f;
                                                
                                                for ( k = l; k < channels; k++)
                                                        s += (a[i*channels+k] * v[k*channels+j]);
                                                
                                                
                                                for (k = l; k < channels; k++){
                                                        v[k*channels+j] += (s * v[k*channels+i]);
                                                }
                                        }
                                }

                                        
                                        #pragma omp master
                                        {
                                        for (j = l; j < channels; j++)
                                                v[i*channels+j] = v[j*channels+i] = 0.0f;
                                        }
                                        #pragma omp barrier
                         }
                                         
                        #pragma omp master
                        {
                                v[i*channels+i] = 1.0f;
                                g = rv1[i];
                                l = i;
                        }//master
                        #pragma omp barrier
                        
                 }
                 
        }//omp
     
  
}


/* diagonalize the bidiagonal form */


static float PYTHAG(float a, float b)
{
        float at = fAbs(a), bt = fAbs(b), ct, result;
        
        if (at > bt)       { ct = fDiv(bt, at); result = at * fSqrt(1.0f + ct * ct); }//printf("%d\t",(int)result);}
        else if (bt > 0.0f) { ct = fDiv(at , bt); result = bt * fSqrt(1.0f + ct * ct); }//printf("%d\t",(int)result);}
        else result = 0.0f;
        
        return(result);
        
}

void diagonalize(float w[channels], float rv1[channels], float v[channels*channels], float anorm){
        
        int i, its, j, jj, k, l, nm;
        float c, f, h, s, x, y, z;
        float g = 0.0f;
        #pragma omp parallel default(none) private( g, h, f, j, y, z, x) shared(nm, k, its, l, rv1,  w, c, s, i, v, anorm) num_threads(CORE)//private(i,jj,j,y,z,x,h,g,s,c,f) shared(nm,rv1,w,v,m,n,a,flag) num_threads(CORE)// 
        {
                
                for (k =channels - 1; k >= 0; k--)
                {  

                        /* loop over singular values */
                        for (its = 0; its < 30; its++)
                        {  
                                /* loop over allowed iterations */
                               
                                #pragma omp master
                                {               
                                        
                                        for (l = k; l > 0; l--)
                                        {  
                                                nm = l - 1;
                                                if (fAbs(rv1[l]) + anorm == anorm || fAbs(w[nm]) + anorm == anorm)
                                                        break;
                                        }
                                }//master
                                
                                #pragma omp barrier
      
                                if (l == k)
                                {                  
                                        /* convergence */
                                        break;
                                        
                                }
                                #pragma omp barrier
                                #pragma omp master
                                {
                                        /* shift from bottom 2 x 2 minor */
                                        z = w[k];
                                        y = w[nm];
					x = w[l];
                                        nm = k - 1;     
                                        g = rv1[nm];
                                        h = rv1[k];
                                        
                                        f = fDiv(((y - z) * (y + z) + (g - h) * (g + h)), (2.0f * h * y));
                                        g = PYTHAG(f, 1.0f); 
                                        f = fDiv(((x - z) * (x + z) + h * (fDiv(y, (f + SIGN(g, f))) - h)), x); 
                                        
                                        /* next QR transformation */
                                        c = 1.0f;
					s = 1.0f;
                                }//master
                                #pragma omp barrier     
                                
                                for (j = l; j <= nm; j++)
                                {
                                        
                                        #pragma omp master
                                        {                                       
                                                
                                                i = j + 1;
                                                g = rv1[i];
                                                y = w[i];
                                                h = s * g;
                                                g = c * g;
                                                z = PYTHAG(f, h);
                                                rv1[j] = z;
                                                c = fDiv(f, z);
                                                s = fDiv(h, z);
                                                f = x * c + g * s;
                                                g = g * c - x * s;
                                                h = y * s;
                                                y = y * c;
                                                
                                                
                                        }//master
                                        #pragma omp barrier
                                        
                                        #pragma omp for //nowait
                                        for (jj = 0; jj < channels; jj++)
                                        {
                                                x = v[jj*channels+j];
                                                z = v[jj*channels+i];
                                                v[jj*channels+j] = (x * c + z * s);
                                                v[jj*channels+i] = (z * c - x * s);
                                        }
                                        
                                        #pragma omp master
                                        {
                                                z = PYTHAG(f, h);
                                                
                                                w[j] = z;
                                                
                                                if (z)
                                                {
						  z = fDiv(1.0f, z);
                                                        c = f * z;
                                                        s = h * z;
                                                        
                                                }
                                                
                                                f = (c * g) + (s * y);
                                                x = (c * y) - (s * g);
                                        }//master
                                        #pragma omp barrier
                                        
                                }
                                
                                
                                #pragma omp master
                                {
                                        rv1[l] = 0.0f;
                                        rv1[k] = f;
                                        w[k] = x; 
                                }               
                                
                        }
                        #pragma omp barrier
                }      
                
        }//omp
        
}

//CALCOLO K PC
void PC(float datiInput[][256], float datioutput[][256], float v[channels*channels]){
        
        int i, k, k2;
        int k_comp=9;
        float temp;
	
	float *datainput;
	#if HWPERFMALLOC
	perf_start();
        #endif
	datainput = plp_alloc_l1((int)(window*channels*sizeof(float)));
	//printf("malloc %x \n",datainput);
        #if HWPERFMALLOC
	perf_stop();
	printf("STOP alloc\n"); perf_print_all();
	#endif
	int dma_id0 = memcpy_async(datainput, datiInput, window*channels*4);
	memcpy_wait(dma_id0);
        
        #pragma omp parallel default(none) private(k,k2, temp) shared(datainput, v, datioutput, k_comp) num_threads(CORE) 
        {
                temp=0.0f;
                #pragma omp barrier
                #pragma omp for 
                for (i = 0; i < window; i++) {
                        
                        for(k=0; k < k_comp; k++) {
                                
                                for (k2 = 0; k2 < channels; k2++) 
                                {                                                                                                                                                               
                                        
                                        temp+= datainput[k2*window+i] * v[k2*channels+k];
                                        
                                }
                                datioutput[k][i]=temp; 
                                temp=0.0f;                      
                        } 
                }
                
        }//omp
#if HWPERFFREE
	perf_start();
#endif
        l1free(datainput);
	datainput = NULL;
#if HWPERFFREE
	perf_stop();
	printf("FREE\n"); perf_print_all();
#endif
}
