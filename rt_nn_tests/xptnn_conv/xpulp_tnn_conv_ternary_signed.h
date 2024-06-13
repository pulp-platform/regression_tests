#ifndef __XPULP_NN_CONV_TERNARY_SIGNED_H
#define __XPULP_NN_CONV_TERNARY_SIGNED_H
#include <stdio.h>
#include "pulp_nn_utils.h"



// TODO: review argument order
void __attribute__((noinline)) xpulp_tnn_conv_ternary_signed(
                                                     uint8_t  *pIn,
                                                     uint8_t  *pIm2ColBuffer,
                                                     int8_t   *pBias,
                                                     uint8_t  *pOut,
                                                     uint8_t  *pWeight,
                                                     uint32_t *pThr,
                                                     uint16_t  dim_in_x,
                                                     uint16_t  dim_in_y,
                                                     uint16_t  ch_in,
                                                     uint16_t  dim_out_x,
                                                     uint16_t  dim_out_y,
                                                     uint16_t  ch_out,
                                                     uint16_t  dim_kernel_x,
                                                     uint16_t  dim_kernel_y,
                                                     uint16_t  padding_y_top,
                                                     uint16_t  padding_y_bottom,
                                                     uint16_t  padding_x_left,
                                                     uint16_t  padding_x_right,
                                                     uint16_t  stride_x,
#ifndef PROFILE
                                                     uint16_t  stride_y);
#else
                                                     uint16_t  stride_y,
                                                     uint32_t *im2col_cycles,
                                                     uint32_t *hotloop_prep_cycles,
                                                     uint32_t *hotloop_cycles,
                                                     uint32_t *threshold_cycles,
                                                     uint32_t *hotloop_leftover_cycles,
                                                     uint32_t *matmul4x2_leftover_cycles);
#endif
#endif
