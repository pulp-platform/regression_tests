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
 * RedMulE Hardware Abstraction Layer (HAL)
 */

#ifndef __HAL_REDMULE_H__
#define __HAL_REDMULE_H__

#include <pulp.h>
#include "inc/x_input.h"
#include "inc/w_input.h"
#include "inc/y_input.h"
#include "inc/z_output.h"
#include "inc/golden.h"
#include "inc/tensor_dim.h"

/*
 * 
 * For control, generic configuration register layout,
 * and job-dependent register map, look at redmule_archi.h
 *
 */

// For all the following functions we use __builtin_pulp_OffsetedWrite and __builtin_pulp_OffsetedRead
// instead of classic load/store because otherwise the compiler is not able to correctly factorize
// the HWPE base in case several accesses are done, ending up with twice more code

#define HWPE_WRITE(value, offset) *(volatile int *)(ARCHI_CLUST_HWPE_BASE + offset) = value
#define HWPE_READ(offset) *(volatile int *)(ARCHI_CLUST_HWPE_BASE + offset)

static inline void redmule_x_add_set (unsigned int value) {
  HWPE_WRITE(value, REDMULE_REG_OFFS + REDMULE_REG_X_PTR);
}

static inline void redmule_w_add_set (unsigned int value) {
  HWPE_WRITE(value, REDMULE_REG_OFFS + REDMULE_REG_W_PTR);
}

static inline void redmule_z_add_set (unsigned int value) {
  HWPE_WRITE(value, REDMULE_REG_OFFS + REDMULE_REG_Z_PTR);
}

static inline void redmule_mcfg_set (uint32_t mcfg0, uint32_t mcfg1) {
  HWPE_WRITE(mcfg0, REDMULE_REG_OFFS + REDMULE_MCFG0_PTR);
  HWPE_WRITE(mcfg1, REDMULE_REG_OFFS + REDMULE_MCFG1_PTR);
}

static inline void redmule_arith_set(uint32_t arith) {
  HWPE_WRITE(arith, REDMULE_REG_OFFS + REDMULE_ARITH_PTR);
}

static inline void hwpe_trigger_job() {
  HWPE_WRITE(0, REDMULE_TRIGGER);
}

static inline int hwpe_acquire_job() {
  return HWPE_READ(REDMULE_ACQUIRE);
}

static inline unsigned int hwpe_get_status() {
  return HWPE_READ(REDMULE_STATUS);
}

static inline unsigned int hwpe_get_running_job() {
  return HWPE_READ(REDMULE_RUNNING_JOB);
}

static inline void hwpe_soft_clear() {
  HWPE_WRITE(0, REDMULE_SOFT_CLEAR);
}

static inline void hwpe_cg_enable() {
  *(volatile int*) (ARCHI_CLUST_CTRL_BASE + CLUST_CTRL_HWPE_EN) |= CLUST_CTRL_HWPE_EN_MASK;
}

static inline void hwpe_cg_disable() {
  *(volatile int*) (ARCHI_CLUST_CTRL_BASE + CLUST_CTRL_HWPE_EN) &= ~CLUST_CTRL_HWPE_EN_MASK;
}

static inline void redmule_evt_wait() {
  do {
    eu_evt_maskWaitAndClr (1 << ARCHI_CL_HWPE_EVT0);
  } while((*(int volatile *)(ARCHI_CLUST_HWPE_BASE + REDMULE_STATUS)) != 0);
}

static inline int hwpe_wait_acquire() {
  int job_id = hwpe_acquire_job();
  while(job_id < 0) {
    eu_evt_maskWaitAndClr (1 << ARCHI_CL_HWPE_EVT0);
    job_id = hwpe_acquire_job();
  }
  return job_id;
}

static inline unsigned int redmule_get_data_correctable_count () {
  return HWPE_READ(REDMULE_ECC_REG_OFFS + DATA_CORR_ERR);
}

static inline unsigned int redmule_get_data_uncorrectable_count () {
  return HWPE_READ(REDMULE_ECC_REG_OFFS + DATA_UNCORR_ERR);
}

static inline unsigned int redmule_get_meta_correctable_count () {
  return HWPE_READ(REDMULE_ECC_REG_OFFS + METADATA_CORR_ERR);
}

static inline unsigned int redmule_get_meta_uncorrectable_count () {
  return HWPE_READ(REDMULE_ECC_REG_OFFS + METADATA_UNCORR_ERR);
}

/* DMA APIs */
static inline int mchan_alloc(){
  return *(volatile int*) DMA_COMMAND_QUEUE;
}

static inline void mchan_transfer(unsigned int len,
                                  unsigned int ext_addr,
                                  unsigned int tcdm_addr) {

  *(volatile int*) DMA_COMMAND_QUEUE = len |
                                       (DMA_RX << PLP_DMA_TYPE_BIT)  |
                                       (DMA_INC << PLP_DMA_INCR_BIT) |
                                       (0 << PLP_DMA_2D_BIT)         |
                                       (1 << PLP_DMA_ELE_BIT)        |
                                       (1 << PLP_DMA_ILE_BIT)        |
                                       (0 << PLP_DMA_BLE_BIT)        |
                                       (0 << PLP_DMA_2D_TCDM_BIT);
  *(volatile int*) DMA_COMMAND_QUEUE = tcdm_addr;
  *(volatile int*) DMA_COMMAND_QUEUE = ext_addr;
}

static inline void mchan_barrier(int id) {
  while(((*(volatile int*)(DMA_STATUS_REGISTER)) >> id ) & 0x1 ) {
    eu_evt_maskWaitAndClr(1 << FC_DMA_EVENT);
 }
}

static inline void mchan_free(int id) {
  *(volatile int*) DMA_STATUS_REGISTER = 0x1 << id;
}

void redmule_cfg(unsigned int x, unsigned int w, unsigned int z, uint16_t m_size, uint16_t n_size,
  uint16_t k_size, uint8_t gemm_op, uint8_t gemm_fmt) {

  uint32_t mcfg_reg0 = 0;
  uint32_t mcfg_reg1 = 0;
  uint32_t arith_reg = 0;

  mcfg_reg0 = (k_size << 16) | (m_size << 0);
  mcfg_reg1 = n_size << 0;

  arith_reg = (gemm_op << 10) | (gemm_fmt << 7);

  redmule_x_add_set((unsigned int)x);
  redmule_w_add_set((unsigned int)w);
  redmule_z_add_set((unsigned int)z);
  redmule_mcfg_set((unsigned int)mcfg_reg0, (unsigned int)mcfg_reg1);
  redmule_arith_set((unsigned int)arith_reg);
}

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

    if ( z_computed != z_oup[z/2] ) err++;
  }

  return err;

}

int redmule16_compare_int(uint32_t *actual_z, uint32_t *golden_z, int len) {
  #define ERR 0x0000
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
