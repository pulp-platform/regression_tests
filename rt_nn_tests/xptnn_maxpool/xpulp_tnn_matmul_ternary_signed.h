#ifndef __XPULP_TNN_MATMUL_TERNARY_SIGNED_H
#define __XPULP_TNN_MATMUL_TERNARY_SIGNED_H

#include "pulp_nn_utils.h"

uint8_t * __attribute__((noinline)) xpulp_tnn_matmul_ternary_signed(
                        uint8_t  *pIn,
                        int8_t   *pBias,
                        uint32_t *pThr,
                        uint8_t  *pOut,
                        uint8_t  *pOut2,
                        uint8_t  *pWeight,
                        uint16_t num_col_im2col,
                        uint16_t ch_out,
#ifndef PROFILE
                        uint32_t *thrc_res1,
                        uint32_t *thrc_res2);
#else
                        uint32_t *thrc_res1,
                        uint32_t *thrc_res2,
                        uint32_t *hotloop_prep_cycles,
                        uint32_t *hotloop_cycles,
                        uint32_t *threshold_cycles,
                        uint32_t *hotloop_leftover_cycles);
#endif

inline void __attribute__((aligned(4))) hotloop_4x2(
  int *sum, int *sum2, int *sum3, int *sum4, int *sum5, int *sum6, int *sum7, int *sum8,
  uint32_t *ptrA, uint32_t *ptrA2, uint32_t *ptrA3, uint32_t *ptrA4,
  uint32_t *ptrB, uint32_t *ptrB2, int num_col_im2col_words
){
  for (int j=0; j<num_col_im2col_words; j++)
  {
    *sum = MacLoads20(0, 0, 0, 0, ptrA, *sum);
    *sum2 = MacLoads20(0, 0, 1, 0, ptrA2, *sum2);
    *sum3 = MacLoads20(0, 0, 2, 0, ptrA3, *sum3);
    *sum4 = MacLoads20(0, 1, 3, 0, ptrB, *sum4);
    ptrB = MacLoadUpdate(ptrB);

    *sum5 = MacLoads20(1, 0, 0, 1, ptrA, *sum5);
    ptrA = MacLoadUpdate(ptrA);
    *sum6 = MacLoads20(1, 0, 1, 1, ptrA2, *sum6);
    ptrA2 = MacLoadUpdate(ptrA2);
    *sum7 = MacLoads20(1, 0, 2, 1, ptrA3, *sum7);
    ptrA3 = MacLoadUpdate(ptrA3);
    *sum8 = MacLoads20(1, 0, 3, 1, ptrA4, *sum8);
    ptrA4 = MacLoadUpdate(ptrA4);

    ptrB2 = MacLoadInit(0, 1, 0, 1, ptrB2);
  }
}


inline void __attribute__((aligned(4))) hotloop_3x2(
  int *sum, int *sum2, int *sum3, int *sum4, int *sum5, int *sum6,
  uint32_t *ptrA, uint32_t *ptrA2, uint32_t *ptrA3, uint32_t *ptrB, uint32_t *ptrB2, int num_col_im2col_words
){
  for (int j=0; j<num_col_im2col_words; j++)
  {
    *sum = MacLoads20(0, 0, 0, 0, ptrA, *sum);
    *sum2 = MacLoads20(0, 0, 1, 0, ptrA2, *sum2);
    *sum3 = MacLoads20(0, 1, 2, 0, ptrB, *sum3);
    ptrB = MacLoadUpdate(ptrB);

    *sum4 = MacLoads20(1, 0, 0, 1, ptrA, *sum4);
    ptrA = MacLoadUpdate(ptrA);
    *sum5 = MacLoads20(1, 0, 1, 1, ptrA2, *sum5);
    ptrA2 = MacLoadUpdate(ptrA2);
    *sum6 = MacLoads20(1, 0, 2, 1, ptrA3, *sum6);
    ptrA3 = MacLoadUpdate(ptrA3);

    ptrB2 = MacLoadInit(0, 1, 0, 1, ptrB2);
  }
}


inline void __attribute__((aligned(4))) hotloop_2x2(
  int *sum, int *sum2, int *sum3, int *sum4,
  uint32_t *ptrA, uint32_t *ptrA2, uint32_t *ptrB, uint32_t *ptrB2, int num_col_im2col_words
){
  for (int j=0; j<num_col_im2col_words; j++)
  {
    *sum = MacLoads20(0, 0, 0, 0, ptrA, *sum);
    *sum2 = MacLoads20(0, 1, 1, 0, ptrB, *sum2);
    ptrB = MacLoadUpdate(ptrB);

    *sum3 = MacLoads20(1, 0, 0, 1, ptrA, *sum3);
    ptrA = MacLoadUpdate(ptrA);
    *sum4 = MacLoads20(1, 0, 1, 1, ptrA2, *sum4);
    ptrA2 = MacLoadUpdate(ptrA2);

    ptrB2 = MacLoadInit(0, 1, 0, 1, ptrB2);
  }
}


inline void __attribute__((aligned(4))) hotloop_1x2(
  int *sum, int *sum2, uint32_t *ptrA, uint32_t *ptrB, uint32_t *ptrB2, int num_col_im2col_words
){
  for (int j=0; j<num_col_im2col_words; j++)
  {
    *sum = MacLoads20(0, 1, 0, 0, ptrB, *sum);
    ptrB = MacLoadUpdate(ptrB);
    *sum2 = MacLoads20(1, 0, 0, 1, ptrA, *sum2);
    ptrA = MacLoadUpdate(ptrA);

    ptrB2 = MacLoadInit(0, 1, 0, 1, ptrB2);
  }
}



#endif