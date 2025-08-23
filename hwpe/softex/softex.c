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

#include <stdint.h>
#include <memory.h>
#include "stdio.h"
#include "archi_softex.h"
#include "hal_softex.h"
#include "pulp.h"

#include "inc/golden.h"
#include "inc/scores.h"

#define TOLERANCE 0x2

uint16_t scores_ext [LENGTH] = SCORES;
uint16_t golden [LENGTH]     = GOLDEN;

int main() {
  volatile int errors = 0;

  uint16_t volatile *scores = (uint16_t volatile *) pi_l1_malloc(0, (FMT_WIDTH*LENGTH));

  if(get_core_id() == 0){
    #ifdef USE_DMA
      volatile unsigned int dma_id = 0;
      dma_id = mchan_alloc();

      mchan_transfer((unsigned int) FMT_WIDTH*LENGTH  ,
                     (unsigned int) scores_ext        ,
                     (unsigned int) scores            
      );

      mchan_barrier(dma_id);
      mchan_free(dma_id);
    #else
      memcpy(scores, scores_ext, LENGTH*FMT_WIDTH);
    #endif

    // Enable softex
    hwpe_cg_enable();

    hwpe_soft_clear();

    HWPE_WRITE(scores, SOFTEX_IN_ADDR);
    HWPE_WRITE(LENGTH * FMT_WIDTH, SOFTEX_TOT_LEN);
    HWPE_WRITE(scores, SOFTEX_OUT_ADDR);

    hwpe_trigger_job();

    softex_evt_wait();

    // Disable softex
    hwpe_cg_disable();

    for (int i = 0; i < LENGTH; i++) {
      uint16_t diff;

      if (golden [i] >= scores[i]) {
        diff = golden [i] - scores [i];
      } else {
        diff = scores [i] - golden [i];
      }

      if (diff > TOLERANCE) {
        errors += 1;
        
        printf ("Mismatch!!!\tIndex: %d\tExpected: 0x%04x\tWas: 0x%04x\tDifference: 0x%x\n", i, golden [i], scores [i], diff);
      }
    }

    *(int *) 0x1A1040A0 = errors;

    printf("Test completed with %d errors\n", errors);
  }
  synch_barrier();
  return errors;
}
