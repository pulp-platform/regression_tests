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

#include "dummypar1.h"

__attribute__ ((section(".heapsram"))) int matA[8*8];
__attribute__ ((section(".heapsram"))) int matB[8*8];
__attribute__ ((section(".heapsram"))) int matR1[8*8];
__attribute__ ((section(".heapsram"))) int matR2[8*8];
__attribute__ ((section(".heapsram"))) int matR3[8*8];
__attribute__ ((section(".heapsram"))) int matR4[8*8];

__attribute__ ((section(".heapsram"))) int matR5[8*8];
__attribute__ ((section(".heapsram"))) int matR6[8*8];
__attribute__ ((section(".heapsram"))) int matR7[8*8];
__attribute__ ((section(".heapsram"))) int matR8[8*8];

__attribute__ ((section(".heapsram"))) int matC[8*8];
__attribute__ ((section(".heapsram"))) int matD[8*8];

__attribute__ ((section(".heapsram"))) int matResult[16*16];



int main()
{
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
  
  int coreid;
  unsigned int errors;

  coreid = rt_core_id();

  // initialize matrices
  if (coreid == 0)
    initialize_mat(matA,8,5);
  else if (coreid == 1)
    initialize_mat(matB,8,1);
  else if (coreid == 2)
    initialize_mat(matC,8,3);
  else if (coreid == 3)
    initialize_mat(matD,8,7);

  // first stage of computation
  if (coreid == 0)
    MatrixAdd(matA, matA, matR1, 8, 0);
  else if (coreid == 1)
    MatrixMul(matA, matB, matR2, 8, 0);
  else if (coreid == 2)
    MatrixAdd(matB, matA, matR3, 8, 0);
  else if (coreid == 3)
    MatrixMul(matB, matB, matR4, 8, 0);

  synch_barrier();

  // second stage of computation // switched cores
  if (coreid == 3)
    MatrixMul(matR1, matC, matR5, 8, 0);
  else if (coreid == 0)
    MatrixAdd(matR2, matC, matR6, 8, 0);
  else if (coreid == 1)
    MatrixMul(matR3, matC, matR7, 8, 0);
  else if (coreid == 2)
    MatrixAdd(matR4, matC, matR8, 8, 0);

  synch_barrier();

  // third stage of computation // switched cores
  if (coreid == 2)
    MatrixAdd(matR5, matC, matR1, 8, 0);
  else if (coreid == 3)
    MatrixMul(matR6, matC, matR2, 8, 0);
  else if (coreid == 0)
    MatrixAdd(matR7, matC, matR3, 8, 0);
  else if (coreid == 1)
    MatrixMul(matR8, matC, matR4, 8, 0);

  synch_barrier();

  // last stage of computation // switched cores
  if (coreid == 1)
    MatrixMul(matR1, matD, matResult, 8, 0);
  else if (coreid == 2)
    MatrixAdd(matR2, matD, matResult, 8, 1);
  else if (coreid == 3)
    MatrixMul(matR3, matD, matResult, 8, 2);
  else if (coreid == 0)
    MatrixAdd(matR4, matD, matResult, 8, 3);

  synch_barrier();

  if (coreid < 4) {
  	const int EXP_RESULT[4] = {-1070580, -1014080, -957580, -901080};
	
	errors = (matResult[coreid] != EXP_RESULT[coreid]);
	
  	print_summary((unsigned int) errors);
  }

  return 0;
}

void initialize_mat(volatile int* A, unsigned int size, unsigned int seed)
{
  unsigned int i;
  for (i=0;i<size*size;i++){
    A[i] = seed*seed-i;
  }

}

void MatrixMul(volatile int* A, volatile int* B,volatile int* C, unsigned int size, unsigned int ind)
{

  unsigned int i,j,k;
  int a,b,sum;

  for (i = 0; i < size; ++i){
    for (j = 0; j < size; ++j) {
      sum = 0;
      for (k = 0; k < size; ++k) {
        a = A[i * size + k];
        b = B[k * size + j];
        sum += a * b;
      }
      C[i * size + j + ind*size*size] = (int)sum;
    }
  }
}


void MatrixAdd(volatile int* A, volatile int* B,volatile int* C, unsigned int size, unsigned int ind)
{
  unsigned int i,j;
  int a,b;

  for (i = 0; i < size; ++i){
    for (j = 0; j < size; ++j) {
      a = A[i * size + j];
      b = B[i * size + j];
      C[i * size + j + ind*size*size] = a+b;
    }
  }
}
