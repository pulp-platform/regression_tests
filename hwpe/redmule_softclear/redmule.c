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
 * RedMulE SW test
 */

#include <stdint.h>
#include "stdio.h"
#include "archi_redmule.h"
#include "hal_redmule.h"
#include "pulp.h"

static inline void wait_cycles(const unsigned cycles)
{
  /**
   * Each iteration of the loop below will take four cycles on RI5CY (one for
   * `addi` and three for the taken `bnez`; if the instructions hit in the
   * I$).  Thus, we let `i` count the number of remaining loop iterations and
   * initialize it to a fourth of the number of clock cyles.  With this
   * initialization, we must not enter the loop if the number of clock cycles
   * is less than four, because this will cause an underflow on the first
   * subtraction.
   */
  register unsigned threshold;
  asm volatile("li %[threshold], 4" : [threshold] "=r" (threshold));
  asm volatile goto("ble %[cycles], %[threshold], %l2"
          : /* no output */
          : [cycles] "r" (cycles), [threshold] "r" (threshold)
          : /* no clobbers */
          : __wait_cycles_end);
  register unsigned i = cycles >> 2;
__wait_cycles_start:
  // Decrement `i` and loop if it is not yet zero.
  asm volatile("addi %0, %0, -1" : "+r" (i));
  asm volatile goto("bnez %0, %l1"
          : /* no output */
          : "r" (i)
          : /* no clobbers */
          : __wait_cycles_start);
__wait_cycles_end:
  return;
}

int main() {

  volatile int errors = 0;
  unsigned int cluster_id = rt_cluster_id();
  unsigned int intc_data_correctable_cnt, redmule_data_correctable_cnt = 0;
  unsigned int intc_meta_correctable_cnt = 0;
  unsigned int intc_data_uncorrectable_cnt, redmule_data_uncorrectable_cnt = 0;
  unsigned int intc_meta_uncorrectable_cnt = 0;

  if(get_core_id() == 0){

    uint16_t m_size = M_SIZE;
    uint16_t n_size = N_SIZE;
    uint16_t k_size = K_SIZE;

    uint8_t *x_ext = x_inp;
    uint8_t *w_ext = w_inp;
    uint8_t *y_ext = y_inp;
    uint8_t *z_ext = z_oup;

    uint8_t volatile *x = (uint8_t volatile *) pi_l1_malloc(0, (2*m_size*n_size));
    uint8_t volatile *w = (uint8_t volatile *) pi_l1_malloc(0, (2*n_size*k_size));
    uint8_t volatile *y = (uint8_t volatile *) pi_l1_malloc(0, (2*m_size*k_size));
    uint8_t volatile *z = (uint8_t volatile *) pi_l1_malloc(0, (2*m_size*k_size));

    #ifdef USE_DMA
      volatile unsigned int dma_id = 0;
      dma_id = mchan_alloc();
      mchan_transfer((unsigned int) 2*(2*m_size*n_size),
                     (unsigned int) x_ext,
                     (unsigned int) x    );
      mchan_barrier(dma_id);
      mchan_free(dma_id);
    
      dma_id = mchan_alloc();
      mchan_transfer((unsigned int) 2*(2*n_size*k_size),
                     (unsigned int) w_ext,
                     (unsigned int) w    );
      mchan_barrier(dma_id);
      mchan_free(dma_id);
    
      dma_id = mchan_alloc();
      mchan_transfer((unsigned int) 2*(2*m_size*k_size),
                     (unsigned int) y_ext,
                     (unsigned int) y    );
      mchan_barrier(dma_id);
    #else
      generate_test_data16((int) x, (int) w, (int) y, (int) m_size, (int) n_size, (int) k_size);
    #endif

    int gold_sum = 0, check_sum = 0;
    int i,j;

    int offload_id_tmp, offload_id;

    // Enable RedMulE
    hwpe_cg_enable();
    asm volatile("": : :"memory");

    hwpe_soft_clear();
    asm volatile("": : :"memory");

    volatile int job_id = -1;

    // job 0
    job_id = hwpe_wait_acquire();
    asm volatile("": : :"memory");
    redmule_x_add_set ((unsigned int) x);
    redmule_w_add_set ((unsigned int) w);
    redmule_y_add_set ((unsigned int) y);
    redmule_z_add_set ((unsigned int) z);
    redmule_cfg (m_size, n_size, k_size, gemm_ops);
    asm volatile("": : :"memory");
    hwpe_trigger_job();
    asm volatile("": : :"memory");

    // job 1
    job_id = hwpe_wait_acquire();
    asm volatile("": : :"memory");
    redmule_x_add_set ((unsigned int) x);
    redmule_w_add_set ((unsigned int) w);
    redmule_y_add_set ((unsigned int) y);
    redmule_z_add_set ((unsigned int) z);
    redmule_cfg (m_size, n_size, k_size, gemm_ops);
    asm volatile("": : :"memory");
    hwpe_trigger_job();
    asm volatile("": : :"memory");

    // soft-clear execution
    wait_cycles(20);
    hwpe_soft_clear();
    wait_cycles(100);

    // job 0
    job_id = hwpe_wait_acquire();
    asm volatile("": : :"memory");
    redmule_x_add_set ((unsigned int) x);
    redmule_w_add_set ((unsigned int) w);
    redmule_y_add_set ((unsigned int) y);
    redmule_z_add_set ((unsigned int) z);
    redmule_cfg (m_size, n_size, k_size, gemm_ops);
    asm volatile("": : :"memory");
    hwpe_trigger_job();
    asm volatile("": : :"memory");

    // Wait for end of computation
    redmule_evt_wait();

    // Disable RedMulE
    hwpe_cg_disable();

    errors = redmule_compare16((int) z, (int) m_size, (int) k_size);

    *(int *) 0x1A1040A0 = errors;

    if(job_id != 0) {
      printf ("Terminated test with wrong job id!!! and %d errors. See you!\n", errors);
      errors++;
    }
    else {
      printf ("Terminated test with OK job id and %d errors. See you!\n", errors);
    }

  }
  synch_barrier();
  return (errors != 0);
}
