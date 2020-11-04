// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.


#include <stdio.h>
#include "pulp.h"

#define N_INTERS 10
#define MASK_CORE8 0xFF

#define SW_EVENT_7  7
#define SW_EVENT_6  6
#define SW_EVENT_5  5
#define SW_EVENT_4  4
#define SW_EVENT_3  3
#define SW_EVENT_2  2
#define SW_EVENT_1  1
#define SW_EVENT_0  0

#define _STOP_READY  SW_EVENT_0
#define _STOP_READ   SW_EVENT_1
#define _DATA_READY  SW_EVENT_2
#define _DATA_READ   SW_EVENT_3

#define CORE_CLKGATE          ARCHI_EU_DEMUX_ADDR + EU_CORE_EVENT_WAIT
#define CORE_CLKGATE_CLRBUFF  ARCHI_EU_DEMUX_ADDR + EU_CORE_EVENT_WAIT_CLEAR
#define CLEAR_BUFF            ARCHI_EU_DEMUX_ADDR + EU_CORE_BUFFER_CLEAR




void check_add(testresult_t *result, void (*start)(), void (*stop)());
void check_hwloop(testresult_t *result, void (*start)(), void (*stop)());
void check_prod_cons(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "add",                  .test = check_add          },
  { .name = "hwloop",               .test = check_hwloop       },
  { .name = "prod_cons",            .test = check_prod_cons    },
  {0, 0}
};

int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  return run_suite(testcases);
}

volatile unsigned int g_irq_counter[8] = {0,0,0,0,0,0,0,0};
volatile unsigned int _data; //critical variable
volatile unsigned int _stop; //critical variable


void check_add(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i, j;
  unsigned int exp;
  unsigned int act;
  int core_id;
  unsigned int mask = MASK_CORE8 & 0xFE; //no trigger core 0


  act = 0;
  exp = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256;
  core_id = get_core_id();

  if(core_id == 0) {

    for(i = 0; i < N_INTERS; i++){

      for(j = 0; j < 500; j++) asm volatile ("nop\n");

      eu_evt_trig(eu_evt_trig_addr(SW_EVENT_7), mask);
    }

  } else {

    eu_evt_maskSet(1 << SW_EVENT_7);

    //-----------------------------------------------------------------
    // Basic Check
    //-----------------------------------------------------------------
    for(i = 0; i < N_INTERS; i++) {
      asm volatile ("addi %[act], x0, 1\n"
                    "addi %[act], %[act], 2\n"
                    "addi %[act], %[act], 4\n"
                    "p.elw x0, 0x0(%[clkgate_addr])\n" //eu_evt_wait(); <- evt_read32(ARCHI_EU_DEMUX_ADDR, EU_CORE_EVENT_WAIT);
                    "sw %[evtMask], 0x0(%[clr_buf])\n" //eu_evt_clr(1 << EU_CORE_EVENT_WAIT)
                    "addi %[act], %[act], 8\n"
                    "addi %[act], %[act], 16\n"
                    "addi %[act], %[act], 32\n"
                    "addi %[act], %[act], 64\n"
                    "addi %[act], %[act], 128\n"
                    "addi %[act], %[act], 256\n"
                    : [act] "+r" (act)
                    : [clkgate_addr] "r" (CORE_CLKGATE),
                      [clr_buf]      "r" (CLEAR_BUFF),
                      [evtMask]      "r" (1 << SW_EVENT_7));

      if(act != exp) {
        result->errors++;
        printf("Testing add before and after events: %X, expected %X\n", act, exp);
      }
    }

    eu_evt_maskClr(1 << SW_EVENT_7);

  }
  synch_barrier();
}


void check_hwloop(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i, j;
  unsigned int mask = MASK_CORE8 & 0xFE; //no trigger core 0
  int core_id;

  core_id = get_core_id();

  if(core_id == 0) {
    //core 0

    //-----------------------------------------------------------------
    // Clock Gating and explicit clear buffer
    //-----------------------------------------------------------------

    for(j = 0; j < 400; j++) asm volatile ("nop\n");
    for(i = 0; i < N_INTERS; i++) {
      for(j = 0; j < i*5+1000; j++) asm volatile ("nop\n");

      eu_evt_trig(eu_evt_trig_addr(SW_EVENT_7), mask);
    }

    //-----------------------------------------------------------------
    // Clock Gating and implicit clear buffer
    //-----------------------------------------------------------------

    for(j = 0; j < 400; j++) asm volatile ("nop\n");
    for(i = 0; i < N_INTERS; i++) {
      for(j = 0; j < i*5+1000; j++) asm volatile ("nop\n");

      eu_evt_trig(eu_evt_trig_addr(SW_EVENT_7), mask);
    }

  } else {
    // other cores
    int act;
    int exp;

    exp = 10*(1 + 2 + 3 + 4 + 5 + 6);

    //-----------------------------------------------------------------
    // Clock Gating and explicit clear buffer
    //-----------------------------------------------------------------

    eu_evt_maskSet(1 << SW_EVENT_7);
    act = 0;
    asm volatile ("lp.counti x0, %[N]\n"
                  "lp.starti x0, startE\n"
                  "lp.endi   x0, endE\n"
                  "startE: addi %[act], %[act], 1\n"
                  "addi %[act], %[act], 2\n"
                  "addi %[act], %[act], 3\n"
                  "p.elw x0, 0x0(%[clkgate_addr])\n"
                  "sw %[evtMask], 0x0(%[clr_buf])\n"
                  "addi %[act], %[act], 4\n"
                  "addi %[act], %[act], 5\n"
                  "endE: addi %[act], %[act], 6\n"
                  : [act] "+r" (act)
                  : [N]            "i" (N_INTERS),
                    [clkgate_addr] "r" (CORE_CLKGATE),
                    [clr_buf]      "r" (CLEAR_BUFF),
                    [evtMask]      "r" (1 << SW_EVENT_7));

    eu_evt_maskClr(1 << SW_EVENT_7);

    if(act != exp) {
      result->errors++;
      printf("Testing hwloop with clock gating and explicit clear buffer: %X, expected %X\n", act, exp);
    }

    //-----------------------------------------------------------------
    // No Clock Gating
    //-----------------------------------------------------------------

    act = 0;
    asm volatile ("lp.counti x0, %[N]\n"
                  "lp.starti x0, startN\n"
                  "lp.endi   x0, endN\n"
                  "startN: addi %[act], %[act], 1\n"
                  "addi %[act], %[act], 2\n"
                  "addi %[act], %[act], 3\n"
                  "addi %[act], %[act], 4\n"
                  "addi %[act], %[act], 5\n"
                  "endN: addi %[act], %[act], 6\n"
                  : [act] "+r" (act)
                  : [N]   "i" (N_INTERS));

    if(act != exp) {
      result->errors++;
      printf("Testing normal hwloop: %X, expected %X\n", act, exp);
    }

    //-----------------------------------------------------------------
    // Clock Gating and implicit clear buffer
    //-----------------------------------------------------------------

    eu_evt_maskSet(1 << SW_EVENT_7);
    act = 0;
    asm volatile ("lp.counti x0, %[N]\n"
                  "lp.starti x0, startI\n"
                  "lp.endi   x0, endI\n"
                  "startI: addi %[act], %[act], 1\n"
                  "addi %[act], %[act], 2\n"
                  "addi %[act], %[act], 3\n"
                  "p.elw x0, 0x0(%[clkgate_addr])\n"
                  "addi %[act], %[act], 4\n"
                  "addi %[act], %[act], 5\n"
                  "endI: addi %[act], %[act], 6\n"
                  : [act] "+r" (act)
                  : [N]            "i" (N_INTERS),
                    [clkgate_addr] "r" (CORE_CLKGATE_CLRBUFF),
                    [evtMask]      "r" (1 << SW_EVENT_7));


    eu_evt_maskClr(1 << SW_EVENT_7);

    if(act != exp) {
      result->errors++;
      printf("Testing hwloop with clock gating and implicit clear buffer: %X, expected %X\n", act, exp);
    }

  }

  synch_barrier();
}

void check_prod_cons(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i, j;
  int core_id;
  unsigned int mask1 = MASK_CORE8 & 0x02; //trigger only core 1
  unsigned int mask0 = MASK_CORE8 & 0x01; //trigger only core 0

  core_id = get_core_id();

  if(core_id == 0) {

    eu_evt_maskSet(1 << _STOP_READ);
    eu_evt_maskSet(1 << _DATA_READ);

    _stop = 0;

    for(i = 0; i < N_INTERS; i++){

      eu_evt_trig(eu_evt_trig_addr(_STOP_READY), mask1);

      //WAIT _STOP_READ
      asm volatile ("p.elw x0, 0x0(%[clkgate_addr])\n"
                     :
                     : [clkgate_addr] "r" (CORE_CLKGATE_CLRBUFF));
      //delay loop
      for(j = 0; j < 500; j++) asm volatile ("nop\n");

      _data = 2*i;

      eu_evt_trig(eu_evt_trig_addr(_DATA_READY), mask1);
      //WAIT _DATA_READ
      asm volatile ("p.elw x0, 0x0(%[clkgate_addr])\n"
                     :
                     : [clkgate_addr] "r" (CORE_CLKGATE_CLRBUFF));

    }

    _stop = 1;
    eu_evt_trig(eu_evt_trig_addr(_STOP_READY), mask1);

    //WAIT _STOP_READ
    asm volatile ("p.elw x0, 0x0(%[clkgate_addr])\n"
                     :
                     : [clkgate_addr] "r" (CORE_CLKGATE_CLRBUFF));

    eu_evt_maskClr(1 << _STOP_READ);
    eu_evt_maskClr(1 << _DATA_READ);

  } else if(core_id ==1) {

    unsigned int stop_read;
    unsigned int datas[N_INTERS];

    eu_evt_maskSet(1 << _STOP_READY);
    eu_evt_maskSet(1 << _DATA_READY);

    i=0;
    while(1){

      //WAIT _STOP_READY
      asm volatile ("p.elw x0, 0x0(%[clkgate_addr])\n"
                     :
                     : [clkgate_addr] "r" (CORE_CLKGATE_CLRBUFF));

      stop_read = _stop;

      eu_evt_trig(eu_evt_trig_addr(_STOP_READ), mask0);

      if(stop_read) break;

      if(i>=10) { printf("Error! Data out of bounds (i = %d) \n",i); break; }

      //WAIT _DATA_READY
      asm volatile ("p.elw x0, 0x0(%[clkgate_addr])\n"
                     :
                     : [clkgate_addr] "r" (CORE_CLKGATE_CLRBUFF));

      datas[i] = _data;

      eu_evt_trig(eu_evt_trig_addr(_DATA_READ), mask0);

      i++;


    }

    eu_evt_maskClr(1 << _STOP_READY);
    eu_evt_maskClr(1 << _DATA_READY);

    if(i != N_INTERS) {
      result->errors++;
      printf("Core 1 did not receives the expected number of data\n");
    }


    for(j = 0; j < i; j++){
      if(datas[j] != j*2) {
       result->errors++;
       printf("datas[%u] is %u, expected %u\n",j,datas[j],j*2);
      }
    }

  }
  synch_barrier();
}