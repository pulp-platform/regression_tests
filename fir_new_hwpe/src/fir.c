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

#include <stdio.h>
#include <stdint.h>
#include "common.h"
#include "fir.h"

void fir16(
  const int16_t *arr,
  const int16_t *coeff,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
) {
  
  int offload_id_tmp, offload_id;

  // acquire job 
  while((offload_id_tmp = fir_acquire_job()) < 0);
  // job-dependent registers
  fir_x_addr_set((unsigned int) arr & 0xFFFFFFFF/* TASK4: Fill the correct address */);
  fir_h_addr_set((unsigned int) coeff & 0xFFFFFFFF/* TASK4: Fill the correct address */);
  fir_y_addr_set((unsigned int) output & 0xFFFFFFFF/* TASK4: Fill the correct address */);
  fir_shift_length_set(right_shift, arr_len); // right_shift, length

  // start hwpe operation
  fir_trigger_job();
  
  // wait for hwpe to finish
  FIR_BUSYWAIT();
}
