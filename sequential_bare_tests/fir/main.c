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

/* 
 * Mantainer: Luca Valente, luca.valente2@unibo.it
 */
#include <stdio.h>
#include "pulp.h"

#ifndef RV_ISA_RV32
  #define NUM_ITER 5
  #warning "NUM_ITER equal to 5"
#else
  #define NUM_ITER 1
  #warning "NUM_ITER equal to 1"
#endif

static unsigned samples[NUM_ITER];

extern void test_setup();
extern void test_clear();
extern void test_run(int);
extern int test_check();

// this function can be redefined in each test to return a proper string
const char* __attribute__((weak)) get_testname()
{
  return "Undefined";
}

int main() {

  printf("(%d %d) %s %d\n", rt_cluster_id(), rt_core_id(), __FILE__, __LINE__);

  int cid = get_core_id();

  printf("(%d %d) %s %d\n", rt_cluster_id(), rt_core_id(), __FILE__, __LINE__);

#if ARCHI_HAS_CLUSTER
  synch_barrier();
#endif

  printf("(%d %d) %s %d\n", rt_cluster_id(), rt_core_id(), __FILE__, __LINE__);

  if (cid == 0) {

  printf("(%d %d) %s %d\n", rt_cluster_id(), rt_core_id(), __FILE__, __LINE__);
    
    plp_power_init();
    test_setup();
    perf_reset();

  printf("(%d %d) %s %d\n", rt_cluster_id(), rt_core_id(), __FILE__, __LINE__);

    for (int i = 0; i < NUM_ITER; ++i) {
      test_clear();

      reset_timer();
      start_timer();

      if (i==NUM_ITER-1) plp_power_start();

      perf_start();

      test_run(i);

      perf_stop();

      if (i==NUM_ITER-1) plp_power_stop();

      stop_timer();

      samples[i] = get_time();
    }

    int check = test_check();

    printf("Correct: %d\n", check);
    for (int i = 0; i < NUM_ITER; ++i)
      printf("TS[%d]: %d\n", i, samples[i]);

    if (check == 1)
      printf("== test: %s -> success, nr. of errors: %d, execution time: %d\n", get_testname(), 0, samples[0]);
    else
      printf("== test: %s -> fail, nr. of errors: %d, execution time: %d\n", get_testname(), 1, samples[0]);
    
    perf_print_all();

    if (check)
      return 0;
    else
      return 1;
  }

  printf("(%d %d) %s %d\n", rt_cluster_id(), rt_core_id(), __FILE__, __LINE__);

  return 0;
}
