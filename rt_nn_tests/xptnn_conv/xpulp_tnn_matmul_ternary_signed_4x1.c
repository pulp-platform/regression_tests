#include <stdio.h>
#include <math.h>
#include "pulp_nn_utils.h"
#include "xpulp_tnn_matmul_ternary_signed_4x1.h"



// TODO: review argument order
uint8_t * __attribute__((noinline)) xpulp_tnn_matmul_ternary_signed_4x1(
                        uint8_t  *pIn,
                        int8_t   *pBias,
                        uint32_t *pThr,
                        uint8_t  *pOut,
                        uint8_t  *pWeight,
                        uint16_t num_col_im2col,
                        uint16_t ch_out,
#ifndef PROFILE
                        uint32_t *thrc_res)
{
#else
                        uint32_t *thrc_res,
                        uint32_t *hotloop_prep_cycles,
                        uint32_t *hotloop_cycles,
                        uint32_t *threshold_cycles,
                        uint32_t *hotloop_leftover_cycles)
{
  uint32_t hotloop_prep_add;
  uint32_t hotloop_add;
  uint32_t threshold_add;
  uint32_t hotloop_leftover_add;
#endif
  uint16_t ch_out_r = ch_out / 5;

  uint16_t num_col_im2col_w = num_col_im2col / 5;
  uint16_t num_col_im2col_a = num_col_im2col_w;
  uint16_t num_col_im2col_c = num_col_im2col_w << 2;
  // used for hotloop calls
  uint16_t num_col_im2col_words = num_col_im2col_w >> 2;

  uint8_t *pA = pWeight;
  v2s *currThr = (v2s *) pThr;

  int res;
  res = *thrc_res;

  for(int i=0; i < ch_out >> 2; i++)
  {
    #ifdef PROFILE
    //printf("Started hotloop_prep counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    uint8_t *pB = pIn;

    uint32_t *ptrB  = (uint32_t *) pB;

    uint8_t *pA2 = (pA + num_col_im2col_w);
    uint8_t *pA3 = (pA2 + num_col_im2col_w);
    uint8_t *pA4 = (pA3 + num_col_im2col_w);

    uint32_t *ptrA  = (uint32_t *) pA ;
    uint32_t *ptrA2 = (uint32_t *) pA2;
    uint32_t *ptrA3 = (uint32_t *) pA3;
    uint32_t *ptrA4 = (uint32_t *) pA4;

    ptrA = MacLoadInit(1, 0, 0, 0, ptrA);
    ptrA2 = MacLoadInit(1, 0, 1, 0, ptrA2);
    ptrA3 = MacLoadInit(1, 0, 2, 0, ptrA3);
    ptrA4 = MacLoadInit(1, 0, 3, 0, ptrA4);

  
    ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
  
    int sum = 0;
    int sum2 = 0;
    int sum3 = 0;
    int sum4 = 0;

    if (pBias != NULL)
    {
      sum = ((int) (*pBias++));
      sum2 = ((int) (*pBias++));
      sum3 = ((int) (*pBias++));
      sum4 = ((int) (*pBias++));
    }
    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop_prep counter\n");
    read_cycle_counter(hotloop_prep_add);
    *hotloop_prep_cycles += hotloop_prep_add;
    #endif

    #ifdef PROFILE
    //printf("Started hotloop counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    
    hotloop_4x1(
      &sum, &sum2, &sum3, &sum4, ptrA, ptrA2, ptrA3, ptrA4, ptrB, num_col_im2col_words
    );

    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop counter\n");
    read_cycle_counter(hotloop_add);
    *hotloop_cycles += hotloop_add;
    #endif

    #ifdef PROFILE
    //printf("Started hotloop_leftover counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    int col_cnt_im2col = num_col_im2col_c & 0xf;

    if (col_cnt_im2col)
    {
      uint16_t loop_cnt_im2col_w = (num_col_im2col_words) << 2;
      pA+=loop_cnt_im2col_w;
      pA2+=loop_cnt_im2col_w;
      pA3+=loop_cnt_im2col_w;
      pA4+=loop_cnt_im2col_w;

      uint16_t loop_cnt_im2col_a = (num_col_im2col_words) << 2;
      pB+=loop_cnt_im2col_a;

      volatile uint32_t valA, valA2, valA3, valA4, valB;
      // pack the remaining weights and activations into 32-bit vectors
      // padding with 0xd9 because ternary_decoder(0xd9) = 0000000000
      if (col_cnt_im2col == 4)
      {
        valA = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA;
        valA2 = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA2;
        valA3 = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA3;
        valA4 = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA4;

        valB = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pB;
      }
      else if (col_cnt_im2col == 8)
      {
        valA = 0xd9 << 24 | 0xd9 << 16 | *(pA + 1) << 8 | *pA;
        valA2 = 0xd9 << 24 | 0xd9 << 16 | *(pA2 + 1) << 8 | *pA2;
        valA3 = 0xd9 << 24 | 0xd9 << 16 | *(pA3 + 1) << 8 | *pA3;
        valA4 = 0xd9 << 24 | 0xd9 << 16 | *(pA4 + 1) << 8 | *pA4;

        valB = 0xd9 << 24 | 0xd9 << 16 | *(pB + 1) << 8 | *pB;
      }
      else // col_cnt_im2col == 12
      {
        valA = 0xd9 << 24 | *(pA + 2) << 16 | *(pA + 1) << 8 | *pA;
        valA2 = 0xd9 << 24 | *(pA2 + 2) << 16 | *(pA2 + 1) << 8 | *pA2;
        valA3 = 0xd9 << 24 | *(pA3 + 2) << 16 | *(pA3 + 1) << 8 | *pA3;
        valA4 = 0xd9 << 24 | *(pA4 + 2) << 16 | *(pA4 + 1) << 8 | *pA4;

        valB = 0xd9 << 24 | *(pB + 2) << 16 | *(pB + 1) << 8 | *pB;
      }

      uint32_t *pA_p = &valA;
      uint32_t *pA2_p = &valA2;
      uint32_t *pA3_p = &valA3;
      uint32_t *pA4_p = &valA4;

      uint32_t *pB_p = &valB;

      pA_p = MacLoadInit(1, 0, 0, 0, pA_p);
      pA2_p = MacLoadInit(1, 0, 1, 0, pA2_p);
      pA3_p = MacLoadInit(1, 0, 2, 0, pA3_p);
      pA4_p = MacLoadInit(1, 0, 3, 0, pA4_p);
      pB_p = MacLoadInit(0, 1, 0, 0, pB_p);
  
      pA += PACK_INT2_SIZE(col_cnt_im2col);

      sum = MacLoads20(0, 0, 0, 0, pA_p, sum);
      sum2 = MacLoads20(0, 0, 1, 0, pA2_p, sum2);
      sum3 = MacLoads20(0, 0, 2, 0, pA3_p, sum3);
      sum4 = MacLoads20(0, 0, 3, 0, pA4_p, sum4);
    }
    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop_leftover counter\n");
    read_cycle_counter(hotloop_leftover_add);
    *hotloop_leftover_cycles += hotloop_leftover_add;
    #endif

    #ifdef PROFILE
    //printf("Started threshold counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    res = thr_cmp(res, sum, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    res = thr_cmp(res, sum2, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    res = thr_cmp(res, sum3, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    res = thr_cmp(res, sum4, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped threshold counter\n");
    read_cycle_counter(threshold_add);
    *threshold_cycles += threshold_add;
    #endif

    if (!col_cnt_im2col)
    {
      pA+=(4*num_col_im2col_w);
    }
    else
    {
      pA+=(3*num_col_im2col_w);
    }
  }

  // leftover part : the hotloop above produces 4N output channels. If out_ch not divisible
  // by 4, the remaining output channels are computed below
  int out_ch_left = ch_out & 0x3;

  if (out_ch_left == 1)
  {
    #ifdef PROFILE
    //printf("Started hotloop_prep counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    uint8_t *pB = pIn;

    uint32_t *ptrB  = (uint32_t *) pB;

    uint32_t *ptrA  = (uint32_t *) pA ;

    ptrA = MacLoadInit(1, 0, 0, 0, ptrA);

  
    ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
  
    int sum = 0;

    if (pBias != NULL)
    {
      sum = ((int) (*pBias++));
    }
    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop_prep counter\n");
    read_cycle_counter(hotloop_prep_add);
    *hotloop_prep_cycles += hotloop_prep_add;
    #endif

    #ifdef PROFILE
    //printf("Started hotloop counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    
    hotloop_1x1(
      &sum, ptrA, ptrB, num_col_im2col_words
    );

    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop counter\n");
    read_cycle_counter(hotloop_add);
    *hotloop_cycles += hotloop_add;
    #endif

    #ifdef PROFILE
    //printf("Started hotloop_leftover counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    int col_cnt_im2col = num_col_im2col_c & 0xf;

    if (col_cnt_im2col)
    {
      uint16_t loop_cnt_im2col_w = (num_col_im2col_words) << 2;
      pA+=loop_cnt_im2col_w;

      uint16_t loop_cnt_im2col_a = (num_col_im2col_words) << 2;
      pB+=loop_cnt_im2col_a;

      volatile uint32_t valA, valB;
      // pack the remaining weights and activations into 32-bit vectors
      // padding with 0xd9 because ternary_decoder(0xd9) = 0000000000
      if (col_cnt_im2col == 4)
      {
        valA = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA;

        valB = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pB;
      }
      else if (col_cnt_im2col == 8)
      {
        valA = 0xd9 << 24 | 0xd9 << 16 | *(pA + 1) << 8 | *pA;

        valB = 0xd9 << 24 | 0xd9 << 16 | *(pB + 1) << 8 | *pB;
      }
      else // col_cnt_im2col == 12
      {
        valA = 0xd9 << 24 | *(pA + 2) << 16 | *(pA + 1) << 8 | *pA;

        valB = 0xd9 << 24 | *(pB + 2) << 16 | *(pB + 1) << 8 | *pB;
      }

      uint32_t *pA_p = &valA;

      uint32_t *pB_p = &valB;

      pA_p = MacLoadInit(1, 0, 0, 0, pA_p);
      pB_p = MacLoadInit(0, 1, 0, 0, pB_p);
  
      pA += PACK_INT2_SIZE(col_cnt_im2col);

      sum = MacLoads20(0, 0, 0, 0, pA_p, sum);
    }
    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop_leftover counter\n");
    read_cycle_counter(hotloop_leftover_add);
    *hotloop_leftover_cycles += hotloop_leftover_add;
    #endif

    #ifdef PROFILE
    //printf("Started threshold counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    res = thr_cmp(res, sum, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped threshold counter\n");
    read_cycle_counter(threshold_add);
    *threshold_cycles += threshold_add;
    #endif

    if (!col_cnt_im2col)
    {
      pA+=num_col_im2col_w;
    }
  }
  else if (out_ch_left == 2)
  {
    #ifdef PROFILE
    //printf("Started hotloop_prep counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    uint8_t *pB = pIn;

    uint32_t *ptrB  = (uint32_t *) pB;

    uint8_t *pA2 = (pA + num_col_im2col_w);

    uint32_t *ptrA  = (uint32_t *) pA ;
    uint32_t *ptrA2 = (uint32_t *) pA2;

    ptrA = MacLoadInit(1, 0, 0, 0, ptrA);
    ptrA2 = MacLoadInit(1, 0, 1, 0, ptrA2);

  
    ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
  
    int sum = 0;
    int sum2 = 0;

    if (pBias != NULL)
    {
      sum = ((int) (*pBias++));
      sum2 = ((int) (*pBias++));
    }
    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop_prep counter\n");
    read_cycle_counter(hotloop_prep_add);
    *hotloop_prep_cycles += hotloop_prep_add;
    #endif

    #ifdef PROFILE
    //printf("Started hotloop counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    
    hotloop_2x1(
      &sum, &sum2, ptrA, ptrA2, ptrB, num_col_im2col_words
    );

    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop counter\n");
    read_cycle_counter(hotloop_add);
    *hotloop_cycles += hotloop_add;
    #endif

    #ifdef PROFILE
    //printf("Started hotloop_leftover counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    int col_cnt_im2col = num_col_im2col_c & 0xf;

    if (col_cnt_im2col)
    {
      uint16_t loop_cnt_im2col_w = (num_col_im2col_words) << 2;
      pA+=loop_cnt_im2col_w;
      pA2+=loop_cnt_im2col_w;

      uint16_t loop_cnt_im2col_a = (num_col_im2col_words) << 2;
      pB+=loop_cnt_im2col_a;

      volatile uint32_t valA, valA2, valB;
      // pack the remaining weights and activations into 32-bit vectors
      // padding with 0xd9 because ternary_decoder(0xd9) = 0000000000
      if (col_cnt_im2col == 4)
      {
        valA = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA;
        valA2 = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA2;

        valB = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pB;
      }
      else if (col_cnt_im2col == 8)
      {
        valA = 0xd9 << 24 | 0xd9 << 16 | *(pA + 1) << 8 | *pA;
        valA2 = 0xd9 << 24 | 0xd9 << 16 | *(pA2 + 1) << 8 | *pA2;

        valB = 0xd9 << 24 | 0xd9 << 16 | *(pB + 1) << 8 | *pB;
      }
      else // col_cnt_im2col == 12
      {
        valA = 0xd9 << 24 | *(pA + 2) << 16 | *(pA + 1) << 8 | *pA;
        valA2 = 0xd9 << 24 | *(pA2 + 2) << 16 | *(pA2 + 1) << 8 | *pA2;

        valB = 0xd9 << 24 | *(pB + 2) << 16 | *(pB + 1) << 8 | *pB;
      }

      uint32_t *pA_p = &valA;
      uint32_t *pA2_p = &valA2;

      uint32_t *pB_p = &valB;

      pA_p = MacLoadInit(1, 0, 0, 0, pA_p);
      pA2_p = MacLoadInit(1, 0, 1, 0, pA2_p);
      pB_p = MacLoadInit(0, 1, 0, 0, pB_p);
  
      pA += PACK_INT2_SIZE(col_cnt_im2col);

      sum = MacLoads20(0, 0, 0, 0, pA_p, sum);
      sum2 = MacLoads20(0, 0, 1, 0, pA2_p, sum2);
    }
    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop_leftover counter\n");
    read_cycle_counter(hotloop_leftover_add);
    *hotloop_leftover_cycles += hotloop_leftover_add;
    #endif

    #ifdef PROFILE
    //printf("Started threshold counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    res = thr_cmp(res, sum, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    res = thr_cmp(res, sum2, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped threshold counter\n");
    read_cycle_counter(threshold_add);
    *threshold_cycles += threshold_add;
    #endif

    if (!col_cnt_im2col)
    {
      pA+=(2*num_col_im2col_w);
    }
    else
    {
      pA+=num_col_im2col_w;
    }
  }
  else if (out_ch_left == 3)
  {
    #ifdef PROFILE
    //printf("Started hotloop_prep counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    uint8_t *pB = pIn;

    uint32_t *ptrB  = (uint32_t *) pB;

    uint8_t *pA2 = (pA + num_col_im2col_w);
    uint8_t *pA3 = (pA2 + num_col_im2col_w);

    uint32_t *ptrA  = (uint32_t *) pA ;
    uint32_t *ptrA2 = (uint32_t *) pA2;
    uint32_t *ptrA3 = (uint32_t *) pA3;
    ptrA = MacLoadInit(1, 0, 0, 0, ptrA);
    ptrA2 = MacLoadInit(1, 0, 1, 0, ptrA2);
    ptrA3 = MacLoadInit(1, 0, 2, 0, ptrA3);

  
    ptrB = MacLoadInit(0, 1, 0, 0, ptrB);
  
    int sum = 0;
    int sum2 = 0;
    int sum3 = 0;

    if (pBias != NULL)
    {
      sum = ((int) (*pBias++));
      sum2 = ((int) (*pBias++));
      sum3 = ((int) (*pBias++));
    }
    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop_prep counter\n");
    read_cycle_counter(hotloop_prep_add);
    *hotloop_prep_cycles += hotloop_prep_add;
    #endif

    #ifdef PROFILE
    //printf("Started hotloop counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    
    hotloop_3x1(
      &sum, &sum2, &sum3,
      ptrA, ptrA2, ptrA3, ptrB, num_col_im2col_words
    );

    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop counter\n");
    read_cycle_counter(hotloop_add);
    *hotloop_cycles += hotloop_add;
    #endif

    #ifdef PROFILE
    //printf("Started hotloop_leftover counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    int col_cnt_im2col = num_col_im2col_c & 0xf;

    if (col_cnt_im2col)
    {
      uint16_t loop_cnt_im2col_w = (num_col_im2col_words) << 2;
      pA+=loop_cnt_im2col_w;
      pA2+=loop_cnt_im2col_w;
      pA3+=loop_cnt_im2col_w;

      uint16_t loop_cnt_im2col_a = (num_col_im2col_words) << 2;
      pB+=loop_cnt_im2col_a;

      volatile uint32_t valA, valA2, valA3, valB;
      // pack the remaining weights and activations into 32-bit vectors
      // padding with 0xd9 because ternary_decoder(0xd9) = 0000000000
      if (col_cnt_im2col == 4)
      {
        valA = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA;
        valA2 = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA2;
        valA3 = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pA3;

        valB = 0xd9 << 24 | 0xd9 << 16 | 0xd9 << 8 | *pB;
      }
      else if (col_cnt_im2col == 8)
      {
        valA = 0xd9 << 24 | 0xd9 << 16 | *(pA + 1) << 8 | *pA;
        valA2 = 0xd9 << 24 | 0xd9 << 16 | *(pA2 + 1) << 8 | *pA2;
        valA3 = 0xd9 << 24 | 0xd9 << 16 | *(pA3 + 1) << 8 | *pA3;

        valB = 0xd9 << 24 | 0xd9 << 16 | *(pB + 1) << 8 | *pB;
      }
      else // col_cnt_im2col == 12
      {
        valA = 0xd9 << 24 | *(pA + 2) << 16 | *(pA + 1) << 8 | *pA;
        valA2 = 0xd9 << 24 | *(pA2 + 2) << 16 | *(pA2 + 1) << 8 | *pA2;
        valA3 = 0xd9 << 24 | *(pA3 + 2) << 16 | *(pA3 + 1) << 8 | *pA3;

        valB = 0xd9 << 24 | *(pB + 2) << 16 | *(pB + 1) << 8 | *pB;
      }

      uint32_t *pA_p = &valA;
      uint32_t *pA2_p = &valA2;
      uint32_t *pA3_p = &valA3;

      uint32_t *pB_p = &valB;

      pA_p = MacLoadInit(1, 0, 0, 0, pA_p);
      pA2_p = MacLoadInit(1, 0, 1, 0, pA2_p);
      pA3_p = MacLoadInit(1, 0, 2, 0, pA3_p);
      pB_p = MacLoadInit(0, 1, 0, 0, pB_p);
  
      pA += PACK_INT2_SIZE(col_cnt_im2col);

      sum = MacLoads20(0, 0, 0, 0, pA_p, sum);
      sum2 = MacLoads20(0, 0, 1, 0, pA2_p, sum2);
      sum3 = MacLoads20(0, 0, 2, 0, pA3_p, sum3);
    }
    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped hotloop_leftover counter\n");
    read_cycle_counter(hotloop_leftover_add);
    *hotloop_leftover_cycles += hotloop_leftover_add;
    #endif

    #ifdef PROFILE
    //printf("Started threshold counter\n");
    reset_cycle_counter();
    start_cycle_counter();
    #endif
    res = thr_cmp(res, sum, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    res = thr_cmp(res, sum2, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    res = thr_cmp(res, sum3, *currThr++);
    check_store_4x1(res, pOut);
    reset_currThr();

    #ifdef PROFILE
    stop_cycle_counter();
    //printf("Stopped threshold counter\n");
    read_cycle_counter(threshold_add);
    *threshold_cycles += threshold_add;
    #endif

    if (!col_cnt_im2col)
    {
      pA+=(3*num_col_im2col_w);
    }
    else
    {
      pA+=(2*num_col_im2col_w);
    }
  }

  *thrc_res = res;

  return pOut;
}




