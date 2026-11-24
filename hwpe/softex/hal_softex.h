/*
 * Andrea Belano <andrea.belano@studio.unibo.it>
 *
 * Copyright 2024 ETH Zurich and University of Bologna
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

#ifndef __HAL_SOFTEX__
#define __HAL_SOFTEX__

#include <pulp.h>
#include "archi_softex.h"

#define HWPE_WRITE(value, offset) *(volatile int *)(SOFTEX_BASE_ADD + offset) = value
#define HWPE_READ(offset) *(volatile int *)(SOFTEX_BASE_ADD + offset)

static inline void hwpe_trigger_job() {
    HWPE_WRITE(0, SOFTEX_TRIGGER);
}

static inline int hwpe_acquire_job() {
    return HWPE_READ(SOFTEX_ACQUIRE);
}

static inline unsigned int hwpe_get_status() {
    return HWPE_READ(SOFTEX_STATUS);
}

static inline void hwpe_soft_clear() {
  HWPE_WRITE(0, SOFTEX_SOFT_CLEAR);
}

static inline void hwpe_cg_enable() {
  *(volatile int*) (ARCHI_CLUST_CTRL_BASE + CLUST_CTRL_HWPE_EN) |= (CLUST_CTRL_HWPE_EN_MASK | SOFTEX_CG_EN_MSK);
}

static inline void hwpe_cg_disable() {
  *(volatile int*) (ARCHI_CLUST_CTRL_BASE + CLUST_CTRL_HWPE_EN) &= ~(CLUST_CTRL_HWPE_EN_MASK | SOFTEX_CG_EN_MSK);
}

static inline void softex_evt_wait() {
  do {
    eu_evt_maskWaitAndClr (1 << ARCHI_CL_HWPE_EVT0);
  } while((*(int volatile *)(ARCHI_CLUST_HWPE_BASE + SOFTEX_STATUS)) != 0);
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

#endif