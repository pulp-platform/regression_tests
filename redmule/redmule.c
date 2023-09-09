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
#include "utils/redmule_utils.h"
#include "archi_redmule.h"
#include "hal_redmule.h"

// #include "inc/x_input.h"
// #include "inc/w_input.h"
// #include "inc/y_input.h"
// #include "inc/z_output.h"
#include "inc/golden.h"

int main() {

  volatile int errors = 0;

  if(get_core_id() == 0){
    uint16_t m_size = M_SIZE;
    uint16_t n_size = N_SIZE;
    uint16_t k_size = K_SIZE;

    uint8_t volatile *x = (uint8_t volatile *) pi_l1_malloc(0, (2*m_size*n_size));
    uint8_t volatile *w = (uint8_t volatile *) pi_l1_malloc(0, (2*n_size*k_size));
    uint8_t volatile *y = (uint8_t volatile *) pi_l1_malloc(0, (2*m_size*k_size));

    generate_test_data16((int) x, (int) w, (int) y, (int) m_size, (int) n_size, (int) k_size);

    int gold_sum = 0, check_sum = 0;
    int i,j;

    int offload_id_tmp, offload_id;

    // Enable RedMulE
    hwpe_cg_enable();

    hwpe_soft_clear();

    // while( ( offload_id_tmp = hwpe_acquire_job() ) < 0);

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

    // Disable RedMulE
    hwpe_cg_disable();

    errors = redmule_compare16((int) y, (int) m_size, (int) k_size);

    *(int *) 0x1A1040A0 = errors;

    printf ("Terminated test with %d errors. See you!\n", errors);

  }
  synch_barrier();
  return errors;
}
