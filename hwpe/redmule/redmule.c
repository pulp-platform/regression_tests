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

    hwpe_soft_clear();

    // redmule_cfg ((unsigned int) x,
    //              (unsigned int) w,
    //              (unsigned int) y,
    //              m_size, n_size, k_size,
    //              (uint8_t) GEMM,
    //              (uint8_t) Float16);
    redmule_x_add_set ((unsigned int) x);
    redmule_w_add_set ((unsigned int) w);
    redmule_y_add_set ((unsigned int) y);
    redmule_z_add_set ((unsigned int) y);
    redmule_cfg (m_size, n_size, k_size, gemm_ops);

    // Start RedMulE operation
    hwpe_trigger_job();

    // Wait for end of computation
    redmule_evt_wait();

    // Check number of detected errors by ECC modules inside RedMulE
    redmule_data_correctable_cnt = redmule_get_data_correctable_count();
    redmule_data_uncorrectable_cnt = redmule_get_data_uncorrectable_count();

    // Disable RedMulE
    hwpe_cg_disable();

    errors = redmule_compare16((int) y, (int) m_size, (int) k_size);

    *(int *) 0x1A1040A0 = errors;

    printf ("Terminated test with %d errors. See you!\n", errors);

    // Check number of detected errors by ECC modules inside interconnect
    intc_data_correctable_cnt = hwpe_hci_ecc_get_data_correctable_count(cluster_id);
    intc_meta_correctable_cnt = hwpe_hci_ecc_get_meta_correctable_count(cluster_id);
    intc_data_uncorrectable_cnt = hwpe_hci_ecc_get_data_uncorrectable_count(cluster_id);
    intc_meta_uncorrectable_cnt = hwpe_hci_ecc_get_meta_uncorrectable_count(cluster_id);
    for (int i = 0; i < 16; i++) {
      intc_meta_correctable_cnt += tcdm_scrubber_get_mismatch_count(cluster_id, i);
    }

    printf ("Data errors corrected inside RedMulE: %d. Data errors uncorrectable inside RedMulE: %d \n",
      redmule_data_correctable_cnt, redmule_data_uncorrectable_cnt);
    printf("Data errors corrected inside intc: %d. Data errors uncorrectable inside intc: %d\n",
      intc_data_correctable_cnt, intc_data_uncorrectable_cnt);
    printf("Meta errors corrected inside intc: %d. Meta errors uncorrectable inside intc: %d\n",
      intc_meta_correctable_cnt, intc_meta_uncorrectable_cnt);


  }
  synch_barrier();
  return (errors != 0) && (redmule_data_uncorrectable_cnt==0 && intc_data_uncorrectable_cnt == 0 && intc_meta_uncorrectable_cnt == 0);
}
