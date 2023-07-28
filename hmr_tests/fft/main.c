/*
 * Copyright (C) 2023 ETH Zurich and University of Bologna
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
 * Michael Rogenmoser <michaero@iis.ee.ethz.ch>
 */
#include <pulp.h>
#include "plp_math.h"
#include "plp_const_structs.h"
#include "cfft_data.h"

__attribute__ ((section(".heapsram"))) int16_t p1[2*256];

int main() {

  if (rt_cluster_id() != 0) {
    // Setup HMR


    return bench_cluster_forward(0);
  }

  int unsigned num_errors = 0;
  int unsigned num_cores = 3;//hmr_get_active_cores(0);

  if (core_id() == 0) {
    // Copy data to p1
    for (int i = 0; i < 2*256; i++) {
      p1[i] = p1_init[i];
    }
    printf("Executing on %d cores\n", num_cores);

    // Set up barrier correctly
    eu_bar_setup(eu_bar_addr(0), (1<<num_cores) - 1);
  }
  

  if (core_id() < num_cores) {
    perf_reset();
    synch_barrier();
    perf_start();
    // Execute FFT
    plp_cfft_instance_q16_parallel args = {
      .S              = &plp_cfft_sR_q16_len256, 
      .p1             = p1,         /* Source/destination vector */
      .ifftFlag       = 0,          /* forward (not inverse)     */
      .bitReverseFlag = 1,          /* Do bitreversal            */
      .deciPoint      = 0,          /* deciPoint not used        */
      .nPE            = num_cores}; /* nPE                       */


    plp_cfft_q16p_xpulpv2((void*)&args);
    synch_barrier();
    perf_stop();

    perf_print_all();
  } else {
    return 0;
  }
  if (core_id() == 0) {
    // stop timer
    // Compare result with expected outcome
    for (int i = 0; i < 2*256; i++) {
      if (!((p1[i] >= p1_result[i] - 31) &&
            (p1[i] <= p1_result[i] + 31))) {
        num_errors++;
      printf("Mismatch at %d: got %d, exp %d\n", i, p1[i], p1_result[i]);
      }
    }
    if (num_errors == 0) {
      printf("SUCCESS\n");
    } else {
      printf("Num Errors: %d\n", num_errors);
    }
    return num_errors;
  } else {
    return 0;
  }


}
