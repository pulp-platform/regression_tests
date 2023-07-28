/*
* @Author: Michael Rogenmoser
* @Date:   2023-02-17 18:00:21
* @Last Modified by:   Michael Rogenmoser
* @Last Modified time: 2023-02-17 18:15:33
*/
#include <pulp.h>
#include <stdio.h>
#include "matmul.h"

#define N_ITERS 1
#define max(x,y) (x > y ? x : y)
#define min(x,y) (x < y ? x : y)

__attribute__ ((section(".heapsram"))) int A[SIZE][SIZE];
__attribute__ ((section(".heapsram"))) int B[SIZE][SIZE];
__attribute__ ((section(".heapsram"))) int C[SIZE][SIZE];

void initialize_mat();

void initialize_mat() {
  int i,j;
  
  for (i=0;i<SIZE;i++) {
    for (j=0;j<SIZE;j++) {
      A[i][j] = A_init[i][j];
      B[i][j] = B_init[i][j];
    }
  }
  
}

void matrix_multiplication(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "Matrix Multiplication", .test = matrix_multiplication },
  {0, 0}
};

int main() {
  if (rt_cluster_id() != 0) {
    hmr_enable_all_tmr(0);
    // hmr_enable_all_dmr(0);
    hmr_set_dmr_config_all(0, true); // with rapid recovery
    // hmr_set_dmr_config_all(0, false); // no rapid recovery
    // hmr_set_tmr_config_all(0,  false, true, true, true); // setback, with rapid recovery
    hmr_set_tmr_config_all(0,  false, true, true, false); // setback, no rapid recovery
    printf("after setup: %x\n", hmr_get_active_cores(0));

    return bench_cluster_forward(0);
  }
  int nbErrors = run_suite(testcases);

  synch_barrier();

  return nbErrors != 0;
}

void matrix_multiplication(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = rt_core_id();
  int numcores = 4;//get_core_num();
  int *CHKSUM_RESULT;
  short int i, iter, j, k;
  int lb, ub, chunk;

  if (coreid == 0){
    printf("Start ParMatrixMul\n",0,0,0,0);
    // initialize matrix A and B
    initialize_mat();
  }
  //number of rows each core has to multiply
  chunk = SIZE / numcores;
  //lower bound
  lb = coreid * chunk +  min(coreid, SIZE % numcores);
  //upper bound
  ub = (coreid + 1) * chunk + min(coreid + 1, SIZE % numcores);
  if (coreid == numcores-1) {ub = SIZE;}

  printf("lb: %d, ub: %d\n", lb, ub);
  
  synch_barrier();
  
  /********************* Benchmark Execution *********************/
  if (coreid<numcores) {
    start();

    for (iter = 0; iter < N_ITERS; iter++) {
      for (i = lb; i < ub; i++) {
        for (k = 0; k < SIZE; k++) {
          C[i][k] = 0;
          for (j = 0; j < SIZE; j++)
            C[i][k] += A[i][j] * B[j][k];
        }
      }
    } 
  }
  synch_barrier();
  stop();
  
  /********************* Benchmark Execution *********************/

}
