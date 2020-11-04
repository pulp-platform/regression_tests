/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * Mantainer: Luca Valente, luca.valente2@unibo.it
 */

#include <pulp.h>

#define N 4
#define F 10000

#define MIN(a, b) (((a)<(b))? (a): (b))
#define ABS(a)    (((a)>=0)? (a): (-(a)))

int lu[N*N] = {
    83, 86, 77, 15, 
    93, 35, 86, 92, 
    49, 21, 62, 27, 
    90, 59, 63, 26, 
    };

int lu_ref[N*N] = {
     8924,    55,     1,   -67, 
       93,    35,    86,    92, 
     5268,   545, -8500,   -45, 
     9677,  4727,   -20,   -32, 
    };

__attribute__((section(".heapsram"))) int lu_in[N*N];
__attribute__((section(".heapsram"))) int lu_out[N*N];
__attribute__((section(".heapsram"))) int *G[N];
__attribute__((section(".heapsram"))) int pivots[N];
__attribute__((section(".heapsram"))) volatile int error_status;

static inline int factor(int *A[], int m, int n, int pivot[])
{
  int i, j, k, ii;
  int minMN = MIN(m,n);
  int num_cores = get_core_num();
  int id = rt_core_id();

  for (j=0; j<minMN; ++j)
  {

    // find pivot in column j and  test for singularity.
    int jp=j;

    int t = ABS(A[j][j]);

    if(id == 0)  // core 0
      {

        for (i=j+1; i<m; ++i)
          {
            int ab = ABS(A[i][j]);
            if (ab > t)
              {
                jp = i;
                t = ab;
              }
          }

        pivot[j] = jp;

        // jp now has the index of maximum element 
        // of column j, below the diagonal

        if (A[jp][j] == 0 )
          {
            printf("ERRORE DETECTED = %d\n", id);
            error_status = 1;       // factorization failed because of zero pivot
          }

        if (jp != j)
          {
            // swap rows j and jp
            int *tA = A[j];
            A[j] = A[jp];
            A[jp] = tA;
          }
      }

    synch_barrier();

    if(error_status == 1) return 1;

    //#pragma omp parallel
    {
      if (j<m-1)                // compute elements j+1:M of jth column
        {
          // note A(j,j), was A(jp,p) previously which was
          // guarranteed not to be zero (Label #1)

          int recp = (F * F) / A[j][j];

          //#pragma omp for
          for (k=j+1; k<m; ++k)
            {
              if( (k%num_cores) != id) continue;
              A[k][j] *= recp;
              A[k][j] /= F;
            }
        }

      if (j < minMN-1)
        {
          // rank-1 update to trailing submatrix:   E = E - x*y;
          //
          // E is the region A(j+1:M, j+1:N)
          // x is the column vector A(j+1:M,j)
          // y is row vector A(j,j+1:N)

          //#pragma omp for
          for (ii=j+1; ii<m; ++ii)
            {
              if( (ii%num_cores) != id) continue;
              int jj;
              int *Aii = A[ii];
              int *Aj  = A[j];
              int AiiJ = Aii[j];
              for (jj=j+1; jj<n; ++jj)
                {
                  Aii[jj] -= (AiiJ * Aj[jj])/F;
                }
            }
        }
    }  // parallel

    synch_barrier();

  }

  return 0;
}

int main(int argc, char **argv)
{
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
  
  int i, j;
  int num_cores = get_core_num();
  int id,hc;
  int time = 0;
  int error = 0;

  id = rt_core_id();

  if (id == 0)
    printf("Starting LU application... \n");

  for (i=0; i<N*N; ++i)
    lu_in[i] = lu[i];

  for(i=0; i<N; ++i)
    G[i] = lu_in + N*i;

  synch_barrier();

  for(hc = 0; hc < 3; ++hc) {

    if ( hc == 2 && id == 0 ) {
      reset_timer();
      start_timer();
    }
    perf_reset();
    perf_start();
    
    synch_barrier();

    factor(G, N, N, pivots);

    if ( hc == 2 && id == 0 ) {
      stop_timer();
      time = get_time();
    }
    perf_stop();

    if ( hc == 0 && id == 0 ) {
      for(i=0; i<N*N; ++i) {
        lu_out[i] = lu_in[i];
      }
    }

  }


  if (id == 0)
    printf("...LU application complete!  Errors: %d, Time: %d cycles\n",error,time);

  perf_print_all();
  print_summary((unsigned int) error);

  return error;
}
