// Copyright 2024 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "pulp.h"
#include "mchan_test.h"

#define SIZE 128

__attribute__ ((section(".heapsram"))) int g_mA[SIZE][SIZE];
__attribute__ ((section(".heapsram"))) uint32_t A_shared;

void generate_transactions(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "interference",          .test = generate_transactions   },
  {0, 0}
};

int main() {

  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  int num_cores = get_core_num();

  bench_disable_printf();

  if(rt_core_id() < num_cores) {
    run_suite(testcases);
  }

  synch_barrier();

  return 0;
}

void generate_transactions(testresult_t *result, void (*start)(), void (*stop)()) {

  int num_cores = get_core_num();
  int cid = rt_core_id();
  unsigned int stride = cid*num_cores;

  unsigned int m, n;
  if(cid==0) {
    A_shared = 0x80000000 + 0x100000;
  }

  synch_barrier();
  start();

  #ifdef USE_MCHAN
  for(int p=0; p<15; p++) {
    n = mchan_alloc();
    mchan_transfer(SIZE*SIZE*4,RX,INC,STRIDED,LIN,1,0,0,(uint32_t)A_shared,(uint32_t)g_mA,8,stride,0,0);
    mchan_barrier(n);
    mchan_free(n);
  }
  #else
  for(int p=0; p<SIZE*2/SIZE;p++) {
    for(int k = 0; k< SIZE; k++) {
      g_mA[k][p] = * ( (uint32_t *) (A_shared + k*SIZE + p + cid*0x80000) );
    }
  }
  #endif

  stop();

  if(num_cores != 1) synch_barrier();

  return 0;
}
