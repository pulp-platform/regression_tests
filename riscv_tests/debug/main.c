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

#define BASE_ADDRESS 0x1C000000
#define NCORES 4
#define CORE_CLKGATE_CLRBUFF  EVENT_UNIT_DEMUX_BASE_ADDR + EU_CORE_EVENT_WAIT_CLEAR
#define SW_EVENT 0

void test_init(testresult_t *result, void (*start)(), void (*stop)());
void test_finish(testresult_t *result, void (*start)(), void (*stop)());

void test_rw_gpr(testresult_t *result, void (*start)(), void (*stop)());
void test_rw_csr(testresult_t *result, void (*start)(), void (*stop)());
void test_rw_dbg_regs(testresult_t *result, void (*start)(), void (*stop)());
void test_halt_resume(testresult_t *result, void (*start)(), void (*stop)());
void test_ebreak(testresult_t *result, void (*start)(), void (*stop)());
void test_npc_ppc(testresult_t *result, void (*start)(), void (*stop)());
void test_illegal(testresult_t *result, void (*start)(), void (*stop)());
void test_single_step(testresult_t *result, void (*start)(), void (*stop)());
void test_jumps(testresult_t *result, void (*start)(), void (*stop)());
void test_jumps_after_branch(testresult_t *result, void (*start)(), void (*stop)());
void test_hardware_loop(testresult_t *result, void (*start)(), void (*stop)());
void test_nested_hardware_loop(testresult_t *result, void (*start)(), void (*stop)());
void test_illegal_hardware_loop(testresult_t *result, void (*start)(), void (*stop)());
void test_ss_hardware_loop(testresult_t *result, void (*start)(), void (*stop)());
void test_access_while_sleep(testresult_t *result, void (*start)(), void (*stop)());
void test_access_while_sleep_ss(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "init",                           .test = test_init                  },

  { .name = " 2. test_rw_gpr",                .test = test_rw_gpr                },
  { .name = " 3. test_rw_csr",                .test = test_rw_csr                },
  { .name = " 4. test_rw_dbg_regs",           .test = test_rw_dbg_regs           },
  { .name = " 5. test_halt_resume",           .test = test_halt_resume           },
  { .name = " 6. test_ebreak",                .test = test_ebreak                },
  { .name = " 7. test_npc_ppc",               .test = test_npc_ppc               },
  { .name = " 8. test_illegal",               .test = test_illegal               },
  { .name = " 9. test_single_step",           .test = test_single_step           },
  { .name = "10. test_jumps",                 .test = test_jumps                 },
  { .name = "11. test_jumps_after_branch",    .test = test_jumps_after_branch    },
  { .name = "12. test_hardware_loop",         .test = test_hardware_loop         },
  { .name = "13. test_nested_hardware_loop",  .test = test_nested_hardware_loop  },
  { .name = "14. test_illegal_hardware_loop", .test = test_illegal_hardware_loop },
  { .name = "15. test_ss_hardware_loop",      .test = test_ss_hardware_loop      },
  { .name = "16. test_access_while_sleep",    .test = test_access_while_sleep    },
  { .name = "17. test_access_while_sleep_ss", .test = test_access_while_sleep_ss },

  { .name = "finish",                         .test = test_finish                },
  {0, 0}
};

volatile uint32_t testcase_current[NCORES];
volatile uint32_t tb_errors[NCORES];

//----------------------------------------------------------------------------
// GLOBAL VARIABLE TO LET THEM BE ACCESSIBLE FROM SPI DEBUG (L2 MEMORY)
//----------------------------------------------------------------------------
volatile uint32_t changeme[NCORES];
volatile uint32_t act_hw_ss[NCORES];


int main() {
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  return run_suite(testcases);
}

void test_init(testresult_t *result, void (*start)(), void (*stop)()) {
  //----------------------------------------------------------------------------
  // 1. Stop and tell TB about our testcase_current variable
  //----------------------------------------------------------------------------
  asm volatile ("li x16, 0x04576763;"
                "addi x1, x0, 1;"
                "init_branch: bne x16, x1, init_branch;" ::: "x16");

  int coreid = get_core_id();

  testcase_current[coreid] = 0;
  tb_errors[coreid] = 0;

  asm volatile ("mv x16, %[current];"
                "mv x17, %[tb_errors];"
                "ebreak" :: [current] "r" (&testcase_current[coreid]), [tb_errors] "r" (&tb_errors[coreid]));

  printf("Core %d finished its initialization\n",coreid );

  synch_barrier();
}

//----------------------------------------------------------------------------
// 2. Fill GPRs with well known data
//----------------------------------------------------------------------------
void test_rw_gpr(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t a, b, c;
  int coreid = get_core_id();

  testcase_current[coreid] = 2;

  asm volatile ("li x5, 0x55555555;"
                "li x6, 0x12345666;"
                "li x7, 0x77;"
                "li x18, 0x88;"
                "li x31, 0x31;"
                "ebreak;"
                ::: "x5", "x6", "x7", "x18", "x31");

  // now read back some values written by the debug system
  asm volatile ("ebreak;"
                "mv %[a], x5;"
                "mv %[b], x6;"
                "mv %[c], x31;"
                : [a] "=r" (a), [b] "=r" (b), [c] "=r" (c) :: "x5", "x6", "x31");

  check_uint32(result, "x5",  a, 0x54321089);
  check_uint32(result, "x6",  b, 0x11223344);
  check_uint32(result, "x31", c, 0xFEDCBA09);
  result->errors += tb_errors[coreid];
  synch_barrier();
}

void test_finish(testresult_t *result, void (*start)(), void (*stop)()) {

  int coreid = get_core_id();
  testcase_current[coreid] = 0xFFFFFFFF;

  asm volatile ("ebreak");

  result->errors += tb_errors[coreid]; 

}

//----------------------------------------------------------------------------
// 3. Check CSR access
//----------------------------------------------------------------------------
void test_rw_csr(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t a, b;
  int coreid = get_core_id();

  testcase_current[coreid] = 3;

  asm volatile ("csrw 0x300, %[a];"
                "csrw 0x341, %[b];"
                "ebreak;" :: [a] "r" (0x1), [b] "r" (0x12345678));

  // now read back some values written by the debug system
  asm volatile ("ebreak;"
                "csrr %[a], 0x300;"
                "csrr %[b], 0x341;"
                : [a] "=r" (a), [b] "=r" (b));

  check_uint32(result, "mstatus",  a, 0x00000006);
  check_uint32(result, "mepc",     b, 0x87654321);

  synch_barrier();
}

//----------------------------------------------------------------------------
// 4. Check Debug Register access
//----------------------------------------------------------------------------
void test_rw_dbg_regs(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t a, b;
  int coreid = get_core_id();
  testcase_current[coreid] = 4;

  asm volatile ("ebreak");
  synch_barrier();
}

//----------------------------------------------------------------------------
// 5. Halt and resume core a couple of times
//----------------------------------------------------------------------------
void test_halt_resume(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t a, b;
  int coreid = get_core_id();

  changeme[coreid] = 1;
  testcase_current[coreid] = 5;
  asm volatile ("mv x16, %[addr];"
                "ebreak" :: [addr] "r" (&changeme[coreid]));

  while(changeme[coreid]);

  asm volatile ("ebreak");
  synch_barrier();
}

//----------------------------------------------------------------------------
// 6. ebreak, ebreak, ebreak
//
// Check if PPC and NPC work correctly
//----------------------------------------------------------------------------
void test_ebreak(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = get_core_id();
  testcase_current[coreid] = 6;

  asm volatile ("nop;"
                "ebreak;"
                "ebreak;"
                "ebreak;"
                "ebreak;"
                "ebreak;"
                "ebreak;"
                "ebreak;"
                "ebreak;"
                "ebreak;"
                "ebreak;");
  synch_barrier();
}

//----------------------------------------------------------------------------
// 7. NPC and PPC values
//----------------------------------------------------------------------------
void test_npc_ppc(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = get_core_id();
  unsigned int address_ecall = BASE_ADDRESS + 0x088;
  testcase_current[coreid] = 7;

  asm volatile ("ebreak");

  asm volatile ("la x16, before;"
                "mv x17, %[addr_ecall];"
                "la x18, after;"
                "        nop;"
                "before: ecall;"
                "after:  nop"
                :: [addr_ecall] "r" (address_ecall) : "x16", "x17", "x18");

  synch_barrier();
}

//----------------------------------------------------------------------------
// 8. Illegal Instruction Exception
//----------------------------------------------------------------------------
void test_illegal(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = get_core_id();
  testcase_current[coreid] = 8;
  unsigned int address_ill = BASE_ADDRESS + 0x084;

  asm volatile ("ebreak");

  asm volatile ("la x16,     before_ill;"
                "mv x17, %[addr_ill];"
                "la x18,     after_ill;"
                "            nop;"
                "before_ill: .word 0xF0F0F0F;"
                "after_ill:  nop"
                :: [addr_ill] "r" (address_ill) : "x16", "x17", "x18");
  synch_barrier();
}

//----------------------------------------------------------------------------
// 9. Single Step
//----------------------------------------------------------------------------
void test_single_step(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = get_core_id();
  volatile uint32_t act = 0;
  testcase_current[coreid] = 9;

  changeme[coreid] = 1;

  // check single-step with addi
  asm volatile ("ebreak;"
                "addi %[a], %[a], 1;"
                "addi %[a], %[a], 2;"
                "addi %[a], %[a], 4;"
                "addi %[a], %[a], 8;"
                : [a] "+r" (act));

  check_uint32(result, "addi single step", act, 1 + 2 + 4 + 8);

  //----------------------------------------------------------------------------
  // check tight branch loop with load
  //----------------------------------------------------------------------------
  asm volatile ("ebreak;"
                "mv x16, %[addr];"
                "ss_start: lw x17, 0(x16);"
                "          bne x0, x17, ss_start;"
                :: [addr] "r" (&changeme[coreid]) : "x16", "x17");

  //----------------------------------------------------------------------------
  // check tight branch loop with only bf, so we have to jump out
  //----------------------------------------------------------------------------
  asm volatile ("ebreak;"
                "la x16, tb_jump;"
                "tb_start: beq x0, x0, tb_start;"
                "tb_jump:  nop;");

  //----------------------------------------------------------------------------
  // check tight loop with no exit, so we have to jump out
  //----------------------------------------------------------------------------
  asm volatile ("ebreak;"
                "la x16, tl_jump;"
                "tl_start: j tl_start;"
                "tl_jump:  nop;");
  synch_barrier();
}

//----------------------------------------------------------------------------
// 10. Jumps with NPC setting
//----------------------------------------------------------------------------
void test_jumps(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = get_core_id();
  uint32_t act = 0;
  testcase_current[coreid] = 10;

  // check jumps with addi
  asm volatile ("la x16, jmp1;"
                "ebreak;"
                "      addi %[a], %[a], 1;"
                "      addi %[a], %[a], 2;"
                "jmp1: addi %[a], %[a], 4;"
                "      addi %[a], %[a], 8;"
                : [a] "+r" (act)
                :: "x16");

  check_uint32(result, "jmp1", act, 4 + 8);

  // check jumps to ebreak
  asm volatile ("la x16, jmpe;"
                "ebreak;"
                "      j jmpd;"
                "      nop;"
                "jmpe: ebreak;"
                "      nop;"
                "jmpd: nop;"
                ::: "x16");
  synch_barrier();
}

//----------------------------------------------------------------------------
// 11. Jumps after Branch, in single-stepping mode
//----------------------------------------------------------------------------
void test_jumps_after_branch(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = get_core_id();
  uint32_t act = 0;
  testcase_current[coreid] = 11;

  // check jumps after branch taken
  asm volatile ("        la  x16, bt_11;"
                "        la  x17, jmp_11;"
                "        la  x18, pc0_11;"
                "        la  x19, pc1_11;"
                "        ebreak;"
                "pc0_11: addi %[a], x0, 4;"
                "pc1_11: beq x0, x0, bt_11;"
                "        j jmp_11;"
                "        nop;"
                "bt_11:  addi %[a], x0, 2;"
                "jmp_11: nop;"
                : [a] "=r" (act)
                ::  "x16", "x17", "x18", "x19");

  check_uint32(result, "branch_aft_jmp_t", act, 2);

  // check jumps after branch not taken
  asm volatile ("          la  x16, pc2_11_2;"
                "          la  x17, jmp_11_2;"
                "          la  x18, pc0_11_2;"
                "          la  x19, pc1_11_2;"
                "          ebreak;"
                "pc0_11_2: addi %[a], x0, 4;"
                "pc1_11_2: beq x0, x16, bt_11_2;"
                "pc2_11_2: j jmp_11_2;"
                "bt_11_2:  addi %[a], x0, 2;"
                "jmp_11_2: nop;"
                : [a] "=r" (act)
                ::  "x16", "x17", "x18", "x19");

  check_uint32(result, "branch_aft_jmp_nt", act, 4);
  synch_barrier();
}

//----------------------------------------------------------------------------
// 16. Access while sleep
//----------------------------------------------------------------------------
void test_access_while_sleep(testresult_t *result, void (*start)(), void (*stop)()) {

  uint32_t gpr = 0;
  uint32_t csr = 0xB15B00B5;
  int coreid = get_core_id();

  testcase_current[coreid] = 16;


  if(coreid == 0) { 

    asm volatile ("li x16, 0x04576763;"
                  "li x17, 0x04576763;"
                  "li x18, 0x04576763;"
                  "addi x1, x0, 0x10;" : : : "x16", "x17", "x18");

    asm volatile ("init_branch_1: bne x16, x1, init_branch_1;" ::: "x16", "x1");
    eu_evt_trig(eu_evt_trig_addr(SW_EVENT), 0x02); //wake up core 1

    asm volatile ("init_branch_2: bne x17, x1, init_branch_2;" ::: "x17", "x1");
    eu_evt_trig(eu_evt_trig_addr(SW_EVENT), 0x04); //wake up core 2

    asm volatile ("init_branch_3: bne x18, x1, init_branch_3;" ::: "x18", "x1");

    eu_evt_trig(eu_evt_trig_addr(SW_EVENT), 0x08); //wake up core 3

  }
  else {

  // check if we can access internal registers while the core is sleeping
  // This includes GPR, CSR and Debug Registers
    eu_evt_maskSet(1 << SW_EVENT); 

    asm volatile ("            ebreak;"
                  "            li x16, 0x16161616;"
                  "            li x17, 0x17171717;"
                  "            la x18, aws_elw_1;"
                  "            la x20, next_elw_1;"
                  "            csrw 0x780, %[csr];"
                  "aws_elw_1:  p.elw x0, 0x0(%[clkgate_addr]);"
                  "next_elw_1: mv   %[gpr], x16;"
                  "            csrr %[csr], 0x780;"
                  : [gpr]          "+r"       ( gpr                  ),
                    [csr]          "+r"       ( csr                  )
                  : [clkgate_addr] "r"        ( CORE_CLKGATE_CLRBUFF )
                  : "x16", "x17", "x18", "x20");

    check_uint32(result, "gpr written", gpr, 0xFEDCBA00);
    check_uint32(result, "csr written", csr, 0xC0DE1234);

    eu_evt_maskClr(1 << SW_EVENT);

    result->errors += tb_errors[coreid]; 
  }
  synch_barrier(); 
}

#define HWLP_COUNTI 10
//----------------------------------------------------------------------------
// 12. Hardware Loop
//----------------------------------------------------------------------------
void test_hardware_loop(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t act = 0;
  int coreid = get_core_id();
  testcase_current[coreid] = 12;

  // check hardware loop size 4, loop#0
  asm volatile ("lp.counti x0, %[N];"
                "lp.starti x0, start_HWLP_1;"
                "lp.endi   x0, end_HWLP_1;"
                "start_HWLP_1: addi %[act], %[act], 1;"
                "              ebreak;"
                "              addi %[act], %[act], 2;"
                "end_HWLP_1:   addi %[act], %[act], 3;"
                : [act] "+r" (act)
                : [N]   "i"  (HWLP_COUNTI));


  check_uint32(result, "hardware_loop", act, HWLP_COUNTI*(1+2+3));

  act = 0;
  // check hardware loop size 3, loop#0
  asm volatile ("lp.counti x0, %[N];"
                "lp.starti x0, start_HWLP_2;"
                "lp.endi   x0, end_HWLP_2;"
                "start_HWLP_2: ebreak;"
                "              addi %[act], %[act], 1;"
                "end_HWLP_2:   addi %[act], %[act], 2;"
                : [act] "+r" (act)
                : [N]   "i"  (2*HWLP_COUNTI));


  check_uint32(result, "hardware_loop", act, 2*HWLP_COUNTI*(1+2));

  act = 0;
  // check hardware loop size 2, loop#1
  asm volatile ("lp.counti x1, %[N];"
                "lp.starti x1, start_HWLP_3;"
                "lp.endi   x1, end_HWLP_3;"
                "start_HWLP_3: addi %[act], %[act], 1;"
                "end_HWLP_3:   ebreak;"
                : [act] "+r" (act)
                : [N]   "i"  (3*HWLP_COUNTI));


  check_uint32(result, "hardware_loop", act, 3*HWLP_COUNTI*(1));

  act = 0;
  // check hardware loop size 2, ebreak after lp.counti, loop#1
  asm volatile ("la x16, %[N];"
                "lp.counti x1, %[N];"
                "ebreak;"
                "lp.starti x1, start_HWLP_4;"
                "lp.endi   x1, end_HWLP_4;"
                "start_HWLP_4: addi %[act], %[act], 1;"
                "end_HWLP_4:   nop;"
                : [act] "+r" (act)
                : [N]   "i"  (3*HWLP_COUNTI)
                : "x16");


  check_uint32(result, "hardware_loop", act, 3*HWLP_COUNTI*(1));

  act = 0;
  // check hardware loop size 2, ebreak after lp.starti, loop#1
  asm volatile ("la x16, %[N];"
                "la x17, start_HWLP_5;"
                "lp.counti x1, %[N];"
                "lp.starti x1, start_HWLP_5;"
                "ebreak;"
                "lp.endi   x1, end_HWLP_5;"
                "start_HWLP_5: addi %[act], %[act], 1;"
                "end_HWLP_5:   nop;"
                : [act] "+r" (act)
                : [N]   "i"  (3*HWLP_COUNTI)
                : "x16", "x17");

  act = 0;
  // check hardware loop size 2, ebreak after lp.endi, loop#1
  asm volatile ("la x16, %[N];"
                "la x17, start_HWLP_6;"
                "la x18, end_HWLP_6;"
                "lp.counti x1, %[N];"
                "lp.starti x1, start_HWLP_6;"
                "lp.endi   x1, end_HWLP_6;"
                "ebreak;"
                "start_HWLP_6: addi %[act], %[act], 1;"
                "end_HWLP_6:   nop;"
                : [act] "+r" (act)
                : [N]   "i"  (3*HWLP_COUNTI)
                : "x16", "x17", "x18");


  check_uint32(result, "hardware_loop", act, 3*HWLP_COUNTI*(1));
  synch_barrier(); 

}

//----------------------------------------------------------------------------
// 13. Nested Hardware Loop
//----------------------------------------------------------------------------
void test_nested_hardware_loop(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t act = 0;
  int coreid = get_core_id();
  testcase_current[coreid] = 13;

  asm volatile ("la x16, %[N];"
                "la x17, start_HWLP_7;"
                "la x18, end_HWLP_7;"
                "lp.counti x1, %[N];"
                "lp.starti x1, start_HWLP_7;"
                "lp.endi   x1, end_HWLP_7;"
                "ebreak;" // <--- first ebreak, happens once
                "la x19, %[N_in];"
                "la x20, start_HWLP_7_in;"
                "la x21, end_HWLP_7;"
                "start_HWLP_7: lp.counti x0, %[N_in];"
                "lp.starti x0, start_HWLP_7_in;"
                "lp.endi   x0, end_HWLP_7;"
                "ebreak;" // <--- second ebreak, happens HWLP_COUNTI/2 times
                "start_HWLP_7_in: addi %[act], %[act], 1;"
                "end_HWLP_7:      ebreak;" // <--- third ebreak, happens HWLP_COUNTI*HWLP_COUNTI/2 times
                : [act] "+r" (act)
                : [N]   "i"  (HWLP_COUNTI/2), [N_in]   "i"  (HWLP_COUNTI)
                : "x16", "x17", "x18", "x19", "x20", "x21");


  check_uint32(result, "nested_hardware_loop", act, HWLP_COUNTI*HWLP_COUNTI/2);
  synch_barrier(); 


}

//----------------------------------------------------------------------------
// 14. Illegal Hardware Loop
//----------------------------------------------------------------------------
void test_illegal_hardware_loop(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t act = 0;
  int coreid = get_core_id();
  unsigned int address_ill = BASE_ADDRESS + 0x084;
  testcase_current[coreid] = 14;

  // Illegal instruction is the last one, a patch in the debugger in order to
  // decrement the hwlp counter is needed

  asm volatile ("la x16, start_HWLP_8;"
                "mv x17, %[addr_ill];"
                "la x18, end_HWLP_8;"
                "la x19, end_HWLP_8_1;"
                "lp.counti x0, %[N];"
                "lp.starti x0, start_HWLP_8;"
                "lp.endi   x0, end_HWLP_8;"
                "ebreak;"
                "start_HWLP_8: addi %[act], %[act], 1;"
                "end_HWLP_8:   .word 0xF0F0F0F;"
                "end_HWLP_8_1: nop;"
                : [act]      "+r" (act)
                : [N]        "i"  (HWLP_COUNTI),
                  [addr_ill] "r" (address_ill)
                : "x16", "x17", "x18", "x19");

  check_uint32(result, "illegal_hardware_loop", act, HWLP_COUNTI);

  // Illegal instruction is not the last one, normal debug is ok
  act = 0;
  asm volatile ("la x16, start_HWLP_9;"
                "mv x17, %[addr_ill];"
                "la x18, end_HWLP_9;"
                "la x19, before_ill_hwlp;"
                "lp.counti x0, %[N];"
                "lp.starti x0, start_HWLP_9;"
                "lp.endi   x0, end_HWLP_9;"
                "ebreak;"
                "start_HWLP_9:    addi %[act], %[act], 1;"
                "before_ill_hwlp: .word 0xF0F0F0F;"
                "end_HWLP_9:      nop;"
                : [act]      "+r" (act)
                : [N]        "i"  (HWLP_COUNTI),
                  [addr_ill] "r"  (address_ill)
                : "x16", "x17", "x18", "x19");


  check_uint32(result, "illegal_hardware_loop", act, HWLP_COUNTI);
  synch_barrier(); 
}

//----------------------------------------------------------------------------
// 15. Hardware Loop Single Step
//----------------------------------------------------------------------------
void test_ss_hardware_loop(testresult_t *result, void (*start)(), void (*stop)()) {
  int coreid = get_core_id();
  uint32_t act_add = (uint32_t)&act_hw_ss[coreid];

  testcase_current[coreid] = 15;
  act_hw_ss[coreid] = 0;

  asm volatile ("la x16, start_HWLP_10;"
                "la x17, middle_HWLP_10;"
                "la x18, end_HWLP_10;"
                "la x19, %[N];"
                "la x22, store_HWLP_10;"
                "mv x20, %[act_add];"
                "xor x21, x21, x21;"
                "lp.counti x0, %[N];"
                "lp.starti x0, start_HWLP_10;"
                "lp.endi   x0, end_HWLP_10;"
                "ebreak;"
                "start_HWLP_10:    addi x21, x21, 1;"
                "middle_HWLP_10:   addi x21, x21, 2;"
                "end_HWLP_10:      addi x21, x21, 3;"
                "store_HWLP_10:    sw x21, 0(%[act_add]);"
                :
                : [N]   "i"  (HWLP_COUNTI), [act_add] "r" (act_add)
                : "x16", "x17", "x18", "x19", "x20", "x21", "x22");


  check_uint32(result, "ss_hardware_loop", act_hw_ss[coreid], HWLP_COUNTI*(1+2+3));
  synch_barrier(); 
}

//----------------------------------------------------------------------------
// 17. Access while sleep in single step mode
//----------------------------------------------------------------------------
void test_access_while_sleep_ss(testresult_t *result, void (*start)(), void (*stop)()) {

  uint32_t gpr = 0;
  uint32_t csr = 0xB15B00B5;
  int coreid = get_core_id();
  unsigned int address = eu_evt_trig_addr(SW_EVENT);
  

  testcase_current[coreid] = 17;


  if(coreid == 0) { 

    asm volatile ("li x16, 0x04576763;"
                  "li x17, 0x04576763;"
                  "li x18, 0x04576763;"
                  "addi x1, x0, 0x10;" : : : "x16", "x17", "x18");

    asm volatile ("init_branch_11: bne x16, x1, init_branch_11;" ::: "x16", "x1");
    eu_evt_trig(eu_evt_trig_addr(SW_EVENT), 0x02); //wake up core 1

  }
  else if (coreid ==1) {

  // check if we can access internal registers while the core is sleeping
  // This includes GPR, CSR and Debug Registers
    eu_evt_maskSet(1 << SW_EVENT); 
  //----------------------------------------------------------------------------
  // single step mode
  //----------------------------------------------------------------------------
    asm volatile ("            li x16, 0x16161616;"
                  "            li x17, 0x17171717;"
                  "            la x18, aws_elw_2;"
                  "            la x19, next_elw_2;"
                  "            la x20, next_mv_2;"
                  "            csrw 0x780, %[csr];"
                  "            ebreak;"
                  "aws_elw_2:  p.elw x0, 0x0(%[clkgate_addr]);"
                  "next_elw_2: mv   %[gpr], x16;"
                  "next_mv_2:  csrr %[csr], 0x780;"
                  : [gpr]          "+r"       ( gpr                  ),
                    [csr]          "+r"       ( csr                  )
                  : [clkgate_addr] "r"        ( CORE_CLKGATE_CLRBUFF )
                  : "x16", "x17", "x18", "x19", "x20");

    check_uint32(result, "gpr written", gpr, 0xFEDCBA00);
    check_uint32(result, "csr written", csr, 0xC0DE1234);

    eu_evt_maskClr(1 << SW_EVENT);

    result->errors += tb_errors[coreid]; 
  }
  synch_barrier(); 
}
