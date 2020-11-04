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
//p.min
//p.minu
//pv.min.h
//pv.min.sc.h
//pv.min.sci.h
//pv.minu.h
//pv.minu.sc.h
//pv.minu.sci.h
//pv.min.b
//pv.min.sc.b
//pv.min.sci.b
//pv.minu.b
//pv.minu.sc.b
//pv.minu.sci.b
//p.max
//p.maxu
//pv.max.h
//pv.max.sc.h
//pv.max.sci.h
//pv.maxu.h
//pv.maxu.sc.h
//pv.maxu.sci.h
//pv.max.b
//pv.max.sc.b
//pv.max.sci.b
//pv.maxu.b
//pv.maxu.sc.b
//pv.maxu.sci.b


#include "pulp.h"
#include <stdio.h>
#include "riscv_test.h"

#define SCI_IMM     "11"
#define MIN         "p.min"
#define MINU        "p.minu"
#define MIN_H       "pv.min.h"
#define MIN_H_SC    "pv.min.sc.h"
#define MIN_H_SCI   "pv.min.sci.h"
#define MINU_H      "pv.minu.h"
#define MINU_H_SC   "pv.minu.sc.h"
#define MINU_H_SCI  "pv.minu.sci.h"
#define MIN_B       "pv.min.b"
#define MIN_B_SC    "pv.min.sc.b"
#define MIN_B_SCI   "pv.min.sci.b"
#define MINU_B      "pv.minu.b"
#define MINU_B_SC   "pv.minu.sc.b"
#define MINU_B_SCI  "pv.minu.sci.b"
#define MAX         "p.max"
#define MAXU        "p.maxu"
#define MAX_H       "pv.max.h"
#define MAX_H_SC    "pv.max.sc.h"
#define MAX_H_SCI   "pv.max.sci.h"
#define MAXU_H      "pv.maxu.h"
#define MAXU_H_SC   "pv.maxu.sc.h"
#define MAXU_H_SCI  "pv.maxu.sci.h"
#define MAX_B       "pv.max.b"
#define MAX_B_SC    "pv.max.sc.b"
#define MAX_B_SCI   "pv.max.sci.b"
#define MAXU_B      "pv.maxu.b"
#define MAXU_B_SC   "pv.maxu.sc.b"
#define MAXU_B_SCI  "pv.maxu.sci.b"


void check_min(void);
void check_max(void);


int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if(get_core_id() == 0) {
    test_init();

    check_min();
    check_max();

    test_report();

    if (test_get_num_errors() == 0)
    {
        printf("Everything worked good :-)");
	return 0;
    }
    else
    {
	return -1;
    }
  }
  return 0;
}

#include "testVecRelat_stimuli.h"

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
      asm volatile (asm_str " %[c], %[a], %[b], " #imm "\n" \
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
      asm volatile (asm_str " %[c], %[a], %[b], " #imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_ri(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], " #imm "\n" \
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


void check_min(void) {
  unsigned int i;
  unsigned int act;

  util_check_rr(MIN,  i, g_min);
  util_check_rr(MINU, i, g_minu);

  //-----------------------------------------------------------------
  // Check pv.min.h
  //-----------------------------------------------------------------
  util_check_rr    (MIN_H,     i, g_min_h);
  util_check_rr    (MIN_H_SC,  i, g_min_h_sc);
  util_check_rr_sci(MIN_H_SCI, i, g_min_h_sci, SCI_IMM);


  //-----------------------------------------------------------------
  // Check pv.minu.h
  //-----------------------------------------------------------------
  util_check_rr    (MINU_H,     i, g_minu_h);
  util_check_rr    (MINU_H_SC,  i, g_minu_h_sc);
  util_check_rr_sci(MINU_H_SCI, i, g_minu_h_sci, SCI_IMM);


  //-----------------------------------------------------------------
  // Check pv.min.b
  //-----------------------------------------------------------------
  util_check_rr    (MIN_B,     i, g_min_b);
  util_check_rr    (MIN_B_SC,  i, g_min_b_sc);
  util_check_rr_sci(MIN_B_SCI, i, g_min_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.minu.b
  //-----------------------------------------------------------------
  util_check_rr    (MINU_B,     i, g_minu_b);
  util_check_rr    (MINU_B_SC,  i, g_minu_b_sc);
  util_check_rr_sci(MINU_B_SCI, i, g_minu_b_sci, SCI_IMM);
}

void check_max(void) {
  unsigned int i;
  unsigned int act;

  util_check_rr(MAX,  i, g_max);
  util_check_rr(MAXU, i, g_maxu);

  //-----------------------------------------------------------------
  // Check pv.max.h
  //-----------------------------------------------------------------
  util_check_rr    (MAX_H,     i, g_max_h);
  util_check_rr    (MAX_H_SC,  i, g_max_h_sc);
  util_check_rr_sci(MAX_H_SCI, i, g_max_h_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.maxu.h
  //-----------------------------------------------------------------
  util_check_rr    (MAXU_H,     i, g_maxu_h);
  util_check_rr    (MAXU_H_SC,  i, g_maxu_h_sc);
  util_check_rr_sci(MAXU_H_SCI, i, g_maxu_h_sci, SCI_IMM);


  //-----------------------------------------------------------------
  // Check pv.max.b
  //-----------------------------------------------------------------
  util_check_rr    (MAX_B,     i, g_max_b);
  util_check_rr    (MAX_B_SC,  i, g_max_b_sc);
  util_check_rr_sci(MAX_B_SCI, i, g_max_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.maxu.b
  //-----------------------------------------------------------------
  util_check_rr    (MAXU_B,     i, g_maxu_b);
  util_check_rr    (MAXU_B_SC,  i, g_maxu_b_sc);
  util_check_rr_sci(MAXU_B_SCI, i, g_maxu_b_sci, SCI_IMM);
}

