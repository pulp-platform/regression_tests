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
#include "matrixMul.h"
#include "pulp.h"

void computeGoldMatrixMul(volatile int*,volatile int*,volatile int*, unsigned int, unsigned int, unsigned int, unsigned int);

void copy_array(int*, int*, int);

__attribute__ ((section(".heapsram"))) int h_C[WC * HC*4];
__attribute__ ((section(".heapsram"))) int h_A[WA * HA*4];
__attribute__ ((section(".heapsram"))) int h_B[WB * HB*4];

__attribute__ ((section(".heapsram"))) int A_init[WA * HA];
__attribute__ ((section(".heapsram"))) int B_init[WB * HB];
__attribute__ ((section(".heapsram"))) int C_init[WB * HB];

__attribute__ ((section(".heapl2ram"))) int MasterID = 0;

int main()
{
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  int i;
  int coreid;
  int error;

  coreid = rt_core_id();

  if (coreid >= 4) {
    synch_barrier();
    synch_barrier();
    synch_barrier();
    synch_barrier();
    synch_barrier();
    return 0; // we don't need cores with id's higher than 4
  }

  int offset = coreid*WA*HA;

  error = 0;

  synch_barrier();

  if (coreid == MasterID) {
    for (i = 0; i < WA * HA; i++){
      A_init[i] = i;
    }
    for (i = 0; i < WB * HB; i++){
      B_init[i] = i;
    }
    for (i = 0; i < WB * HB; i++){
      C_init[i] = 0;
    }
  }

  synch_barrier();

  copy_array(A_init, h_A+offset, 256);
  synch_barrier();

  copy_array(B_init, h_B+offset, 256);
  synch_barrier();


  for (i = 0; i<2; i++) {
    copy_array(C_init, h_C+offset, 256);

    computeGoldMatrixMul(h_C, h_A, h_B, offset, HA, WA, WB);
  }

  for (i=0; i<WC*HC; i++) {
    if (h_C[i+offset] != RESULT_MUL[i]) {
      error = error + 1;
    }
  }

  synch_barrier();

  print_summary((unsigned int) error);

  return error;
}

void copy_array(int src[], int targ[], int size){
  int i;
  for (i=0;i<size;i++)
    targ[i] = src[i];
}


void computeGoldMatrixMul(volatile int* C, volatile int* A,volatile int* B, unsigned int offset, unsigned int hA, unsigned int wA, unsigned int wB)
{
  unsigned int i,j,k;
  unsigned int a,b,sum;

  for (i = 0; i < hA; ++i){
    for (j = 0; j < wB; ++j) {
      sum = 0;
      for (k = 0; k < wA; ++k) {
        a = A[i * wA + k + offset];
        b = B[k * wB + j + offset];
        sum += a * b;
      }
      C[i * wB + j + offset] = (unsigned int)sum;
    }
  }
}
