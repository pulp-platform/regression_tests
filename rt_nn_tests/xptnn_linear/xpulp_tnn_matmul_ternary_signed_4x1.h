#ifndef __XPULP_TNN_MATMUL_TERNARY_SIGNED_4X1_H
#define __XPULP_TNN_MATMUL_TERNARY_SIGNED_4X1_H

#include "pulp_nn_utils.h"

uint8_t * __attribute__((noinline)) xpulp_tnn_matmul_ternary_signed_4x1(
                        uint8_t  *pIn,
                        int8_t   *pBias,
                        uint32_t *pThr,
                        uint8_t  *pOut,
                        uint8_t  *pWeight,
                        uint16_t num_col_im2col,
                        uint16_t ch_out,
#ifndef PROFILE
                        uint32_t *thrc_res);
#else
                        uint32_t *thrc_res,
                        uint32_t *hotloop_prep_cycles,
                        uint32_t *hotloop_cycles,
                        uint32_t *threshold_cycles,
                        uint32_t *hotloop_leftover_cycles);
#endif

inline void __attribute__((aligned(4))) hotloop_4x1(
  int *sum, int *sum2, int *sum3, int *sum4,
  uint32_t *ptrA, uint32_t *ptrA2, uint32_t *ptrA3, uint32_t *ptrA4,
  uint32_t *ptrB, int num_col_im2col_words
){
  for (int j=0; j<num_col_im2col_words; j++)
  {
    *sum = MacLoads20(1, 0, 0, 0, ptrA, *sum);
    ptrA = MacLoadUpdate(ptrA);
    *sum2 = MacLoads20(1, 0, 1, 0, ptrA2, *sum2);
    ptrA2 = MacLoadUpdate(ptrA2);
    *sum3 = MacLoads20(1, 0, 2, 0, ptrA3, *sum3);
    ptrA3 = MacLoadUpdate(ptrA3);
    *sum4 = MacLoads20(1, 0, 3, 0, ptrA4, *sum4);
    ptrA4 = MacLoadUpdate(ptrA4);

    ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
    asm volatile ("nop;");
  }
}


inline void __attribute__((aligned(4))) hotloop_3x1(
  int *sum, int *sum2, int *sum3,
  uint32_t *ptrA, uint32_t *ptrA2, uint32_t *ptrA3, uint32_t *ptrB, int num_col_im2col_words
){
  for (int j=0; j<num_col_im2col_words; j++)
  {
    *sum = MacLoads20(1, 0, 0, 0, ptrA, *sum);
    ptrA = MacLoadUpdate(ptrA);
    *sum2 = MacLoads20(1, 0, 1, 0, ptrA2, *sum2);
    ptrA2 = MacLoadUpdate(ptrA2);
    *sum3 = MacLoads20(1, 0, 2, 0, ptrA3, *sum3);
    ptrA3 = MacLoadUpdate(ptrA3);

    ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
    asm volatile ("nop;");
  }
}


inline void __attribute__((aligned(4))) hotloop_2x1(
  int *sum, int *sum2, uint32_t *ptrA, uint32_t *ptrA2, uint32_t *ptrB, int num_col_im2col_words
){
  for (int j=0; j<num_col_im2col_words; j++)
  {
    *sum = MacLoads20(1, 0, 0, 0, ptrA, *sum);
    ptrA = MacLoadUpdate(ptrA);
    *sum2 = MacLoads20(1, 0, 1, 0, ptrA2, *sum2);
    ptrA2 = MacLoadUpdate(ptrA2);

    ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
    asm volatile ("nop;");
  }
}


inline void __attribute__((aligned(4))) hotloop_1x1(
  int *sum, uint32_t *ptrA, uint32_t *ptrB, int num_col_im2col_words
){
  for (int j=0; j<num_col_im2col_words; j++)
  {
    *sum = MacLoads20(1, 0, 0, 0, ptrA, *sum);
    ptrA = MacLoadUpdate(ptrA);

    ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
    asm volatile ("nop;");
  }
}



#endif