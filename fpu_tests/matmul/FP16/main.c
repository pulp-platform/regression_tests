// License, Version 0.51 (the "License"); you may not use this file except in
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "config.h"
#include "pulp.h"

#include <stdio.h>
#include <stdint.h>
#include <limits.h> /* for CHAR_BIT */
#include <math.h>

#include "data.h"

#define STACK_SIZE 2048

void main_fn(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "Matrix Multiplication", .test = main_fn },
  {0, 0}
};

DATA_LOCATION MA_TYPE matA[M*N] __attribute__ ((aligned (4)));
DATA_LOCATION MB_TYPE matB[N*P] __attribute__ ((aligned (4)));
DATA_LOCATION OUT_TYPE matC[M*P] __attribute__ ((aligned (4)));

// End of computation
int done = 0;

int retval = 0;

void __attribute__ ((noinline)) matrix_init(MA_TYPE * __restrict__ A, MB_TYPE * __restrict__ B, OUT_TYPE * __restrict__ C) {
  for (int i = 0; i < M; i++) 
    for (int j = 0; j < N; j++){
      A[i*N+j] = A_mat[i*N+j];


    } 
      
  for (int i = 0; i < N; i++) 
    for (int j = 0; j < P; j++){
      B[i*P+j] = B_mat[i*P+j];
    }
  for (int i = 0; i < M; i++) 
    for (int j = 0; j < P; j++)  
      C[i*P+j] = 0;
  
}

int __attribute ((noinline)) check_result(OUT_TYPE * __restrict__ result) {
  #ifndef FABRIC
    synch_barrier();
  #endif

  if(get_core_id() == 0) {
    float diff;
    int err = 0;

    for (int i = 0; i < (M*P); i++) {
      diff = fabs(result[i] - ref[i]);
      if(diff > THR) {
        err++;
      #ifdef VERBOSE

        printf("Error at index %d:\t refrence %f\t output %f\t error %.4f\n", i, ref[i], result[i], diff);
      #endif
      
      }

      #ifdef PRINT_RESULTS

        printf("index %d:\t refrence %f\t output %f\t error %f\n", i, ref[i], result[i], diff);
      #endif
    }

    return err;

  }
}

void main_fn(testresult_t *result, void (*start)(), void (*stop)()){
  
  if (get_core_id() == 0)
    matrix_init(matA, matB, matC);
 
  #ifndef FABRIC
  synch_barrier();
  #endif
  
  #ifdef STATS
  start();
  #endif
  matMul(matA, matB, matC, M, N, P);

  #ifdef STATS
  stop();
  #endif

  #ifdef CHECK
  result->errors = check_result(matC);
  #endif
};

int main()
{
  #ifdef FABRIC
      main_fn();
  #else
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  int nbErrors = run_suite(testcases);

  synch_barrier();
  #endif
  retval = nbErrors;

  return retval;
}
