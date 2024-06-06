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

static inline void fir16_unroll6x2_inner(
  const int16_t *arr,
  const int16_t *coeff0,
  int16_t       *coeff_buffer,
  int32_t       *buffer,
  unsigned      arr_len,
  int           j
) {

  // marshal coeff_buffer (coefficients "shifted" by one elemnt + padding)
  coeff_buffer[0] = 0;
  for(int k=1; k<13; k++) {
    coeff_buffer[k] = coeff0[j+k-1];
  }
  coeff_buffer[13] = 0;

  // load coefficients into FIR XIFU
  volatile int *pcoeff0 = (volatile int *) &coeff0[j];
  pcoeff0 = __builtin_xfir_lw(16, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(17, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(18, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(19, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(20, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(21, (int *) pcoeff0, 4);
  volatile int *pcoeff1 = (volatile int *) &coeff_buffer[0];
  pcoeff1 = __builtin_xfir_lw(22, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(23, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(24, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(25, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(26, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(27, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(28, (int *) pcoeff1, 4);

  // loop strip-mined on output dimension
  int nb_stripmine_iter     = arr_len / 2;
  int nb_stripmine_leftover = arr_len % 2;
  for (int i=0; i<nb_stripmine_iter; i++) {

    // pointers to temp buffer
    volatile int *psum0 = (volatile int *) &buffer[2*i];
    volatile int *psum1 = (volatile int *) &buffer[2*i+1];

    // load accumulator into FIR XIFU
    psum0 = __builtin_xfir_lw(0, (int *) psum0, 0);
    psum1 = __builtin_xfir_lw(1, (int *) psum1, 0);

    // load arrays
    volatile int *parr = (volatile int *) &arr[j+2*i];

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

    // store temporary
    psum0 = __builtin_xfir_sw((int *) psum0, 0, 0, 0);
    psum1 = __builtin_xfir_sw((int *) psum1, 1, 0, 0);
    
  }
  // leftover on output dimension
  for (int i=nb_stripmine_iter*2; i<arr_len; i++) {

    // pointers to temp buffer
    volatile int *psum0 = (volatile int *) &buffer[i];

    // load accumulator into FIR XIFU
    psum0 = __builtin_xfir_lw(0, (int *) psum0, 0);

    // fully reload arrays (for now)
    volatile int *parr = (volatile int *) &arr[j+i];

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

  }

}

static inline void fir16_unroll8x2_inner(
  const int16_t *arr,
  const int16_t *coeff0,
  int16_t       *coeff_buffer,
  int32_t       *buffer,
  unsigned      arr_len,
  int           j
) {

  // marshal coeff_buffer (coefficients "shifted" by one elemnt + padding)
  coeff_buffer[0] = 0;
  for(int k=1; k<17; k++) {
    coeff_buffer[k] = coeff0[j+k-1];
  }
  coeff_buffer[17] = 0;

  // load coefficients into FIR XIFU
  volatile int *pcoeff0 = (volatile int *) &coeff0[j];
  pcoeff0 = __builtin_xfir_lw(15, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(16, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(17, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(18, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(19, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(20, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(21, (int *) pcoeff0, 4);
  pcoeff0 = __builtin_xfir_lw(22, (int *) pcoeff0, 4);
  volatile int *pcoeff1 = (volatile int *) &coeff_buffer[0];
  pcoeff1 = __builtin_xfir_lw(23, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(24, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(25, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(26, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(27, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(28, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(29, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(30, (int *) pcoeff1, 4);
  pcoeff1 = __builtin_xfir_lw(31, (int *) pcoeff1, 4);

  // loop strip-mined on output dimension
  int nb_stripmine_iter     = arr_len / 2;
  int nb_stripmine_leftover = arr_len % 2;
  for (int i=0; i<nb_stripmine_iter; i++) {

    // pointers to temp buffer
    volatile int *psum0 = (volatile int *) &buffer[2*i];
    volatile int *psum1 = (volatile int *) &buffer[2*i+1];

    // load accumulator into FIR XIFU
    psum0 = __builtin_xfir_lw(0, (int *) psum0, 0);
    psum1 = __builtin_xfir_lw(1, (int *) psum1, 0);

    // load arrays
    volatile int *parr = (volatile int *) &arr[j+2*i];

    // load all array elements
    parr = __builtin_xfir_lw(2,  (int *) parr, 4);
    parr = __builtin_xfir_lw(3,  (int *) parr, 4);
    parr = __builtin_xfir_lw(4,  (int *) parr, 4);
    parr = __builtin_xfir_lw(5,  (int *) parr, 4);
    parr = __builtin_xfir_lw(6,  (int *) parr, 4);
    parr = __builtin_xfir_lw(7,  (int *) parr, 4);
    parr = __builtin_xfir_lw(8,  (int *) parr, 4);
    parr = __builtin_xfir_lw(9,  (int *) parr, 4);
    parr = __builtin_xfir_lw(10, (int *) parr, 4);

    // perform all dot-products
    __builtin_xfir_dotp(0, 2,  15);
    __builtin_xfir_dotp(0, 3,  16);
    __builtin_xfir_dotp(0, 4,  17);
    __builtin_xfir_dotp(0, 5,  18);
    __builtin_xfir_dotp(0, 6,  19);
    __builtin_xfir_dotp(0, 7,  20);
    __builtin_xfir_dotp(0, 8,  21);
    __builtin_xfir_dotp(0, 9,  22);
    __builtin_xfir_dotp(1, 2,  23);
    __builtin_xfir_dotp(1, 3,  24);
    __builtin_xfir_dotp(1, 4,  25);
    __builtin_xfir_dotp(1, 5,  26);
    __builtin_xfir_dotp(1, 6,  27);
    __builtin_xfir_dotp(1, 7,  28);
    __builtin_xfir_dotp(1, 8,  29);
    __builtin_xfir_dotp(1, 9,  30);
    __builtin_xfir_dotp(1, 10, 31);

    // store temporary
    psum0 = __builtin_xfir_sw((int *) psum0, 0, 0, 0);
    psum1 = __builtin_xfir_sw((int *) psum1, 1, 0, 0);
    
  }
  // leftover on output dimension
  for (int i=nb_stripmine_iter*2; i<arr_len; i++) {

    // pointers to temp buffer
    volatile int *psum0 = (volatile int *) &buffer[i];

    // load accumulator into FIR XIFU
    psum0 = __builtin_xfir_lw(0, (int *) psum0, 0);

    // fully reload arrays (for now)
    volatile int *parr = (volatile int *) &arr[j+i];

    // load all array elements
    parr = __builtin_xfir_lw(2,  (int *) parr, 4);
    parr = __builtin_xfir_lw(3,  (int *) parr, 4);
    parr = __builtin_xfir_lw(4,  (int *) parr, 4);
    parr = __builtin_xfir_lw(5,  (int *) parr, 4);
    parr = __builtin_xfir_lw(6,  (int *) parr, 4);
    parr = __builtin_xfir_lw(7,  (int *) parr, 4);
    parr = __builtin_xfir_lw(8,  (int *) parr, 4);
    parr = __builtin_xfir_lw(9,  (int *) parr, 4);
    // perform all dot-products
    __builtin_xfir_dotp(0, 2, 16);
    __builtin_xfir_dotp(0, 3, 17);
    __builtin_xfir_dotp(0, 4, 18);
    __builtin_xfir_dotp(0, 5, 19);
    __builtin_xfir_dotp(0, 6, 20);
    __builtin_xfir_dotp(0, 7, 21);
    __builtin_xfir_dotp(0, 9, 22);

    // store result
    psum0 = __builtin_xfir_sw((int *) psum0, 0, 0, 0);

  }

}


void fir16_unroll6x2(
  const int16_t *arr,
  const int16_t *coeff0,
  int16_t       *coeff_buffer,
  int32_t       *buffer,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
) {

  // loop strip-mined on coefficient dimension
  int nb_stripmine_coeff_iter     = coeff_len / 12;
  int nb_stripmine_coeff_leftover = coeff_len % 12 > 0 ? 1 : 0;
  for (int j=0; j<nb_stripmine_coeff_iter; j++) {
    // call inner
    fir16_unroll6x2_inner(arr, coeff0, coeff_buffer, buffer, arr_len, j*12);
  }
  
  if (nb_stripmine_coeff_leftover) {
    // call inner
    fir16_unroll6x2_inner(arr, coeff0, coeff_buffer, buffer, arr_len, nb_stripmine_coeff_iter*12);
  }

  // process outputs
  for (int i=0; i<arr_len; i++) {
    output[i] = (int16_t) ((buffer[i] >> right_shift) & 0xffff);
  }

}


void fir16_unroll8x2(
  const int16_t *arr,
  const int16_t *coeff0,
  int16_t       *coeff_buffer,
  int32_t       *buffer,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
) {

  // loop strip-mined on coefficient dimension
  int nb_stripmine_coeff_iter     = coeff_len / 16;
  int nb_stripmine_coeff_leftover = coeff_len % 16 > 0 ? 1 : 0;
  for (int j=0; j<nb_stripmine_coeff_iter; j++) {
    // call inner
    fir16_unroll8x2_inner(arr, coeff0, coeff_buffer, buffer, arr_len, j*16);
  }
  
  if (nb_stripmine_coeff_leftover) {
    // call inner
    fir16_unroll8x2_inner(arr, coeff0, coeff_buffer, buffer, arr_len, nb_stripmine_coeff_iter*16);
  }

  // process outputs
  for (int i=0; i<arr_len; i++) {
    output[i] = (int16_t) ((buffer[i] >> right_shift) & 0xffff);
  }

}

