/*
 * Luka Macan <luka.macan@unibo.it>
 *
 * Copyright 2023 ETH Zurich and University of Bologna
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __NEUREKA_TASK_H__
#define __NEUREKA_TASK_H__

#include "neureka_task_defs.h"
#include <stdint.h>

typedef enum neureka_task_flag_e {
  neurekaTaskFlagFalse = 0,
  neurekaTaskFlagTrue = 1
} neureka_task_flag_e;

typedef enum neureka_weight_source_e {
  neurekaWeightSourceTcdm = NEUREKA_FLAG_WEIGHT_SOURCE_TCDM,
  neurekaWeightSourceWmem = NEUREKA_FLAG_WEIGHT_SOURCE_WMEM
} neureka_weight_source_e;

typedef enum neureka_weight_offset_mode_e {
  weightOffsetModeSymmetric = NEUREKA_FLAG_WEIGHT_OFFSET_SYMMETRIC,
  weightOffsetModeLayerWise = NEUREKA_FLAG_WEIGHT_OFFSET_LAYER_WISE
} neureka_weight_offset_mode_e;

typedef enum neureka_activation_prefetch_e {
  activationPrefetchOn  = NEUREKA_FLAG_ACTIVATION_PREFETCH_ON,
  activationPrefetchOff = NEUREKA_FLAG_ACTIVATION_PREFETCH_OFF
} neureka_activation_prefetch_e;

typedef enum {
  normMode8Bit = NEUREKA_NORM_MODE_8BIT,
  normMode32Bit = NEUREKA_NORM_MODE_32BIT
} neureka_norm_mode_e;

typedef struct neureka_norm_t {
  neureka_norm_mode_e mode;
  neureka_task_flag_e flag_bias;
  neureka_task_flag_e flag_shift;
} neureka_norm_t;

typedef enum neureka_quant_mode_e {
  quantMode8Bit = NEUREKA_QUANT_MODE_8BIT,
  quantMode32Bit = NEUREKA_QUANT_MODE_32BIT
} neureka_quant_mode_e;

typedef enum neureka_quant_function_e {
  quantFunctionIdentity = NEUREKA_FLAG_QUANT_FUNCTION_IDENTITY,
  quantFunctionRelu = NEUREKA_FLAG_QUANT_FUNCTION_RELU
} neureka_quant_function_e;

typedef struct neureka_quant_t {
  // Shift amount must be in range 0x00-0x1F
  uint8_t shift_amount;
  neureka_quant_function_e function;
  neureka_task_flag_e flag_rounding;
} neureka_quant_t;

typedef struct neureka_stride_t {
  uint32_t d0;
  uint32_t d1;
  uint32_t d2;
} neureka_stride_t;

typedef struct neureka_subtile_remainder_t {
  uint32_t KoKi;
  uint32_t HoWo;
  uint32_t HiWi;
} neureka_subtile_remainder_t;

typedef struct neureka_subtile_number_t {
  uint32_t KoKi;
  uint32_t HoWo;
} neureka_subtile_number_t;

typedef struct neureka_subtile_t {
  neureka_subtile_remainder_t remainder;
  neureka_subtile_number_t number;
} neureka_subtile_t;

typedef struct neureka_cfg_t {
  neureka_stride_t input_stride;
  neureka_stride_t output_stride;
  neureka_stride_t weights_stride;
  neureka_subtile_t subtile;
  uint32_t padding;
  uint32_t weight_offset_factor;
  uint32_t filter_mask;
  uint32_t conf0;
} neureka_cfg_t;

typedef struct neureka_task_data_t {
  uint32_t weights_ptr;
  uint32_t infeat_ptr;
  uint32_t outfeat_ptr;
  uint32_t scale_ptr;
  uint32_t scale_shift_ptr;
  uint32_t scale_bias_ptr;
  neureka_cfg_t cfg;
} neureka_task_data_t;

typedef struct neureka_task_t {
  neureka_task_data_t data;
  uint8_t qw;
  uint8_t subtile_output_channel;
  uint8_t subtile_input_channel;
  uint8_t kernel_shape;
  uint8_t depthwise;
  uint8_t id;
} neureka_task_t;

void neureka_task_init(neureka_task_t *task);
void neureka_task_set_op_to_conv(neureka_task_t *task,
                                 const uint8_t kernel_shape,
                                 const uint8_t depthwise);
void neureka_task_set_bits(neureka_task_t *task, const uint8_t input_bits,
                           const uint8_t output_bits,
                           const uint8_t weight_bits);
void neureka_task_set_norm_quant(neureka_task_t *task, neureka_quant_t quant,
                                 neureka_norm_t norm);
void neureka_task_set_weight_offset(
    neureka_task_t *task, neureka_weight_offset_mode_e weight_offset_mode,
    const int32_t weight_offset);
void neureka_task_set_input_signed(neureka_task_t *task);
void neureka_task_set_input_unsigned(neureka_task_t *task);
void neureka_task_set_weight_source(neureka_task_t *task,
                                    neureka_weight_source_e weight_source);
uint32_t neureka_get_tile_padding(uint32_t padding, uint32_t i_height,
                                  uint32_t i_width, uint32_t n_height,
                                  uint32_t n_width);
uint32_t neureka_pad_ptr(uint32_t ptr, const uint32_t width,
                         const uint32_t width_stride, const uint8_t padding_top,
                         const uint8_t padding_left);
void neureka_task_set_ptrs_conv(neureka_task_t *task, uint32_t input_ptr,
                                uint32_t w_in, uint32_t w_in_stride,
                                uint8_t padding_top, uint8_t padding_left,
                                uint32_t output_ptr, uint32_t weights_ptr);
void neureka_task_set_ptrs_norm_quant(neureka_task_t *task, uint32_t scale_ptr,
                                      uint32_t shift_ptr, uint32_t bias_ptr);
/** neureka_task_set_strides
 *
 * All the strides variables are strides between elements alongside that
 * dimension and expressed in bytes. There is no stride variable for the channel
 * dimension because the N-EUREKA requires the channels to be contiguous.
 */
void neureka_task_set_strides(neureka_task_t *task, const uint32_t k_in,
                              const uint32_t h_in_stride,
                              const uint32_t w_in_stride,
                              const uint32_t h_out_stride,
                              const uint32_t w_out_stride);
void neureka_task_set_counters(neureka_task_t *task, const uint32_t k_in,
                               const uint32_t h_out, const uint32_t w_out,
                               const uint32_t k_out,
                               const uint8_t padding_bottom,
                               const uint8_t padding_right);
void neureka_task_set_padding(neureka_task_t *task, const uint8_t top,
                              const uint8_t bottom, const uint8_t left,
                              const uint8_t right, const uint8_t value);
void neureka_task_set_mask_filter(neureka_task_t *task, const uint8_t top,
                                  const uint8_t bottom, const uint8_t left,
                                  const uint8_t right);
/** neureka_task_set_dims
 *
 * All the strides variables are strides between elements alongside that
 * dimension and expressed in bytes. There is no stride variable for the channel
 * dimension because the N-EUREKA requires the channels to be contiguous.
 */
void neureka_task_set_dims(
    neureka_task_t *task, const uint32_t w_in, const uint32_t k_in,
    const uint32_t h_in_stride, const uint32_t w_in_stride,
    const uint32_t h_out, const uint32_t w_out, const uint32_t k_out,
    const uint32_t h_out_stride, const uint32_t w_out_stride,
    const uint8_t padding_top, const uint8_t padding_bottom,
    const uint8_t padding_left, const uint8_t padding_right);

#endif // !__NEUREKA_TASK_H__
