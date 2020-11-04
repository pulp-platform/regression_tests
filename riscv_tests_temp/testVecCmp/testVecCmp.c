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
//pv.cmpeq.h
//pv.cmpeq.sc.h
//pv.cmpeq.sci.h
//pv.cmpeq.b
//pv.cmpeq.sc.b
//pv.cmpeq.sci.b
//pv.cmpne.h
//pv.cmpne.sc.h
//pv.cmpne.sci.h
//pv.cmpne.b
//pv.cmpne.sc.b
//pv.cmpne.sci.b
//pv.cmple.h
//pv.cmple.sc.h
//pv.cmple.sci.h
//pv.cmple.b
//pv.cmple.sc.b
//pv.cmple.sci.b
//pv.cmpleu.h
//pv.cmpleu.sc.h
//pv.cmpleu.sci.h
//pv.cmpleu.b
//pv.cmpleu.sc.b
//pv.cmpleu.sci.b
//pv.cmplt.h
//pv.cmplt.sc.h
//pv.cmplt.sci.h
//pv.cmplt.b
//pv.cmplt.sc.b
//pv.cmplt.sci.b
//pv.cmpltu.h
//pv.cmpltu.sc.h
//pv.cmpltu.sci.h
//pv.cmpltu.b
//pv.cmpltu.sc.b
//pv.cmpltu.sci.b
//pv.cmpge.h
//pv.cmpge.sc.h
//pv.cmpge.sci.h
//pv.cmpge.b
//pv.cmpge.sc.b
//pv.cmpge.sci.b
//pv.cmpgeu.h
//pv.cmpgeu.sc.h
//pv.cmpgeu.sci.h
//pv.cmpgeu.b
//pv.cmpgeu.sc.b
//pv.cmpgeu.sci.b
//pv.cmpgt.h
//pv.cmpgt.sc.h
//pv.cmpgt.sci.h
//pv.cmpgt.b
//pv.cmpgt.sc.b
//pv.cmpgt.sci.b
//pv.cmpgtu.h
//pv.cmpgtu.sc.h
//pv.cmpgtu.sci.h
//pv.cmpgtu.b
//pv.cmpgtu.sc.b
//pv.cmpgtu.sci.b


#include <stdio.h>
#include <pulp.h>
#include "riscv_test.h"

#define SCI_IMM      "11"
#define CMPEQ_H      "pv.cmpeq.h"
#define CMPEQ_H_SC   "pv.cmpeq.sc.h"
#define CMPEQ_H_SCI  "pv.cmpeq.sci.h"
#define CMPEQ_B      "pv.cmpeq.b"
#define CMPEQ_B_SC   "pv.cmpeq.sc.b"
#define CMPEQ_B_SCI  "pv.cmpeq.sci.b"
#define CMPNE_H      "pv.cmpne.h"
#define CMPNE_H_SC   "pv.cmpne.sc.h"
#define CMPNE_H_SCI  "pv.cmpne.sci.h"
#define CMPNE_B      "pv.cmpne.b"
#define CMPNE_B_SC   "pv.cmpne.sc.b"
#define CMPNE_B_SCI  "pv.cmpne.sci.b"
#define CMPLE_H      "pv.cmple.h"
#define CMPLE_H_SC   "pv.cmple.sc.h"
#define CMPLE_H_SCI  "pv.cmple.sci.h"
#define CMPLE_B      "pv.cmple.b"
#define CMPLE_B_SC   "pv.cmple.sc.b"
#define CMPLE_B_SCI  "pv.cmple.sci.b"
#define CMPLEU_H     "pv.cmpleu.h"
#define CMPLEU_H_SC  "pv.cmpleu.sc.h"
#define CMPLEU_H_SCI "pv.cmpleu.sci.h"
#define CMPLEU_B     "pv.cmpleu.b"
#define CMPLEU_B_SC  "pv.cmpleu.sc.b"
#define CMPLEU_B_SCI "pv.cmpleu.sci.b"
#define CMPLT_H      "pv.cmplt.h"
#define CMPLT_H_SC   "pv.cmplt.sc.h"
#define CMPLT_H_SCI  "pv.cmplt.sci.h"
#define CMPLT_B      "pv.cmplt.b"
#define CMPLT_B_SC   "pv.cmplt.sc.b"
#define CMPLT_B_SCI  "pv.cmplt.sci.b"
#define CMPLTU_H     "pv.cmpltu.h"
#define CMPLTU_H_SC  "pv.cmpltu.sc.h"
#define CMPLTU_H_SCI "pv.cmpltu.sci.h"
#define CMPLTU_B     "pv.cmpltu.b"
#define CMPLTU_B_SC  "pv.cmpltu.sc.b"
#define CMPLTU_B_SCI "pv.cmpltu.sci.b"
#define CMPGE_H      "pv.cmpge.h"
#define CMPGE_H_SC   "pv.cmpge.sc.h"
#define CMPGE_H_SCI  "pv.cmpge.sci.h"
#define CMPGE_B      "pv.cmpge.b"
#define CMPGE_B_SC   "pv.cmpge.sc.b"
#define CMPGE_B_SCI  "pv.cmpge.sci.b"
#define CMPGEU_H     "pv.cmpgeu.h"
#define CMPGEU_H_SC  "pv.cmpgeu.sc.h"
#define CMPGEU_H_SCI "pv.cmpgeu.sci.h"
#define CMPGEU_B     "pv.cmpgeu.b"
#define CMPGEU_B_SC  "pv.cmpgeu.sc.b"
#define CMPGEU_B_SCI "pv.cmpgeu.sci.b"
#define CMPGT_H      "pv.cmpgt.h"
#define CMPGT_H_SC   "pv.cmpgt.sc.h"
#define CMPGT_H_SCI  "pv.cmpgt.sci.h"
#define CMPGT_B      "pv.cmpgt.b"
#define CMPGT_B_SC   "pv.cmpgt.sc.b"
#define CMPGT_B_SCI  "pv.cmpgt.sci.b"
#define CMPGTU_H     "pv.cmpgtu.h"
#define CMPGTU_H_SC  "pv.cmpgtu.sc.h"
#define CMPGTU_H_SCI "pv.cmpgtu.sci.h"
#define CMPGTU_B     "pv.cmpgtu.b"
#define CMPGTU_B_SC  "pv.cmpgtu.sc.b"
#define CMPGTU_B_SCI "pv.cmpgtu.sci.b"

void check_cmp(void);

int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if(get_core_id() == 0) {
    test_init();

    check_cmp();

    test_report();

    if (test_get_num_errors() == 0)
    {
    }
    else
    {
	return -1;
    }
  }

  return 0;
}

#include "testVecCmp_stimuli.h"

#define util_check_rr(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    : [c] "+r" (prefix ## _act[i]) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
    }

#define util_check_rr_sci(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], " imm "\n" \
                    : [c] "+r" (prefix ## _act[i]) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
    }

#define util_check_rri(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b], " imm "\n" \
                    : [c] "+r" (prefix ## _act[i]) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
    }

#define util_check_ri(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], " imm "\n" \
                    : [c] "+r" (prefix ## _act[i]) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
    }

#define util_check_r(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a]\n" \
                    : [c] "+r" (prefix ## _act[i]) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
    }

#define util_check_cmov_rr(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    "l.cmov   %[d], %[e0], %[e1]\n" \
                    : [c] "+r" (prefix ## _act[i]), \
                      [d] "+r" (prefix ## _act2[i]) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r"  (prefix ## _b[i]), \
                      [e0] "r" (0x13371337), \
                      [e1] "r" (0xDEADBEEF)); \
      test_check(asm_str, prefix ## _act[i],  prefix ## _exp[i]); \
      test_check(asm_str, prefix ## _act2[i], prefix ## _cmov[i]); \
    }

#define util_check_cmov_rr_sci(asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], " imm "\n" \
                    "l.cmov   %[d], %[e0], %[e1]\n" \
                    : [c] "+r" (prefix ## _act[i]), \
                      [d] "+r" (prefix ## _act2[i]) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [e0] "r" (0x13371337), \
                      [e1] "r" (0xDEADBEEF)); \
      test_check(asm_str, prefix ## _act[i],  prefix ## _exp[i]); \
      test_check(asm_str, prefix ## _act2[i], prefix ## _cmov[i]); \
    }

void check_cmp(void) {
  unsigned int i;

  //-----------------------------------------------------------------
  // Check pv.cmp_eq
  //-----------------------------------------------------------------
  util_check_rr    (CMPEQ_H,     i, g_eq_h);
  util_check_rr    (CMPEQ_H_SC,  i, g_eq_h_sc);
  util_check_rr_sci(CMPEQ_H_SCI, i, g_eq_h_sci, SCI_IMM);

  util_check_rr    (CMPEQ_B,     i, g_eq_b);
  util_check_rr    (CMPEQ_B_SC,  i, g_eq_b_sc);
  util_check_rr_sci(CMPEQ_B_SCI, i, g_eq_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.cmp_ne
  //-----------------------------------------------------------------
  util_check_rr    (CMPNE_H,     i, g_ne_h);
  util_check_rr    (CMPNE_H_SC,  i, g_ne_h_sc);
  util_check_rr_sci(CMPNE_H_SCI, i, g_ne_h_sci, SCI_IMM);

  util_check_rr    (CMPNE_B,     i, g_ne_b);
  util_check_rr    (CMPNE_B_SC,  i, g_ne_b_sc);
  util_check_rr_sci(CMPNE_B_SCI, i, g_ne_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.cmp_le
  //-----------------------------------------------------------------
  util_check_rr    (CMPLE_H,     i, g_le_h);
  util_check_rr    (CMPLE_H_SC,  i, g_le_h_sc);
  util_check_rr_sci(CMPLE_H_SCI, i, g_le_h_sci, SCI_IMM);

  util_check_rr    (CMPLE_B,     i, g_le_b);
  util_check_rr    (CMPLE_B_SC,  i, g_le_b_sc);
  util_check_rr_sci(CMPLE_B_SCI, i, g_le_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.cmp_leu
  //-----------------------------------------------------------------
  util_check_rr    (CMPLEU_H,     i, g_leu_h);
  util_check_rr    (CMPLEU_H_SC,  i, g_leu_h_sc);
  util_check_rr_sci(CMPLEU_H_SCI, i, g_leu_h_sci, SCI_IMM);

  util_check_rr    (CMPLEU_B,     i, g_leu_b);
  util_check_rr    (CMPLEU_B_SC,  i, g_leu_b_sc);
  util_check_rr_sci(CMPLEU_B_SCI, i, g_leu_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.cmp_lt
  //-----------------------------------------------------------------
  util_check_rr    (CMPLT_H,     i, g_lt_h);
  util_check_rr    (CMPLT_H_SC,  i, g_lt_h_sc);
  util_check_rr_sci(CMPLT_H_SCI, i, g_lt_h_sci, SCI_IMM);

  util_check_rr    (CMPLT_B,     i, g_lt_b);
  util_check_rr    (CMPLT_B_SC,  i, g_lt_b_sc);
  util_check_rr_sci(CMPLT_B_SCI, i, g_lt_b_sci, SCI_IMM);

   //-----------------------------------------------------------------
  // Check pv.cmp_ltu
  //-----------------------------------------------------------------
  util_check_rr    (CMPLTU_H,     i, g_ltu_h);
  util_check_rr    (CMPLTU_H_SC,  i, g_ltu_h_sc);
  util_check_rr_sci(CMPLTU_H_SCI, i, g_ltu_h_sci, SCI_IMM);

  util_check_rr    (CMPLTU_B,     i, g_ltu_b);
  util_check_rr    (CMPLTU_B_SC,  i, g_ltu_b_sc);
  util_check_rr_sci(CMPLTU_B_SCI, i, g_ltu_b_sci, SCI_IMM);


  //-----------------------------------------------------------------
  // Check pv.cmp_ge
  //-----------------------------------------------------------------
  util_check_rr    (CMPGE_H,     i, g_ge_h);
  util_check_rr    (CMPGE_H_SC,  i, g_ge_h_sc);
  util_check_rr_sci(CMPGE_H_SCI, i, g_ge_h_sci, SCI_IMM);

  util_check_rr    (CMPGE_B,     i, g_ge_b);
  util_check_rr    (CMPGE_B_SC,  i, g_ge_b_sc);
  util_check_rr_sci(CMPGE_B_SCI, i, g_ge_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.cmp_geu
  //-----------------------------------------------------------------
  util_check_rr    (CMPGEU_H,     i, g_geu_h);
  util_check_rr    (CMPGEU_H_SC,  i, g_geu_h_sc);
  util_check_rr_sci(CMPGEU_H_SCI, i, g_geu_h_sci, SCI_IMM);

  util_check_rr    (CMPGEU_B,     i, g_geu_b);
  util_check_rr    (CMPGEU_B_SC,  i, g_geu_b_sc);
  util_check_rr_sci(CMPGEU_B_SCI, i, g_geu_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.cmp_gt
  //-----------------------------------------------------------------
  util_check_rr    (CMPGT_H,     i, g_gt_h);
  util_check_rr    (CMPGT_H_SC,  i, g_gt_h_sc);
  util_check_rr_sci(CMPGT_H_SCI, i, g_gt_h_sci, SCI_IMM);

  util_check_rr    (CMPGT_B,     i, g_gt_b);
  util_check_rr    (CMPGT_B_SC,  i, g_gt_b_sc);
  util_check_rr_sci(CMPGT_B_SCI, i, g_gt_b_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.cmp_gtu
  //-----------------------------------------------------------------
  util_check_rr    (CMPGTU_H,     i, g_gtu_h);
  util_check_rr    (CMPGTU_H_SC,  i, g_gtu_h_sc);
  util_check_rr_sci(CMPGTU_H_SCI, i, g_gtu_h_sci, SCI_IMM);

  util_check_rr    (CMPGTU_B,     i, g_gtu_b);
  util_check_rr    (CMPGTU_B_SC,  i, g_gtu_b_sc);
  util_check_rr_sci(CMPGTU_B_SCI, i, g_gtu_b_sci, SCI_IMM);
}
