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
#include <stdio.h>
#include <stdint.h>
#include "common.h"

void fir16(
  const int16_t *arr,
  const int16_t *coeff,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
) {
  for (int i=0; i<arr_len; i++) {
    // needs more than 32 bits!
    int64_t sum=0;
    for (int j=0; j<coeff_len; j++) {
      sum += arr[i+j] * coeff[j];
      // printf("%04x * %04x -> %016x\n", arr[i+j], coeff[j], sum);
    }

    // shift accumulator and fit it into 16 bits
    output[i] = (int16_t) ((sum >> right_shift) & 0x000000000000ffff);
    // printf("sum=%08x out=%04x\n", sum, output[i]);
  }
}

