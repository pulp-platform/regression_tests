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
// #include "mchan.h"

void computeGoldMatrixMul(int* C, const int* A, const int* B, unsigned int offset, unsigned int hA, unsigned int wA, unsigned int wB);

void dma_ld1024(int*, int*);

PLP_L1_DATA int h_C[WC * HC*8];
PLP_L1_DATA int h_A[WA * HA*8];
PLP_L1_DATA int h_B[WB * HB*8];

int A_init[WA * HA];
int B_init[WB * HB];
int C_init[WB * HB];

int main()
{
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  int i;
  int j;
  int coreid = rt_core_id();
  int error = 0;
  int offset = coreid*WA*HA;
  unsigned int id;

  if (coreid == 0) {
    for (i = 0; i < WA * HA; i++)
      A_init[i] = i;

    for (i = 0; i < WB * HB; i++)
      B_init[i] = i;

    for (i = 0; i < WB * HB; i++)
      C_init[i] = 0;
  }

  synch_barrier();

  // load matrix A
#if MCHAN_VERSION >= 6
  plp_dma_wait(plp_dma_memcpy(A_init, h_A+offset, 1024, PLP_DMA_EXT2LOC));
#elif MCHAN_VERSION == 5
  // DMA v5
  id = mchan_transfer(1024, MCHAN_EXT_TO_LOC_MODE, MCHAN_INC_MODE, MCHAN_LIN_MODE, A_init, h_A+offset, 0,0);
  mchan_barrier(id);
#else
  // DMA v4
  dma_ld1024(h_A+offset, A_init);
  dma_barrier();
#endif
  synch_barrier();
  printf("DMA A done\n");

  // load matrix B
#if MCHAN_VERSION >= 6
  plp_dma_wait(plp_dma_memcpy(B_init, h_B+offset, 1024, PLP_DMA_EXT2LOC));
#elif MCHAN_VERSION >= 5
  // DMA v5
  id = mchan_transfer(1024, MCHAN_EXT_TO_LOC_MODE, MCHAN_INC_MODE, MCHAN_LIN_MODE, B_init, h_B+offset, 0,0);
  mchan_barrier(id);
#else
  // DMA v4
  dma_ld1024(h_B+offset, B_init);
  dma_barrier();
#endif
  synch_barrier();
  printf("DMA B done\n");

  for (i = 0; i<2; i++) {
#if MCHAN_VERSION >= 6
  plp_dma_wait(plp_dma_memcpy(C_init, h_C+offset, 1024, PLP_DMA_EXT2LOC));
#elif MCHAN_VERSION >= 5
    // DMA v5
    id = mchan_transfer(1024, MCHAN_EXT_TO_LOC_MODE, MCHAN_INC_MODE, MCHAN_LIN_MODE, C_init, h_C+offset, 0,0);
    mchan_barrier(id);
#else
    // DMA v4
    dma_ld1024(h_C+offset, C_init);
    dma_barrier();
#endif
    synch_barrier();

    for (j = 0; j < WC*HC; j++) {
      if (h_A[offset + j] != A_init[j])
        printf("h_A[%d] wrong\n", offset + j);

      if (h_B[offset + j] != B_init[j])
        printf("h_B[%d] wrong: Got %X, expected %X\n", offset + j, h_B[offset + j], B_init[j]);

      if (h_C[offset + j] != C_init[j])
        printf("h_C[%d] wrong\n", offset + j);
    }

    computeGoldMatrixMul(h_C, h_A, h_B, offset, HA, WA, WB);

    synch_barrier();
  }

  for (i=0; i<WC*HC; i++) {
    if (h_C[i+offset] != RESULT_MUL[i]) {
      printf("Error at index %d: Got %X, expected %X\n", i + offset, h_C[i+offset], RESULT_MUL[i]);
      error++;
    }
  }

  synch_barrier();

  print_summary((unsigned int) error);

  return error;
}

#if MCHAN_VERSION < 5
void dma_ld1024(int* tcdm_addr, int* ext_addr){
  set_tcdm_addr((int)tcdm_addr);
  set_ext_addr((int)ext_addr);
  push_cmd(LD1024);
}
#endif

void computeGoldMatrixMul(int* C, const int* A, const int* B, unsigned int offset, unsigned int hA, unsigned int wA, unsigned int wB)
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
