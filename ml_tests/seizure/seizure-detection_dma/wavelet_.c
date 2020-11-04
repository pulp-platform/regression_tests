#include "wavelet_.h"
#include "hwPerf.h"
//DEF TRASFORMATA
//static void dwt_step (const gsl_wavelet * w, double *a, size_t stride, size_t n, gsl_wavelet_direction dir, gsl_wavelet_workspace * work);
/*__attribute__ ((aligned (8))) RT_LOCAL_DATA*/ 



static void
dwt_step (const gsl_wavelet * w, float *a, size_t stride, size_t n,
          gsl_wavelet_direction dir, gsl_wavelet_workspace * work)
{

  float ai, ai1;
  size_t i, ii;
  size_t jf;
  size_t k;
  size_t n1, ni, nh, nmod;
  //  #pragma omp parallel num_threads(CORE)
  //  #pragma omp for 
  for (i = 0; i < work->n; i++)
    {
      work->scratch[i] = 0.0f;
    }

  nmod = w->nc * n;
  nmod -= w->offset;            /* center support */

  n1 = n - 1;
  nh = n >> 1;

  
  ii = 0;
  float h,g;
	
  //#pragma omp parralel for
  for (i = 0; i < n; i += 2)
    {
      h = 0, g = 0;

      ni = i + nmod;
	
      for (k = 0; k < w->nc; k++)
	{
	  jf = n1 & (ni + k);
	  h += w->h1[k] * ((a)[(stride)*(jf)]);//ELEMENT (a, stride, jf);
	  g += w->g1[k] * ((a)[(stride)*(jf)]);//ELEMENT (a, stride, jf);
	}
	 
      work->scratch[ii] += h;
      work->scratch[ii + nh] += g;
	
      ii++; 
	
    }
  			   
  for (i = 0; i < n; i++)
    {
      ELEMENT (a, stride, i) = work->scratch[i];
    }
}

/*

  int
  gsl_wavelet_transform (const gsl_wavelet * w,
  float *data, size_t stride, size_t n,
  gsl_wavelet_workspace * work
  )
*/
int
gsl_wavelet_transform (float *data, size_t stride, size_t n, gsl_wavelet_workspace *ptr_workspace)
{
  gsl_wavelet haar;
  gsl_wavelet *w;
  gsl_wavelet_direction dir = gsl_wavelet_forward;
  size_t i;

  w=&haar;

  w->h1=ch_2;
  w->g1=cg_2;
  w->h2=ch_2;
  w->g2=cg_2;
  w->nc=2;
  w->offset=0;
   
  for (i = n; i >= 2; i >>= 1)
    {
		
      dwt_step (w, data, stride, i, dir, ptr_workspace);
			
    }

  return 0;
}

/*
  int wavelet_alloc(gsl_wavelet *ptr_wavelet){

  ptr_wavelet->h1=ch_2;
  ptr_wavelet->g1=cg_2;
  ptr_wavelet->h2=ch_2;
  ptr_wavelet->g2=cg_2;
  ptr_wavelet->nc=2;
  ptr_wavelet->offset=0;
  return ptr_wavelet;

  }

  int workspace_alloc(gsl_wavelet_workspace *ptr_workspace){

  ptr_workspace->n=window;
  ptr_workspace->scratch=ptr_scratch;
  return ptr_workspace;
  }
*/

void calcolo_energia(float *datiInput, float *Output){


	   
  int i;
  int j=0;
  float energy=0.0f;
  float square;
  int n=1;
	
		
  //		#pragma omp parallel num_threads(CORE)
  //		{
  energy=0;
  //		#pragma omp for reduction(+:energy) //schedule(dynamic,35) 		
  for(i=(window/(2));i<(window);i++){
    square=datiInput[i]*datiInput[i];
    energy=energy+square;
  }
  Output[0]=energy;
  energy=0.0f;
  //		#pragma omp for reduction(+:energy) //schedule(dynamic,25)
  for(i=(window/(4));i<(window/2);i++){
    square=datiInput[i]*datiInput[i];
    energy=energy+square;
  }
  Output[1]=energy;
  energy=0.0f;
  //#pragma omp for reduction(+:energy) 
  for(i=(window/(8));i<(window/4);i++){
    square=datiInput[i]*datiInput[i];
    energy=energy+square;
  }
  Output[2]=energy;
  energy=0.0f;
  //#pragma omp for reduction(+:energy)
  for(i=(window/(16));i<(window/8);i++){
    square=datiInput[i]*datiInput[i];
    energy=energy+square;
  }
  Output[3]=energy;
  //		}
	

}

