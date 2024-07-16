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

#include "neureka_task.h"
#include "neureka_task_defs.h"
#include "pulp_nnx_util.h"

uint32_t neureka_get_tile_padding(uint32_t padding, uint32_t i_height,
                                  uint32_t i_width, uint32_t n_height,
                                  uint32_t n_width) {
  uint32_t tile_padding = padding;
  if (i_height > 0) {
    tile_padding &= ~(0xf << 28);
  }
  if (i_width < n_width - 1) {
    tile_padding &= ~(0xf << 24);
  }
  if (i_height < n_height - 1) {
    tile_padding &= ~(0xf << 20);
  }
  if (i_width > 0) {
    tile_padding &= ~(0xf << 16);
  }
  return tile_padding;
}

void neureka_task_init(neureka_task_t *task) {
  *task = (neureka_task_t){.data = {0}};
}

void neureka_task_set_op_to_conv(neureka_task_t *task,
                                 const uint8_t kernel_shape,
                                 const uint8_t depthwise) {
  task->depthwise = depthwise;
  task->kernel_shape = kernel_shape;
  task->subtile_output_channel = depthwise ? NEUREKA_SUBTILE_INPUT_CHANNEL_3x3
                                           : NEUREKA_SUBTILE_OUTPUT_CHANNEL;
  task->subtile_input_channel = kernel_shape == 3
                                    ? NEUREKA_SUBTILE_INPUT_CHANNEL_3x3
                                    : NEUREKA_SUBTILE_INPUT_CHANNEL_1x1;

  const int flag_mode = kernel_shape == 1 ? NEUREKA_FLAG_MODE_1x1
                        : depthwise == 1  ? NEUREKA_FLAG_MODE_3x3_DW
                                          : NEUREKA_FLAG_MODE_3x3;

  task->data.cfg.conf0 &= ~(NEUREKA_MASK_FLAG_MODE);
  task->data.cfg.conf0 |= flag_mode;
}

void neureka_task_set_bits(neureka_task_t *task, const uint8_t input_bits,
                           const uint8_t output_bits,
                           const uint8_t weight_bits) {
  neureka_quant_mode_e quantMode;
  if (output_bits == 8) {
    quantMode = quantMode8Bit;
  } else {
    quantMode = quantMode32Bit;
  }

  task->qw = weight_bits;
  task->data.cfg.conf0 &=
      ~(NEUREKA_MASK_QUANT_MODE | NEUREKA_MASK_FLAG_WEIGHT_BITS);
  task->data.cfg.conf0 |= quantMode | (weight_bits - 1);
}

void neureka_task_set_norm_quant(neureka_task_t *task, neureka_quant_t quant,
                                 neureka_norm_t norm) {
  task->data.cfg.conf0 &=
      ~(NEUREKA_MASK_QUANT_FUNCTION | NEUREKA_MASK_SHIFT_AMOUNT |
        NEUREKA_MASK_NORM_MODE | NEUREKA_MASK_FLAG_NORM_BIAS |
        NEUREKA_MASK_FLAG_NORM_SHIFT);
  task->data.cfg.conf0 |= NEUREKA_FLAG_NORM_QUANT | quant.function |
                          (quant.shift_amount << 16) | norm.mode |
                          norm.flag_bias << NEUREKA_SHIFT_FLAG_NORM_BIAS |
                          norm.flag_shift << NEUREKA_SHIFT_FLAG_NORM_SHIFT;
}

void neureka_task_set_weight_offset(
    neureka_task_t *task, neureka_weight_offset_mode_e weight_offset_mode,
    const int32_t weight_offset) {
  task->data.cfg.conf0 &= ~NEUREKA_MASK_WEIGHT_OFFSET_MODE;
  task->data.cfg.conf0 |= weight_offset_mode;
  task->data.cfg.weight_offset_factor = weight_offset;
}

void neureka_task_set_input_signed(neureka_task_t *task) {
  task->data.cfg.conf0 |= NEUREKA_FLAG_INPUT_SIGNED;
}

void neureka_task_set_input_unsigned(neureka_task_t *task) {
  task->data.cfg.conf0 &= ~NEUREKA_FLAG_INPUT_SIGNED;
}

void neureka_task_set_weight_source(neureka_task_t *task,
                                    neureka_weight_source_e weight_source) {
  task->data.cfg.conf0 &= ~NEUREKA_MASK_FLAG_WEIGHT_SOURCE;
  task->data.cfg.conf0 |= weight_source;
}

void neureka_task_set_activation_prefetch(neureka_task_t *task,
                                    neureka_activation_prefetch_e activation_prefetch) {
  task->data.cfg.conf0 &= ~NEUREKA_MASK_FLAG_ACTIVATION_PREFETCH;
  task->data.cfg.conf0 |= activation_prefetch;
}

/** neureka_pad_ptr
 *
 * Calculate the pointer to the start of the ptr as if
 * it was the start to the padded data.
 * Necessary for input pointer when it's padded.
 */
uint32_t neureka_pad_ptr(uint32_t ptr, const uint32_t width,
                         const uint32_t width_stride, const uint8_t padding_top,
                         const uint8_t padding_left) {
  return ptr - (padding_top * width + padding_left) * width_stride;
}

void neureka_task_set_ptrs_conv(neureka_task_t *task, uint32_t input_ptr,
                                uint32_t w_in, uint32_t w_in_stride,
                                uint8_t padding_top, uint8_t padding_left,
                                uint32_t output_ptr, uint32_t weights_ptr) {
  task->data.infeat_ptr =
      neureka_pad_ptr(input_ptr, w_in, w_in_stride, padding_top, padding_left);
  task->data.outfeat_ptr = output_ptr;
  task->data.weights_ptr = weights_ptr;
}

void neureka_task_set_ptrs_norm_quant(neureka_task_t *task, uint32_t scale_ptr,
                                      uint32_t shift_ptr, uint32_t bias_ptr) {
  task->data.scale_ptr = scale_ptr;
  task->data.scale_shift_ptr = shift_ptr;
  task->data.scale_bias_ptr = bias_ptr;
}

void neureka_task_set_strides(neureka_task_t *task, const uint32_t k_in,
                              const uint32_t h_in_stride,
                              const uint32_t w_in_stride,
                              const uint32_t h_out_stride,
                              const uint32_t w_out_stride) {
  const uint32_t num_k_in =
      nnx_calculate_number_of_tiles(k_in, task->subtile_input_channel);

  const neureka_stride_t input_stride = {
      .d0 = w_in_stride, .d1 = h_in_stride, .d2 = 0};
  task->data.cfg.input_stride = input_stride;

  const neureka_stride_t output_stride = {.d0 = NEUREKA_OUTPUT_BANDWIDTH_BYTES,
                                          .d1 = w_out_stride,
                                          .d2 = h_out_stride};
  task->data.cfg.output_stride = output_stride;

  if (task->kernel_shape == 1) { // 1x1
    task->data.cfg.weights_stride.d0 = NEUREKA_WEIGHT_BANDWIDTH_BYTES_1x1;
    task->data.cfg.weights_stride.d1 =
        NEUREKA_WEIGHT_BANDWIDTH_BYTES_1x1 * num_k_in;
  } else if (!task->depthwise) { // 3x3
    task->data.cfg.weights_stride.d0 = NEUREKA_WEIGHT_BANDWIDTH_BYTES_3x3;
    task->data.cfg.weights_stride.d1 =
        NEUREKA_WEIGHT_BANDWIDTH_BYTES_3x3 * task->qw * num_k_in;
  } else { // 3x3 depthwise
    task->data.cfg.weights_stride.d0 = NEUREKA_WEIGHT_BANDWIDTH_BYTES_3x3;
    task->data.cfg.weights_stride.d1 = 0;
  }
  task->data.cfg.weights_stride.d2 = 0;
}

void neureka_task_set_counters(neureka_task_t *task, const uint32_t k_in,
                               const uint32_t h_out, const uint32_t w_out,
                               const uint32_t k_out,
                               const uint8_t padding_bottom,
                               const uint8_t padding_right) {
  const uint16_t num_Ko =
      nnx_calculate_number_of_tiles(k_out, task->subtile_output_channel);
  const uint16_t num_Ki =
      nnx_calculate_number_of_tiles(k_in, task->subtile_input_channel);
  const uint16_t num_Ho =
      nnx_calculate_number_of_tiles(h_out, NEUREKA_SUBTILE_OUTPUT_HEIGHT);
  const uint16_t num_Wo =
      nnx_calculate_number_of_tiles(w_out, NEUREKA_SUBTILE_OUTPUT_WIDTH);

  const uint16_t rem_Ko =
      nnx_calculate_last_tile_size(k_out, task->subtile_output_channel);
  const uint16_t rem_Ki =
      nnx_calculate_last_tile_size(k_in, task->subtile_input_channel);
  const uint16_t rem_Ho =
      nnx_calculate_last_tile_size(h_out, NEUREKA_SUBTILE_OUTPUT_HEIGHT);
  const uint16_t rem_Wo =
      nnx_calculate_last_tile_size(w_out, NEUREKA_SUBTILE_OUTPUT_WIDTH);
  const uint16_t rem_Hi =
      (task->kernel_shape == 1 ? rem_Ho : rem_Ho + 2) - padding_bottom;
  const uint16_t rem_Wi =
      (task->kernel_shape == 1 ? rem_Wo : rem_Wo + 2) - padding_right;

  const neureka_subtile_t subtile = {
      .number = {.KoKi = nnx_concat_half(num_Ko, num_Ki),
                 .HoWo = nnx_concat_half(num_Ho, num_Wo)},
      .remainder = {.KoKi = nnx_concat_half(rem_Ko, rem_Ki),
                    .HoWo = nnx_concat_half(rem_Ho, rem_Wo),
                    .HiWi = nnx_concat_half(rem_Hi, rem_Wi)}};
  task->data.cfg.subtile = subtile;
}

void neureka_task_set_padding(neureka_task_t *task, const uint8_t top,
                              const uint8_t bottom, const uint8_t left,
                              const uint8_t right, const uint8_t value) {
  task->data.cfg.padding = ((top & 0xf) << 28) | ((right & 0xf) << 24) |
                           ((bottom & 0xf) << 20) | ((left & 0xf) << 16) |
                           (value & 0xff);
}

void neureka_task_set_mask_filter(neureka_task_t *task, const uint8_t top,
                                  const uint8_t bottom, const uint8_t left,
                                  const uint8_t right) {
  task->data.cfg.filter_mask = ((top & 0xff) << 24) | ((right & 0xff) << 16) |
                               ((bottom & 0xff) << 8) | ((left & 0xff) << 0);
}

void neureka_task_set_dims(
    neureka_task_t *task, const uint32_t w_in, const uint32_t k_in,
    const uint32_t h_in_stride, const uint32_t w_in_stride,
    const uint32_t h_out, const uint32_t w_out, const uint32_t k_out,
    const uint32_t h_out_stride, const uint32_t w_out_stride,
    const uint8_t padding_top, const uint8_t padding_bottom,
    const uint8_t padding_left, const uint8_t padding_right) {
  neureka_task_set_strides(task, k_in, h_in_stride, w_in_stride, h_out_stride,
                           w_out_stride);
  neureka_task_set_counters(task, k_in, h_out, w_out, k_out, padding_bottom,
                            padding_right);
  neureka_task_set_padding(task, padding_top, padding_bottom, padding_left,
                           padding_right, 0);
}
