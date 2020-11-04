#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <locale.h>
#include <math.h>
#include "modelSVM.h"
#include "libSVM_predict.h"
#include "libSVM_load_model.h"
#include <omp.h>
#include "math_fns.h"
#include "pulp.h"

#include "init.h"

PULP_L1_DATA struct svm_node *x;
PULP_L1_DATA struct svm_model *model;

void exit_input_error(int line_num)
{
        printf("Wrong input format at line %d\n", line_num);
        return;
}

void exit_with_help()
{
        printf(
                "Usage: svm-predict [options] test_file model_file output_file\n"
                "options:\n"
                "-b probability_estimates: whether to predict probability estimates, 0 or 1 (default 0); for one-class SVM only 0 is supported\n"
                "-q : quiet mode (no outputs)\n"
        );
        return;
}


void svm_free_model_content(svm_model* model_ptr)
{
        int i = 0;
        if(model_ptr->free_sv && model_ptr->l > 0 && model_ptr->SV != NULL)
                free((void *)(model_ptr->SV[0]));
        if(model_ptr->sv_coef)
        {
                for(i=0;i<model_ptr->nr_class-1;i++)
                        free(model_ptr->sv_coef[i]);
        }
        
        free(model_ptr->SV);
        model_ptr->SV = NULL;
        
        free(model_ptr->sv_coef);
        model_ptr->sv_coef = NULL;
        
        free(model_ptr->rho);
        model_ptr->rho = NULL;
        
        free(model_ptr->label);
        model_ptr->label= NULL;
        
        free(model_ptr->probA);
        model_ptr->probA = NULL;
        
        free(model_ptr->probB);
        model_ptr->probB= NULL;
        
        free(model_ptr->nSV);
        model_ptr->nSV = NULL;
}


void svm_free_and_destroy_model(svm_model** model_ptr_ptr)
{
        if(model_ptr_ptr != NULL && *model_ptr_ptr != NULL)
        {
                svm_free_model_content(*model_ptr_ptr);
                free(*model_ptr_ptr);
                *model_ptr_ptr = NULL;
        }
}

static inline float powi(float base, int times)
{
        float tmp = base, ret = 1.0;
        int t = 0;
        for(t=times; t>0; t/=2)
        {
                if(t%2==1) ret*=tmp;
                tmp = tmp * tmp;
        }
        return ret;
}


float dot(const svm_node *px, const svm_node *py)
{
        float sum = 0;
        while(px->index != -1 && py->index != -1)
        {
                if(px->index == py->index)
                {
                        sum += px->value * py->value;
                        ++px;
                        ++py;
                }
                else
                {
                        if(px->index > py->index)
                                ++py;
                        else
                                ++px;
                }                       
        }
        return sum;
}

float kernel_function(const svm_node *x, const svm_node *y, const svm_parameter param)
{
        /*
         *        switch(param.kernel_type)
         *        {
         *                case LINEAR:
         *                        return dot(x,y);
         *                case POLY:
         *                        return powi(param.gamma*dot(x,y)+param.coef0,param.degree);
         *                case RBF:
         *                {
         */
        float sum = 0;
	//	printf("gamma %d\n ", (int)(1000.0F*param.gamma);

        while(x->index != -1 && y->index !=-1)
        {
                if(x->index == y->index)
                {
                        float d = x->value - y->value;
                        sum += d*d;
                        ++x;
                        ++y; 
                }
                else
                {
                        if(x->index > y->index)
                        {       
                                sum += y->value * y->value;
                                ++y;
                        }
                        else
                        {
                                sum += x->value * x->value;
                                ++x;
                        }
                }
        }
        
        while(x->index != -1)
        {
                sum += x->value * x->value;
                ++x;
        }
        
        while(y->index != -1)
        {
                sum += y->value * y->value;
                ++y;
        }
#ifdef DEBUG
	//	perf_stop();
	printf("sum of kernel_function: %d\n", (int)sum);
	printf("gamma: %d\n", (int)(100.0F*param.gamma));
	printf("product: %d\n", (int)(100.0F*(-param.gamma*sum)));
	//	perf_start();
#endif
	float result_exp = fExp((float)(-param.gamma*sum));
	//printf("result_exp: %d\n", (int)(10000.0F *result_exp));
        return result_exp;
        /*
}
case SIGMOID:
        return tanh(param.gamma*dot(x,y)+param.coef0);
case PRECOMPUTED:  //x: test (validation), y: SV
        return x[(int)(y->value)].value;
default:
        return 0;  // Unreachable 
}
*/
}


float svm_predict_values(const svm_node *x, float* dec_values)
{
 
  int j;
  int i;
  int cont=0;
  int nr_class = model->nr_class;
  int l = model->l;
  int dim_feature = 36 ;
  svm_node SV[dim_feature + 1];
  svm_parameter _param = model->param;
  unsigned int stripe_size = (dim_feature + 1) * CORE ;
  
#if HWPERFMALLOC
  perf_start();
#endif
  float *sv_coef = plp_alloc_l1((int)(sizeof(float)*l));
  float *kvalue  = plp_alloc_l1((int)(sizeof(float)*l));
  float *data_buff[2]; 
  data_buff[0] = plp_alloc_l1(stripe_size*sizeof(float)) ;              // 1024 Byte
  data_buff[1] = plp_alloc_l1(stripe_size*sizeof(float)) ;              // 1024 Byte
#if HWPERFMALLOC
  perf_stop();
  //printf("STOP alloc\n"); perf_print_all();
#endif 
  float *buffer_in_dma = (float *) data_buff[0] ;
  float *buffer_out_dma = (float *) data_buff[2] ;
  float *ptr_data_model=data_model_l2; 
  float *buffer_in_compute ;
  int buffId = 0;
  int trans_id_load[2];
  int indx, indy, indz;
  int val=CORE;
  int flag = 0;
        
  int end=0;
  if (CORE == 8) end = 328;
  else if (CORE == 4) end = 320;
  else if (CORE == 2) end = 318;
  else if (CORE == 1) end = 310;
        
  
#pragma omp parallel default(none) private(i, j, SV) shared(dim_feature, end, trans_id_load, _param, ptr_data_model, val, l, data_buff, flag, buffId, buffer_in_dma, buffer_in_compute, sv_coef,data_model_l2, kvalue, x)  num_threads(CORE)
  {
                
#pragma omp barrier
    for (i=0; i < end; i+=CORE){
                        
#pragma omp master
      {
	buffer_in_compute = buffer_in_dma ;
                                
	// Double Buffer Switching
	if (buffId == 0){
	  buffId=1;
	  buffer_in_dma = data_buff[buffId] ; //printf("\nUSO DATA[1]\n");                               
	}else
	  {                
	    buffId=0;
	    buffer_in_dma = data_buff[buffId] ; //printf("\nUSO DATA[0]\n");
	  }
                                
	//Next Stripe DMA Load
	if(i < end - CORE){
                                        
	  if (CORE == 2) flag=2;
	  if(i == end - 2 * CORE)
	    val = 3 - flag;
	  else
	    val = CORE;
                                        
	  trans_id_load[!buffId] = memcpy_async(buffer_in_dma, (ptr_data_model + (dim_feature + 1) * i), val * (dim_feature + 1) * sizeof(float));
	  //sprintf("PROGRAMMING LOAD TRANSFER, status:%d, iter: %d\n" ,pulp_dma_status(pulp_dma_base()),i);
	}
                                
	//Wait Current Stripe Load
	if(i > CORE - 1) {
	  memcpy_wait(trans_id_load[buffId]);
	  //printf("DMA TRANFERS COMPLETE, status:%d, iter: %d\n\n" ,pulp_dma_status(pulp_dma_base()),i);
	}
      }//master
                        
      //COMPUTE 
      if(i > CORE - 1){
                                
#pragma omp master
	{
                                        
	  if (CORE == 2) flag=2;
	  if( i == end - CORE )
	    val = 3 - flag;
	  else
	    val = CORE;
	  //printf("val:%d\n", val);       
	}//master
                                
#pragma omp barrier

#pragma omp for 
	for(indx=0; indx < val; indx++){
	  //printf("\nval:%d\n", val);
	  sv_coef[(i-CORE)+indx] = buffer_in_compute[indx * (dim_feature + 1)]; //printf("%d\t", (int)sv_coef[(i-1)+indx]);  
	  for(j=1;j< (dim_feature + 1);j++){
	    SV[j-1].index = j;
	    SV[j-1].value = buffer_in_compute[j + indx * (dim_feature + 1)]; //float temp=SV[j-1].value*100;printf("%d\t", (int)temp );
	  }//printf("\n");
	  SV[dim_feature].index = -1;
	  SV[dim_feature].value = 0.0f;
                                        
	  kvalue[i - CORE + indx] = kernel_function(x, SV,_param); 
	}   
                                
      }
                        
    }
                
  }//omp
    
  int *start = malloc(sizeof(int)*nr_class);
  start[0] = 0;
  for(i=1;i<nr_class;i++)
    start[i] = start[i-1]+model->nSV[i-1];
        
  int *vote = malloc(sizeof(int)*nr_class);
  for(i=0;i<nr_class;i++)
    vote[i] = 0;
        
  int p=0;
  //      int j=0;
  float sum = 0.0f;
  //      #pragma omp parallel            
  //      {
  for(i=0;i<nr_class;i++)
    for(j=i+1;j<nr_class;j++)
      {
	sum = 0.0f;
	int si = start[i];
	int sj = start[j];
	int ci = model->nSV[i];
	int cj = model->nSV[j];
                        
	int k;
	float *coef1 = &sv_coef[j-1];
	float *coef2 = &sv_coef[i];
                        
	for(k=0;k<ci;k++)
	  sum += coef1[si+k] * kvalue[si+k];
                        
	for(k=0;k<cj;k++)
	  sum += coef2[sj+k] * kvalue[sj+k];
                        
	sum -= model->rho[p];
	dec_values[p] = sum;
                        
	if(dec_values[p] > 0.0f)
	  ++vote[i];
	else
	  ++vote[j];
	p++;
                        
                        
      }
                
  int vote_max_idx = 0;
  for(i=1;i<nr_class;i++)
    if(vote[i] > vote[vote_max_idx])
      vote_max_idx = i;
                        
  printf("\nRESULT:%d\n",model->label[vote_max_idx]);
                
  // free l1 memory
#if HWPERFFREE
  perf_start();
#endif
  l1free(data_buff[0]);
  l1free(vote);
  l1free(start);
  l1free(kvalue);
  l1free(sv_coef);
#if HWPERFFREE
  perf_stop();
  printf("FREE\n"); perf_print_all();
#endif
  return 0;
}


/*
//float svm_predict_values(const svm_model *model, const svm_node *x, float* dec_values)
float svm_predict_values(const svm_node *x, float* dec_values)
{
        
        int j;
        int i;
        
        int nr_class = model->nr_class;
        int l = model->l;
        svm_node SV[37];
        svm_parameter _param = model->param;
        #if HWPERFMALLOC
	perf_start();
        #endif
        float *sv_coef = plp_alloc_l1((int)(sizeof(float)*l));
	float *kvalue  = plp_alloc_l1((int)(sizeof(float)*l));
	float *data_model = plp_alloc_l1((int)(sizeof(float)*315*37));
	
	int dma_id0 = memcpy_async(data_model, data_model_l2, 315*37*4);
	memcpy_wait(dma_id0);
	
	//printf("malloc %x %x \n",sv_coef, kvalue);
        #if HWPERFMALLOC
	perf_stop();
	//printf("STOP alloc\n"); perf_print_all();
        #endif        
        #pragma omp parallel default(none) num_threads(CORE) shared(sv_coef,data_model_l2, kvalue, x, l, _param) private(j, SV)//private(j, i, SV)
        {
	
                #pragma omp barrier
	  
#pragma omp for //nowait 
                
                for(i=0; i < l; i++){
                        
		  //sv_coef[i]=data_model[i][0]; 
		  sv_coef[i]=data_model[i*36]; 
			//printf("sv coef: %d\n", (int) sv_coef[i]);
                        for(j=1;j<=36;j++){
                                SV[j-1].index = j;
				//SV[j-1].value = data_model[i][j]; 
                                SV[j-1].value = data_model[i*36+j]; 
				//printf("SV[%d]: %d\n", j, (int) SV[j-1].value);
                        }
                        SV[36].index = -1;
                        SV[36].value = 0.0f;
                        kvalue[i] = kernel_function(x, SV,_param); 
			//printf("kvalue %d \n", (int)(kvalue[i]));
                }
                
        }//omp
	l1free(data_model);
#ifdef DEBUG
	perf_stop();
	float sum_kvalue;
	sum_kvalue = 0.0F;
	for(int indk=0;indk<315;indk++){
	  sum_kvalue +=  100.0F*fAbs(kvalue[indk]);
	}
	//for(int indk=0;indk<36;indk++){
	//sum_kvalue +=  100.0F*fAbs(SV[indk].value);
	//}
	printf("sum of kvalue: %d\n", (int) sum_kvalue);
	perf_start();
#endif


        #if HWPERFMALLOC
	perf_start();
        #endif
        int *start = plp_alloc_l1((int)(sizeof(int)*nr_class));
        int *vote  = plp_alloc_l1((int)(sizeof(int)*nr_class));
	//printf("malloc %x %x\n",start, vote);
        #if HWPERFMALLOC
	perf_stop();
	printf("STOP alloc\n"); perf_print_all();
        #endif
        start[0] = 0;
        for(i=1;i<nr_class;i++)
                start[i] = start[i-1]+model->nSV[i-1];
        
        for(i=0;i<nr_class;i++)
                vote[i] = 0;
        
        int p=0;
        //      int j=0;
        float sum = 0.0f;
    
        for(i=0;i<nr_class;i++) {
	  for(j=i+1;j<nr_class;j++)
	    {
	      sum = 0.0f;
	      int si = start[i];
	      int sj = start[j];
	      int ci = model->nSV[i];
	      int cj = model->nSV[j];
                        
	      int k;
	      float *coef1 = &sv_coef[j-1];
	      float *coef2 = &sv_coef[i];
                        
	      for(k=0;k<ci;k++)
		sum += coef1[si+k] * kvalue[si+k];
                        
	      for(k=0;k<cj;k++)
		sum += coef2[sj+k] * kvalue[sj+k];
                        
	      sum -= model->rho[p];
	      dec_values[p] = sum;
                        
	      if(dec_values[p] > 0.0f)
		++vote[i];
	      else
		++vote[j];
	      p++;
                        
                        
	    }
	}

#ifdef DEBUG
	perf_stop();
	float sum_decvalues;
	sum_decvalues = 0.0F;
	for(int indk=0;indk<p;indk++){
	  sum_decvalues +=  100.0F*fAbs(dec_values[indk]);
	}
	printf("sum of decvalues: %d\n", (int) sum_decvalues);
	perf_start();
#endif


	int vote_max_idx = 0;
	for(i=1;i<nr_class;i++)
	  if(vote[i] > vote[vote_max_idx])
	    vote_max_idx = i;
                        
	#if  HWPERF
	perf_stop();
	#endif
	printf("\nRESULT:%d\n",model->label[vote_max_idx]);
	#if  HWPERF
	perf_start();
	#endif

	// free l1 memory
#if HWPERFFREE
	perf_start();
#endif
	l1free(vote);
	l1free(start);
	l1free(kvalue);
	l1free(sv_coef);
#if HWPERFFREE
	perf_stop();
	printf("FREE\n"); perf_print_all();
#endif
	return 0;
}

*/
