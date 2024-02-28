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

#include <pulp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 0x400
#define NUM_BANKS 16
#define SCRUBBER_INTERVAL 2

int main() {
  // Collecting info about the core ID and the running cluster ID
  unsigned int core_id = get_core_id();
  unsigned int cluster_id = rt_cluster_id();

  if (rt_cluster_id() != 0) return bench_cluster_forward(0);

  if (core_id != 0) synch_barrier();

  unsigned int *test_array = pi_l1_malloc(cluster_id, SIZE);

  // Initializing the memory
  for (int i = 0; i < SIZE; i++) {
    pulp_write32(&test_array[i], i);
  }

  // Initialize the scrubbing interval for all memory banks
  for (int i = 0; i < NUM_BANKS; i++)
    tcdm_scrubber_set_interval(cluster_id, i, SCRUBBER_INTERVAL);

  // Initialize the error-tracking variables
  bool  mismatch = 0;
  unsigned int error = 0;
  for (int i = 0; i < SIZE; i++) {
    mismatch = (pulp_read32(&test_array[i]) != i);
    if (mismatch) {
      error ++;
      printf("Expected 0x%x, got 0x%x\n", i, pulp_read32(&test_array[i]));
    }
  }

  return error;

}
