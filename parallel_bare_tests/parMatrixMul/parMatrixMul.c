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
#include <stdio.h>

#include "parMatrixMul.h"

#define N_ITERS 1

#define CHECKSUM 

#ifdef CHECKSUM
#define CHKSM 88408
#endif

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

  // printf("Testing IRQ reg: 0x%x\n", rt_irq_get_fc_vector_base());

  if (rt_cluster_id() != 0) {
#ifdef ARCHI_TCLS
    enable_tcls();
#endif // TCLS
    return bench_cluster_forward(0);
  }

#ifdef ARCHI_TCLS
  // Enable interrupts
  hal_irq_enable();
#endif // TCLS

  int nbErrors = run_suite(testcases);

  synch_barrier();

#ifdef ARCHI_TCLS
  printf("Reading group %d core0_mismatch_reg: 0x%x\n", rt_core_id(), *(volatile int *)(ARCHI_TCLS_ADDR + 0x8 + rt_core_id()*0x100));
  printf("Reading group %d core1_mismatch_reg: 0x%x\n", rt_core_id(), *(volatile int *)(ARCHI_TCLS_ADDR + 0xC + rt_core_id()*0x100));
  printf("Reading group %d core2_mismatch_reg: 0x%x\n", rt_core_id(), *(volatile int *)(ARCHI_TCLS_ADDR + 0x10 + rt_core_id()*0x100));

  synch_barrier();
#endif // TCLS

  return nbErrors != 0;
}

void matrix_multiplication(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = rt_core_id();
  int numcores = get_core_num();
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
  lb = coreid * chunk;
  //upper bound
  ub = lb + chunk;
  if (coreid == numcores-1) {ub = SIZE;}
  
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

#ifdef CHECKSUM
  if(coreid == 0) {

    int chk = 0;
    for (k = 0; k < SIZE; k++)
      for (j = 0; j < SIZE; j++)
        chk += C[k][j];
    
    check_uint32(result, "Checksum failed", CHKSM, chk);
  }
#endif
}
