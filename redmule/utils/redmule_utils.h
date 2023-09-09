/*
 * Copyright (C) 2022-2023 ETH Zurich and University of Bologna
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
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Author: Yvan Tortorella  <yvan.tortorella@unibo.it>
 *
 */

#include "../inc/x_input.h"
#include "../inc/w_input.h"
#include "../inc/y_input.h"
#include "../inc/z_output.h"

#ifndef REDMULE_UTILS_H
#define REDMULE_UTILS_H

void generate_test_data16(int x_start_addr,
                          int w_start_addr,
                          int y_start_addr,
                          int m_size,
                          int n_size,
                          int k_size) {
  
  int x_addr     = x_start_addr;
  int w_addr     = w_start_addr;
  int y_addr     = y_start_addr;
  int x_end_addr = x_start_addr + (2*m_size*n_size);
  int w_end_addr = w_start_addr + (2*n_size*k_size);
  int y_end_addr = y_start_addr + (2*m_size*k_size);

  // Generating input stimuli from golden model
  for (x_addr = x_start_addr; x_addr < x_end_addr; x_addr += 2) {
    int x = x_addr - x_start_addr;
    *(uint32_t *)(x_addr) = x_inp[x/2];
  }

  // Generating Weight stimuli from golden model
  for (w_addr = w_start_addr; w_addr < w_end_addr; w_addr += 2) {
    int w = w_addr - w_start_addr;
    *(uint32_t *)(w_addr) = w_inp[w/2];
  }

  for (y_addr = y_start_addr; y_addr < y_end_addr; y_addr += 2) {
    int y = y_addr - y_start_addr;
    *(uint32_t *)(y_addr) = y_inp[y/2];
  }
}

int redmule_compare16 (int z_start_addr, int m_size, int k_size) {
  int err = 0;
  int z_end_addr = z_start_addr + 2*m_size*k_size;
  uint16_t z_computed;
  uint16_t diff, diff_1, diff_2;

  for (int z_addr = z_start_addr; z_addr < z_end_addr; z_addr += 2) {
    int z = z_addr - z_start_addr;
    z_computed = *(uint32_t *)(z_addr);

    if ( z_computed != z_oup[z/2] ) {
      diff_1 = z_computed - z_oup[z/2];
      if (diff_1 > 3) {
        diff_2 = z_oup[z/2] - z_computed;
        if (diff_2 > 3) {
          err++;
        }
      }
    }
  }

  return err;

}

int redmule16_compare_int(uint32_t *actual_z, uint32_t *golden_z, int len) {
  #define ERR 0x0011
  uint32_t actual_word = 0;
  uint16_t actual_MSHWord, actual_LSHWord;
  uint32_t golden_word = 0;
  uint16_t golden_MSHWord, golden_LSHWord;
  uint32_t actual = 0;
  uint32_t golden = 0;

  int errors = 0;
  int error;

  for (int i=0; i<len; i++) {
    error = 0;
    actual_word = *(actual_z+i);
    golden_word = *(golden_z+i);

    // int error = ((actual_word ^ golden_word) & ~IGNORE_BITS_COMPARE) ? 1 : 0;
    uint16_t diff = 0;
    
    // Chechink Least Significant Half-Word
    actual_LSHWord = (uint16_t)(actual_word & 0x0000FFFF);
    golden_LSHWord = (uint16_t)(golden_word & 0x0000FFFF);

    diff = (actual_LSHWord > golden_LSHWord) ? (actual_LSHWord - golden_LSHWord) : 0;
    diff = (actual_LSHWord < golden_LSHWord) ? (golden_LSHWord - actual_LSHWord) : 0;

    if (diff > ERR) {
      error = 1;
      #ifdef VERBOSE
        tfp_printf ("diff: 0x%08x\n", diff);
        tfp_printf ("LSW: Error!\n");
      #endif
    }

    // Checking Most Significant Half-Word
    actual_MSHWord = (uint16_t)((actual_word >> 16) & 0x0000FFFF);
    golden_MSHWord = (uint16_t)((golden_word >> 16) & 0x0000FFFF);

    diff = (actual_MSHWord > golden_MSHWord) ? (actual_MSHWord - golden_MSHWord) : 0;
    diff = (actual_MSHWord < golden_MSHWord) ? (golden_MSHWord - actual_MSHWord) : 0;

    if (diff > ERR) {
      error = 1;
      #ifdef VERBOSE
        tfp_printf ("diff: 0x%08x\n", diff);
        tfp_printf ("MSW: Error!\n");
      #endif
    }
    
    errors += error;

    #ifdef DEBUG
      tfp_printf("  Golden: 0x%08x; Actual: 0x%08x,\n", golden_word, actual_word);
    #endif

    #ifdef VERBOSE
    if(error) {
        if(errors==1) tfp_printf("  golden     <- actual     @ address    @ index\n");
        tfp_printf("  0x%08x <- 0x%08x @ 0x%08x @ 0x%08x\n", golden_word, actual_word, (actual_z+i), i*4);
    }
    #endif
  }
  return errors;
}

int redmule8_compare_int(uint32_t *actual_z, uint32_t *golden_z, int len) {
  #define ERR 0x0011
  uint32_t actual_word = 0;
  uint8_t  actual_Byte0,
           actual_Byte1,
           actual_Byte2,
           actual_Byte3;
  uint32_t golden_word = 0;
  uint8_t  golden_Byte0,
           golden_Byte1,
           golden_Byte2,
           golden_Byte3;
  uint32_t actual = 0;
  uint32_t golden = 0;

  int errors = 0;
  int error;

  for (int i=0; i<len; i++) {
    error = 0;
    actual_word = *(actual_z+i);
    golden_word = *(golden_z+i);

    // int error = ((actual_word ^ golden_word) & ~IGNORE_BITS_COMPARE) ? 1 : 0;
    uint8_t diff = 0;
    
    // Cheching Byte0
    actual_Byte0 = (uint8_t)(actual_word & 0x000000FF);
    golden_Byte0 = (uint8_t)(golden_word & 0x000000FF);

    diff = (actual_Byte0 > golden_Byte0) ? (actual_Byte0 - golden_Byte0) : 0;
    diff = (actual_Byte0 < golden_Byte0) ? (golden_Byte0 - actual_Byte0) : 0;

    if (diff > ERR) {
      error = 1;
      tfp_printf ("diff: 0x%08x\n", diff);
      tfp_printf ("Byte0: Error!\n");
    }

    // Cheching Byte1
    actual_Byte1 = (uint8_t)( (actual_word >> 8 ) & 0x000000FF);
    golden_Byte1 = (uint8_t)( (golden_word >> 8 ) & 0x000000FF);

    diff = (actual_Byte1 > golden_Byte1) ? (actual_Byte1 - golden_Byte1) : 0;
    diff = (actual_Byte1 < golden_Byte1) ? (golden_Byte1 - actual_Byte1) : 0;

    if (diff > ERR) {
      error = 1;
      tfp_printf ("diff: 0x%08x\n", diff);
      tfp_printf ("Byte1: Error!\n");
    }

    // Cheching Byte2
    actual_Byte2 = (uint8_t)( (actual_word >> 16 ) & 0x000000FF);
    golden_Byte2 = (uint8_t)( (golden_word >> 16 ) & 0x000000FF);

    diff = (actual_Byte2 > golden_Byte2) ? (actual_Byte2 - golden_Byte2) : 0;
    diff = (actual_Byte2 < golden_Byte2) ? (golden_Byte2 - actual_Byte2) : 0;

    if (diff > ERR) {
      error = 1;
      tfp_printf ("diff: 0x%08x\n", diff);
      tfp_printf ("Byte2: Error!\n");
    }

    // Cheching Byte3
    actual_Byte3 = (uint8_t)( (actual_word >> 24 ) & 0x000000FF);
    golden_Byte3 = (uint8_t)( (golden_word >> 24 ) & 0x000000FF);

    diff = (actual_Byte3 > golden_Byte3) ? (actual_Byte3 - golden_Byte3) : 0;
    diff = (actual_Byte3 < golden_Byte3) ? (golden_Byte3 - actual_Byte3) : 0;

    if (diff > ERR) {
      error = 1;
      tfp_printf ("diff: 0x%08x\n", diff);
      tfp_printf ("Byte3: Error!\n");
    }
    
    errors += error;

    #ifdef DEBUG
      tfp_printf("  Golden: 0x%08x; Actual: 0x%08x,\n", golden_word, actual_word);
    #endif

    #ifdef VERBOSE
      if(error) {
        if(errors==1) tfp_printf("  golden     <- actual     @ address    @ index\n");
        tfp_printf("  0x%08x <- 0x%08x @ 0x%08x @ 0x%08x\n", golden_word, actual_word, (actual_z+i), i*4);
      }
    #endif
  }
  return errors;
}

#endif
