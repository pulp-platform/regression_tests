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
 * Michael Rogenmoser <michaero@iis.ee.ethz.ch>
 */
#include <pulp.h>

// #define ARCHI_HMR_OFFSET 0x2000
// #define ARCHI_HMR_ADDR ( ARCHI_CLUSTER_PERIPHERALS_GLOBAL_ADDR(0) + ARCHI_HMR_OFFSET )

int tmr_test_func() {
  printf("In TMR critical section: %u\n", core_id());
  return 0;
}

int dmr_test_func() {
  printf("In DMR critical section: %u\n", core_id());
  return 0;
}


int main() {

  // uint32_t *hmr_reg = ARCHI_HMR_ADDR;

  // printf("%x\n", *hmr_reg);
  printf("MTVEC CSR: %x\n", hal_spr_read(0x305));

  if (rt_cluster_id() != 0) {

    printf("indiv. available: %x\nDMR available:    %x\nTMR available:    %x\nRapidRecovery av: %x\n",
      hmr_get_available_config(0) & 0x1,
      (hmr_get_available_config(0) & 0x2) >> 0x1,
      (hmr_get_available_config(0) & 0x4) >> 0x2,
      (hmr_get_available_config(0) & 1<<8) >> 8 );

    // printf("%x\n", hmr_reg[1]);

    printf("before setup: %x\n", hmr_get_active_cores(0));
    // hmr_enable_all_tmr(0);
    // hmr_enable_all_dmr(0);
    hmr_set_dmr_config_all(0, true); // with rapid recovery
    // hmr_set_dmr_config_all(0, false); // no rapid recovery
    hmr_set_tmr_config_all(0,  false, true, true, true); // setback, with rapid recovery
    // hmr_set_tmr_config_all(0,  false, true, true, false); // setback, no rapid recovery
    printf("after setup: %x\n", hmr_get_active_cores(0));
    // hmr_disable_all_tmr(0);

    // hmr_tmr_barrier_setup_all();

    // rt_irq_set_handler(24, pos_hmr_tmr_irq);
    // rt_irq_set_handler(23, pos_hmr_tmr_synch);


    return bench_cluster_forward(0);
  }

  // hal_irq_enable();

  // hal_spr_write(0x304, 1<<24|1<<23);

  int nbErrors = 0;//run_suite(testcases);

  printf("%u is here\n", core_id());


  for (int i = 0; i < 200; i++) {
    __asm__ __volatile__("nop");
  }


  if (core_id() == 1) {
    hmr_tmr_critical_section(tmr_test_func);
  
    // hmr_dmr_critical_section(dmr_test_func);
  }
  // if (core_id() == 1) {

  // }

  // if (core_id() == 1) {
  //   // enter critical section
  //   hmr_enable_tmr(0, 1);

  //   // do critical stuff


  //   // exit critical section

  // }

  for (int i = 0; i < 2000; i++) {
    __asm__ __volatile__("nop");
  }

  eu_bar_trig_wait_clr(eu_bar_addr(0));

  printf("%u passed barrier 1\n", core_id());

  for (int i = 0; i < 200; i++) {
    __asm__ __volatile__("nop");
  }

  if (core_id() == 1) {
    hmr_tmr_critical_section(tmr_test_func);
    // hmr_dmr_critical_section(dmr_test_func);
  }
  for (int i = 0; i < 2000; i++) {
    __asm__ __volatile__("nop");
  }

  eu_bar_trig_wait_clr(eu_bar_addr(0));
  // if (CORE_IN_TMR(core_id())) {
  //   lkasjdf;kasjdf
  // }

  printf("%u passed barrier 2\n", core_id());

  return nbErrors != 0;
}
