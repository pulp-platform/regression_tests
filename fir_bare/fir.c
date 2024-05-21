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
#include "common.h"

void fir16(const int16_t *arr, const int16_t *coeff, int16_t *output,
         unsigned arr_length, unsigned coeff_len) {

  for (unsigned i = 0; i < arr_length - coeff_len; i++) {
    int sum = 0;
    for (unsigned j = 0; j < coeff_len; j++) {
      sum += arr[i+j] * coeff[j];
      printf("%04x,%04x,%08x\n", arr[i+j], coeff[j], sum);
    }

    // doesn't make much sense...
    output[i] = (int16_t) (sum & 0xffff);
    printf("%04x\n", output[i]);
  }
}

void fir8(const int8_t *arr, const int8_t *coeff, int16_t *output,
         unsigned arr_length, unsigned coeff_len) {

  for (unsigned i = 0; i < arr_length - coeff_len; i++) {
    int sum = 0;
    for (unsigned j = 0; j < coeff_len; j++) {
      sum += arr[i+j] * coeff[j];
    }

    output[i] = (int8_t) (sum & 0xffff);
  }
}

