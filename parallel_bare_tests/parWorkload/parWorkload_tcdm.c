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


__attribute__ ((section(".heapsram"))) int h_C[WC * HC*4];
__attribute__ ((section(".heapsram"))) int h_A[WA * HA*4];
__attribute__ ((section(".heapsram"))) int h_B[WB * HB*4];


int main()
{
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  int i;
  int error=0;
  int coreid;

  coreid = rt_core_id();
  if (coreid >= 4) {
    synch_barrier();
    return 0; // we don't need cores with id's higher than 4
  }

  int offset = coreid*WA*HA;

  for (i = 0; i < WA * HA; i++)
    h_A[i+offset] = i;

  for (i = 0; i < WB * HB; i++)
    h_B[i+offset] = i;


  for (i = 0; i<2; i++) {
    for (i = 0; i < WB * HB; i++)
      h_C[i+offset] = 0;

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
