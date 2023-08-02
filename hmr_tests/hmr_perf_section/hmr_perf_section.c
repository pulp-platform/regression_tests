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
#include <stdio.h>

void test_func() {
  printf("In performance section: %u\n", core_id());
  return;
}

int main() {

  if (rt_cluster_id() != 0) {

    printf("indiv. available: %x\nDMR available:    %x\nTMR available:    %x\nRapidRecovery av: %x\n",
      hmr_get_available_config(0) & 0x1,
      (hmr_get_available_config(0) & 0x2) >> 0x1,
      (hmr_get_available_config(0) & 0x4) >> 0x2,
      (hmr_get_available_config(0) & 1<<8) >> 8 );

    // printf("%x\n", hmr_reg[1]);

    printf("before setup: %x\n", hmr_get_active_cores(0));
    hmr_enable_all_tmr(0);
    // hmr_enable_all_dmr(0);
    hmr_set_dmr_config_all(0, true); // with rapid recovery
    // hmr_set_dmr_config_all(0, false); // no rapid recovery
    // hmr_set_tmr_config_all(0,  false, true, true, true, false); // setback, with rapid recovery
    hmr_set_tmr_config_all(0,  false, true, true, false, false); // setback, no rapid recovery
    printf("after setup: %x\n", hmr_get_active_cores(0));
    // hmr_disable_all_tmr(0);

    // hmr_tmr_barrier_setup_all();

    // rt_irq_set_handler(24, pos_hmr_tmr_irq);
    // rt_irq_set_handler(23, pos_hmr_tmr_synch);


    return bench_cluster_forward(0);
  }

  hmr_tmr_perf_setup_sp();


  printf("%u is here\n", core_id());


  for (int i = 0; i < 200; i++) {
    __asm__ __volatile__("nop");
  }


  if (core_id() == 0) {
    hmr_tmr_performance_section(test_func);
  }


  for (int i = 0; i < 2000; i++) {
    __asm__ __volatile__("nop");
  }

  eu_bar_trig_wait_clr(eu_bar_addr(0));

  printf("%u passed barrier 1\n", core_id());

  for (int i = 0; i < 200; i++) {
    __asm__ __volatile__("nop");
  }



  if (core_id() == 0) {
    hmr_tmr_performance_section(test_func);
  }


  for (int i = 0; i < 2000; i++) {
    __asm__ __volatile__("nop");
  }

  eu_bar_trig_wait_clr(eu_bar_addr(0));



  printf("%u passed barrier 2\n", core_id());


  return 0;


}
