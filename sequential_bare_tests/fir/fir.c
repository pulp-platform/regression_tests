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
#include "../common.h"

void fir16(const int16_t *arr, const int16_t *coeff, int16_t *output,
         unsigned arr_length, unsigned coeff_len) {

  for (unsigned i = 0; i < arr_length - coeff_len; i++) {
    uint16_t sum = 0;
    for (unsigned j = 0; j < coeff_len; j++) {
      sum += arr[i+j] * coeff[j];
    }

    output[i] = sum;
  }
}

void fir8(const int8_t *arr, const int8_t *coeff, int16_t *output,
         unsigned arr_length, unsigned coeff_len) {

  for (unsigned i = 0; i < arr_length - coeff_len; i++) {
    uint16_t sum = 0;
    for (unsigned j = 0; j < coeff_len; j++) {
      sum += arr[i+j] * coeff[j];
    }

    output[i] = sum;
  }
}

#if DOTP==1
#define SumDotp16(a, b, c) __builtin_pulp_sdotsp2(a, b, c)
#define Dotp16(a, b)       __builtin_pulp_dotsp2(a, b)

typedef signed short FiltsV __attribute__((vector_size (4)));

void fir16_dotp(const int16_t *arr, const int16_t *coeff, int16_t *output,
         unsigned arr_length, unsigned coeff_len) {

  FiltsV* VectA;
  FiltsV* VectC;

  for (unsigned i = 0; i < arr_length - coeff_len; i++) {
    uint32_t sum = 0;
    VectA = (FiltsV*)(&arr[i]);
    VectC = (FiltsV*)(&coeff[0]);
    for (unsigned j = 0; j < coeff_len/2; j++) {
      sum = SumDotp16(VectA[j], VectC[j], sum);
    }
    output[i] = (uint16_t)sum;
  }
}

#define SumDotp8(a, b, c) __builtin_pulp_sdotsp4(a, b, c)
#define Dotp8(a, b)       __builtin_pulp_dotsp4(a, b)

typedef signed char FiltcV __attribute__((vector_size (4)));

void fir8_dotp(const int8_t *arr, const int8_t *coeff, int16_t *output,
         unsigned arr_length, unsigned coeff_len) {

  FiltcV* VectA;
  FiltcV* VectC;

  for (unsigned i = 0; i < arr_length - coeff_len; i++) {
    uint32_t sum = 0;
    VectA = (FiltcV*)(&arr[i]);
    VectC = (FiltcV*)(&coeff[0]);
    for (unsigned j = 0; j < coeff_len/4; j++) {
      sum = SumDotp8(VectA[j], VectC[j], sum);
    }
    output[i] = (uint16_t)sum;
  }
}

#endif
