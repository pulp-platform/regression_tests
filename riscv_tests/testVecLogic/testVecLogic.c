// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

// This testbench checks the basic functionality of:
//


//pv.srl.h
//pv.srl.sc.h
//pv.srl.sci.h
//pv.srl.b
//pv.srl.sc.b
//pv.srl.sci.b
//pv.sra.h
//pv.sra.sc.h
//pv.sra.sci.h
//pv.sra.b
//pv.sra.sc.b
//pv.sra.sci.b
//pv.sll.h
//pv.sll.sc.h
//pv.sll.sci.h
//pv.sll.b
//pv.sll.sc.b
//pv.sll.sci.b
//pv.or.h
//pv.or.sc.h
//pv.or.sci.h
//pv.or.b
//pv.or.sc.b
//pv.or.sci.b
//pv.xor.h
//pv.xor.sc.h
//pv.xor.sci.h
//pv.xor.b
//pv.xor.sc.b
//pv.xor.sci.b
//pv.and.h
//pv.and.sc.h
//pv.and.sci.h
//pv.and.b
//pv.and.sc.b
//pv.and.sci.b
//pv.insert.h
//pv.insert.b

#include "pulp.h"
#include <stdio.h>
#include "riscv_test.h"

#define SCI_IMM    "11"
#define SRL_H      "pv.srl.h"
#define SRL_H_SC   "pv.srl.sc.h"
#define SRL_H_SCI  "pv.srl.sci.h"
#define SRL_B      "pv.srl.b"
#define SRL_B_SC   "pv.srl.sc.b"
#define SRL_B_SCI  "pv.srl.sci.b"
#define SRA_H      "pv.sra.h"
#define SRA_H_SC   "pv.sra.sc.h"
#define SRA_H_SCI  "pv.sra.sci.h"
#define SRA_B      "pv.sra.b"
#define SRA_B_SC   "pv.sra.sc.b"
#define SRA_B_SCI  "pv.sra.sci.b"
#define SLL_H      "pv.sll.h"
#define SLL_H_SC   "pv.sll.sc.h"
#define SLL_H_SCI  "pv.sll.sci.h"
#define SLL_B      "pv.sll.b"
#define SLL_B_SC   "pv.sll.sc.b"
#define SLL_B_SCI  "pv.sll.sci.b"
#define OR_H       "pv.or.h"
#define OR_H_SC    "pv.or.sc.h"
#define OR_H_SCI   "pv.or.sci.h"
#define OR_B       "pv.or.b"
#define OR_B_SC    "pv.or.sc.b"
#define OR_B_SCI   "pv.or.sci.b"
#define XOR_H      "pv.xor.h"
#define XOR_H_SC   "pv.xor.sc.h"
#define XOR_H_SCI  "pv.xor.sci.h"
#define XOR_B      "pv.xor.b"
#define XOR_B_SC   "pv.xor.sc.b"
#define XOR_B_SCI  "pv.xor.sci.b"
#define AND_H      "pv.and.h"
#define AND_H_SC   "pv.and.sc.h"
#define AND_H_SCI  "pv.and.sci.h"
#define AND_B      "pv.and.b"
#define AND_B_SC   "pv.and.sc.b"
#define AND_B_SCI  "pv.and.sci.b"
#define INS_H      "pv.insert.h"
#define INS_B      "pv.insert.b"

void check_srl(void);
void check_sra(void);
void check_sll(void);
void check_or(void);
void check_xor(void);
void check_and(void);
void check_ins(void);


int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if(get_core_id() == 0) {
    test_init();

    check_srl();
    check_sra();
    check_sll();
    check_or();
    check_xor();
    check_and();
    check_ins();

    test_report();

    if (test_get_num_errors() == 0)
    {
        printf("Everything worked good :-)");
    }
    else
    {
	return -1;
    }
  }

  return 0;
}

#include "testVecLogic_stimuli.h"

#define util_check_rrr(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      act = prefix ## _d[i]; \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rrr_sci(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      act = prefix ## _d[i]; \
      asm volatile (asm_str " %[c], %[a], " imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rrri(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      act = prefix ## _d[i]; \
      asm volatile (asm_str " %[c], %[a], %[b], " imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rr(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rr_sci(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], " imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rri(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b], " imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rri2(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      act = prefix ## _a[i]; \
      asm volatile (asm_str " %[c], %[b], " imm "\n" \
                    : [c] "+r" (act) \
                    : [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_ri(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], " imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_r(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a]\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }


void check_srl(void) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.srl
  //-----------------------------------------------------------------
  util_check_rr    (SRL_H,     i, g_srl_h);
  util_check_rr    (SRL_H_SC,  i, g_srl_h_sc);
  util_check_rr_sci(SRL_H_SCI, i, g_srl_h_sci, "9");

  util_check_rr    (SRL_B,     i, g_srl_b);
  util_check_rr    (SRL_B_SC,  i, g_srl_b_sc);
  util_check_rr_sci(SRL_B_SCI, i, g_srl_b_sci, "5");
}

void check_sra(void) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.sra
  //-----------------------------------------------------------------
  util_check_rr    (SRA_H,     i, g_sra_h);
  util_check_rr    (SRA_H_SC,  i, g_sra_h_sc);
  util_check_rr_sci(SRA_H_SCI, i, g_sra_h_sci, "9");

  util_check_rr    (SRA_B,     i, g_sra_b);
  util_check_rr    (SRA_B_SC,  i, g_sra_b_sc);
  util_check_rr_sci(SRA_B_SCI, i, g_sra_b_sci, "5");
}

void check_sll(void) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.sll
  //-----------------------------------------------------------------
  util_check_rr    (SLL_H,     i, g_sll_h);
  util_check_rr    (SLL_H_SC,  i, g_sll_h_sc);
  util_check_rr_sci(SLL_H_SCI, i, g_sll_h_sci, "9");

  util_check_rr    (SLL_B,     i, g_sll_b);
  util_check_rr    (SLL_B_SC,  i, g_sll_b_sc);
  util_check_rr_sci(SLL_B_SCI, i, g_sll_b_sci, "5");
}

void check_or(void) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.or
  //-----------------------------------------------------------------
  util_check_rr    (OR_H,     i, g_or_h);
  util_check_rr    (OR_H_SC,  i, g_or_h_sc);
  util_check_rr_sci(OR_H_SCI, i, g_or_h_sci, SCI_IMM);

  util_check_rr    (OR_B,     i, g_or_b);
  util_check_rr    (OR_B_SC,  i, g_or_b_sc);
  util_check_rr_sci(OR_B_SCI, i, g_or_b_sci, SCI_IMM);
}

void check_xor(void) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.xor
  //-----------------------------------------------------------------
  util_check_rr    (XOR_H,     i, g_xor_h);
  util_check_rr    (XOR_H_SC,  i, g_xor_h_sc);
  util_check_rr_sci(XOR_H_SCI, i, g_xor_h_sci, SCI_IMM);

  util_check_rr    (XOR_B,     i, g_xor_b);
  util_check_rr    (XOR_B_SC,  i, g_xor_b_sc);
  util_check_rr_sci(XOR_B_SCI, i, g_xor_b_sci, SCI_IMM);
}

void check_and(void) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.and
  //-----------------------------------------------------------------
  util_check_rr    (AND_H,     i, g_and_h);
  util_check_rr    (AND_H_SC,  i, g_and_h_sc);
  util_check_rr_sci(AND_H_SCI, i, g_and_h_sci, SCI_IMM);

  util_check_rr    (AND_B,     i, g_and_b);
  util_check_rr    (AND_B_SC,  i, g_and_b_sc);
  util_check_rr_sci(AND_B_SCI, i, g_and_b_sci, SCI_IMM);
}

void check_ins(void) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.ins
  //-----------------------------------------------------------------

  util_check_rri2(INS_H, i, g_ins_h0, "0");
  util_check_rri2(INS_H, i, g_ins_h1, "1");

  util_check_rri2(INS_B, i, g_ins_b0, "0");
  util_check_rri2(INS_B, i, g_ins_b1, "1");
  util_check_rri2(INS_B, i, g_ins_b2, "2");
  util_check_rri2(INS_B, i, g_ins_b3, "3");
}
