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

// factor of 12 = 6 registers with 2 elems each per type (6 arr + 6 coeff)
#define UNROLLING_FACTOR 12

void fir16_unroll6(const int16_t *arr, const int16_t *coeff, int16_t *output,
         unsigned arr_length, unsigned coeff_len) {
          
  // coefficients are fully reused
  int *pcoeff = (int *) &coeff[0];
  pcoeff = __builtin_xfir_lw(16, pcoeff, 4);
  pcoeff = __builtin_xfir_lw(17, pcoeff, 4);
  pcoeff = __builtin_xfir_lw(18, pcoeff, 4);
  pcoeff = __builtin_xfir_lw(19, pcoeff, 4);
  pcoeff = __builtin_xfir_lw(20, pcoeff, 4);
  pcoeff = __builtin_xfir_lw(21, pcoeff, 4);

  for (unsigned i = 0; i < arr_length - coeff_len; i++) {
    int sum = 0;
    int *psum = &sum;

    // load accumulator into FIR XIFU
    psum = __builtin_xfir_lw(0, psum, 0);

    // fully reload arrays (for now)
    int *parr = (int *) &arr[i];

    // fully unrolled loop
    {
      // load all array elements
      parr = __builtin_xfir_lw(1,  parr, 4);
      parr = __builtin_xfir_lw(2,  parr, 4);
      parr = __builtin_xfir_lw(3,  parr, 4);
      parr = __builtin_xfir_lw(4,  parr, 4);
      parr = __builtin_xfir_lw(5,  parr, 4);
      parr = __builtin_xfir_lw(6,  parr, 4);
      // perform all dot-products
      __builtin_xfir_dotp(0, 1, 16);
      __builtin_xfir_dotp(0, 2, 17);
      __builtin_xfir_dotp(0, 3, 18);
      __builtin_xfir_dotp(0, 4, 19);
      __builtin_xfir_dotp(0, 5, 20);
      __builtin_xfir_dotp(0, 6, 21);
    }
    // store result
    psum = __builtin_xfir_sw(psum, 0, 0, 0);

    output[i] = (int16_t) (sum & 0xffff);
  }
}

void fir16_unroll6x2(const int16_t *arr, const int16_t *coeff, const int16_t *coeff1, int16_t *output,
         unsigned arr_length, unsigned coeff_len) {
          
  // coefficients are fully reused
  volatile int *pcoeff0 = (volatile int *) &coeff[0];
  pcoeff0 = __builtin_xfir_lw(16, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(17, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(18, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(19, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(20, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(21, (int *) pcoeff0, 4);
  volatile int *pcoeff1 = (volatile int *) &coeff1[0];
  pcoeff1 = __builtin_xfir_lw(22, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(23, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(24, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(25, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(26, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(27, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(28, (int *) pcoeff1, 4);

  // loop strip-mined on output dimension
  int nb_stripmine_iter     = (arr_length - coeff_len) / 2;
  int nb_stripmine_leftover = (arr_length - coeff_len) % 2;
  for (int i=0; i<nb_stripmine_iter; i++) {
    int sum0 = 0;
    int sum1 = 0;
    volatile int *psum0 = (volatile int *) &sum0;
    volatile int *psum1 = (volatile int *) &sum1;

    // load accumulator into FIR XIFU
    psum0 = __builtin_xfir_lw(0, (int *) psum0, 0);
    psum1 = __builtin_xfir_lw(1, (int *) psum1, 0);

    // fully reload arrays (for now)
    volatile int *parr = (volatile int *) &arr[2*i];

    // load all array elements
    parr = __builtin_xfir_lw(2, (int *) parr, 4);
    parr = __builtin_xfir_lw(3, (int *) parr, 4);
    parr = __builtin_xfir_lw(4, (int *) parr, 4);
    parr = __builtin_xfir_lw(5, (int *) parr, 4);
    parr = __builtin_xfir_lw(6, (int *) parr, 4);
    parr = __builtin_xfir_lw(7, (int *) parr, 4);
    parr = __builtin_xfir_lw(8, (int *) parr, 4);
    // perform all dot-products
    __builtin_xfir_dotp(0, 2, 16);
    __builtin_xfir_dotp(0, 3, 17);
    __builtin_xfir_dotp(0, 4, 18);
    __builtin_xfir_dotp(0, 5, 19);
    __builtin_xfir_dotp(0, 6, 20);
    __builtin_xfir_dotp(0, 7, 21);
    __builtin_xfir_dotp(1, 2, 22);
    __builtin_xfir_dotp(1, 3, 23);
    __builtin_xfir_dotp(1, 4, 24);
    __builtin_xfir_dotp(1, 5, 25);
    __builtin_xfir_dotp(1, 6, 26);
    __builtin_xfir_dotp(1, 7, 27);
    __builtin_xfir_dotp(1, 8, 28);

    // store result
    psum0 = __builtin_xfir_sw((int *) psum0, 0, 0, 0);
    psum1 = __builtin_xfir_sw((int *) psum1, 1, 0, 0);

    output[2*i]   = (int16_t) (sum0 & 0xffff);
    output[2*i+1] = (int16_t) (sum1 & 0xffff);
  }
  // leftover
  for (int i=nb_stripmine_iter*2; i<arr_length - coeff_len; i++) {
    int sum0 = 0;
    volatile int *psum0 = (volatile int *) &sum0;

    // load accumulator into FIR XIFU
    psum0 = __builtin_xfir_lw(0, (int *) psum0, 0);

    // fully reload arrays (for now)
    volatile int *parr = (volatile int *) &arr[i];

    // load all array elements
    parr = __builtin_xfir_lw(2, (int *) parr, 4);
    parr = __builtin_xfir_lw(3, (int *) parr, 4);
    parr = __builtin_xfir_lw(4, (int *) parr, 4);
    parr = __builtin_xfir_lw(5, (int *) parr, 4);
    parr = __builtin_xfir_lw(6, (int *) parr, 4);
    parr = __builtin_xfir_lw(7, (int *) parr, 4);
    parr = __builtin_xfir_lw(8, (int *) parr, 4);
    // perform all dot-products
    __builtin_xfir_dotp(0, 2, 16);
    __builtin_xfir_dotp(0, 3, 17);
    __builtin_xfir_dotp(0, 4, 18);
    __builtin_xfir_dotp(0, 5, 19);
    __builtin_xfir_dotp(0, 6, 20);
    __builtin_xfir_dotp(0, 7, 21);

    // store result
    psum0 = __builtin_xfir_sw((int *) psum0, 0, 0, 0);

    output[i] = (int16_t) (sum0 & 0xffff);
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

