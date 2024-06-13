#ifndef __XPULP_TNN_MAXPOOL_TERNARY_H
#define __XPULP_TNN_MAXPOOL_TERNARY_H
void __attribute__ ((noinline)) xpulp_tnn_maxpool_ternary(
                                                          int8_t * pIn,
                                                          int8_t * pOut,
                                                          uint16_t  dim_im_in_x,
                                                          uint16_t  dim_im_in_y,
                                                          // ch_im_in: UNCOMPRESSED number of input/output channels
                                                          uint16_t  ch_im_in,
                                                          uint16_t  dim_im_out_x,
                                                          uint16_t  dim_im_out_y,
                                                          uint16_t  dim_kernel_x,
                                                          uint16_t  dim_kernel_y,
                                                          uint16_t  padding_t,
                                                          uint16_t  padding_b,
                                                          uint16_t  padding_l,
                                                          uint16_t  padding_r,
                                                          uint16_t  stride_x,
                                                          uint16_t  stride_y);
#endif
