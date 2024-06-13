#ifndef __XPULP_TNN_LINEAR_TERNARY_I32_SIGNED_H
#define __XPULP_TNN_LINEAR_TERNARY_I32_SIGNED_H

void __attribute__((noinline)) xpulp_tnn_linear_ternary_i32_signed(
                   int8_t *pIn,
                   int8_t *pBias,
                   int8_t *pOut,
                   int8_t *pWeight,
                   uint16_t dim_vec,
                   uint16_t num_o_neurons);

#endif