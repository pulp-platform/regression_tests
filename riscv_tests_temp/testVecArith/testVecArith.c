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
 //add
 //pv.add.h
 //pv.add.sc.h
 //pv.add.sci.h
 //pv.add.b
 //pv.add.sc.b
 //pv.add.sci.b
 //sub
 //pv.sub.h
 //pv.sub.sc.h
 //pv.sub.sci.h
 //pv.sub.b
 //pv.sub.sc.b
 //pv.sub.sci.b
 //pv.avg.h
 //pv.avg.sc.h
 //pv.avg.sci.h
 //pv.avg.b
 //pv.avg.sc.b
 //pv.avg.sci.b
 //pv.avgu.h
 //pv.avgu.sc.h
 //pv.avgu.sci.h
 //pv.avgu.b
 //pv.avgu.sc.b
 //pv.avgu.sci.b
 //p.abs
 //pv.abs.h
 //pv.abs.b
 //pv.extract.h
 //pv.extract.b
 //pv.extractu.h
 //pv.extractu.b
 //pv.insert.h
 //pv.insert.b

#include "pulp.h"
#include <stdio.h>

#define SCI_IMM "11"
#define ADD             "add"
#define PV_ADD_H        "pv.add.h"
#define PV_ADD_H_SC     "pv.add.sc.h"
#define PV_ADD_H_SCI    "pv.add.sci.h"
#define PV_ADD_B        "pv.add.b"
#define PV_ADD_B_SC     "pv.add.sc.b"
#define PV_ADD_B_SCI    "pv.add.sci.b"
#define SUB             "sub"
#define PV_SUB_H        "pv.sub.h"
#define PV_SUB_H_SC     "pv.sub.sc.h"
#define PV_SUB_H_SCI    "pv.sub.sci.h"
#define PV_SUB_B        "pv.sub.b"
#define PV_SUB_B_SC     "pv.sub.sc.b"
#define PV_SUB_B_SCI    "pv.sub.sci.b"
#define PV_AVG_H        "pv.avg.h"
#define PV_AVG_H_SC     "pv.avg.sc.h"
#define PV_AVG_H_SCI    "pv.avg.sci.h"
#define PV_AVG_B        "pv.avg.b"
#define PV_AVG_B_SC     "pv.avg.sc.b"
#define PV_AVG_B_SCI    "pv.avg.sci.b"
#define PV_AVGU_H       "pv.avgu.h"
#define PV_AVGU_H_SC    "pv.avgu.sc.h"
#define PV_AVGU_H_SCI   "pv.avgu.sci.h"
#define PV_AVGU_B       "pv.avgu.b"
#define PV_AVGU_B_SC    "pv.avgu.sc.b"
#define PV_AVGU_B_SCI   "pv.avgu.sci.b"
#define ABS             "p.abs"
#define PV_ABS_H        "pv.abs.h"
#define PV_ABS_B        "pv.abs.b"
#define PV_EXT_H        "pv.extract.h"
#define PV_EXT_B        "pv.extract.b"
#define PV_EXTU_H       "pv.extractu.h"
#define PV_EXTU_B       "pv.extractu.b"
#define PV_INS_H        "pv.insert.h"
#define PV_INS_B        "pv.insert.b"

#include "testVecArith_stimuli.h"

void check_add  (testresult_t *result, void (*start)(), void (*stop)());
void check_sub  (testresult_t *result, void (*start)(), void (*stop)());
void check_avg  (testresult_t *result, void (*start)(), void (*stop)());
void check_abs  (testresult_t *result, void (*start)(), void (*stop)());
void check_ext  (testresult_t *result, void (*start)(), void (*stop)());
void check_extu (testresult_t *result, void (*start)(), void (*stop)());
void check_ins  (testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "add"        , .test = check_add      },
  { .name = "sub"        , .test = check_sub      },
  { .name = "avg"        , .test = check_avg      },
  { .name = "abs"        , .test = check_abs      },
  { .name = "ext"        , .test = check_ext      },
  { .name = "extu"       , .test = check_extu     },
  { .name = "ins"        , .test = check_ins      },
  {0, 0}
};

int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if(get_core_id() == 0) {
    return run_suite(testcases);
  }

  return 0;
}

void test_check(testresult_t *result, const char* asm_str, uint32_t act, uint32_t exp) {
  if (act != exp) {
    result->errors++;
    printf("%s: Actual %08x, expected %08x\n", asm_str, act, exp);
  }
}

#define util_check_rrr(result, asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      act = prefix ## _d[i]; \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(result, asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rrr_sci(result, asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      act = prefix ## _d[i]; \
      asm volatile (asm_str " %[c], %[a], " #imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(result, asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rrri(result, asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      act = prefix ## _d[i]; \
      asm volatile (asm_str " %[c], %[a], %[b], " #imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(result, asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rr(result, asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(result, asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rr_sci(result, asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], " imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(result, asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_rri(result, asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b], " #imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(result, asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_ri(result, asm_str, i, prefix, imm) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], " #imm "\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(result, asm_str, act, prefix ## _exp[i]); \
    }

#define util_check_r(result, asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a]\n" \
                    : [c] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i])); \
      test_check(result, asm_str, act, prefix ## _exp[i]); \
    }

void check_add(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check add (standard addition)
  //-----------------------------------------------------------------
  util_check_rr(result, ADD, i, g_add);

  //-----------------------------------------------------------------
  // Check pv.add.*
  //-----------------------------------------------------------------
  util_check_rr    (result, PV_ADD_H,     i, g_add_h);
  util_check_rr    (result, PV_ADD_H_SC,  i, g_add_h_sc);
  util_check_rr_sci(result, PV_ADD_H_SCI, i, g_add_h_sci, SCI_IMM);

  util_check_rr    (result, PV_ADD_B,     i, g_add_b);
  util_check_rr    (result, PV_ADD_B_SC,  i, g_add_b_sc);
  util_check_rr_sci(result, PV_ADD_B_SCI, i, g_add_b_sci, SCI_IMM);
}

void check_sub(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check sub (standard subtraction)
  //-----------------------------------------------------------------
  util_check_rr(result, SUB, i, g_sub);

  //-----------------------------------------------------------------
  // Check pv.sub.*
  //-----------------------------------------------------------------
  util_check_rr    (result, PV_SUB_H,     i, g_sub_h);
  util_check_rr    (result, PV_SUB_H_SC,  i, g_sub_h_sc);
  util_check_rr_sci(result, PV_SUB_H_SCI, i, g_sub_h_sci, SCI_IMM);

  util_check_rr    (result, PV_SUB_B,     i, g_sub_b);
  util_check_rr    (result, PV_SUB_B_SC,  i, g_sub_b_sc);
  util_check_rr_sci(result, PV_SUB_B_SCI, i, g_sub_b_sci, SCI_IMM);
}

void check_avg(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.avg.h
  //-----------------------------------------------------------------
  util_check_rr    (result, PV_AVG_H,     i, g_avg_h);
  util_check_rr    (result, PV_AVG_H_SC,  i, g_avg_h_sc);
  util_check_rr_sci(result, PV_AVG_H_SCI, i, g_avg_h_sci, SCI_IMM);

  //-----------------------------------------------------------------
  // Check pv.avgu.h
  //-----------------------------------------------------------------
  util_check_rr    (result, PV_AVGU_H,     i, g_avgu_h);
  util_check_rr    (result, PV_AVGU_H_SC,  i, g_avgu_h_sc);
  util_check_rr_sci(result, PV_AVGU_H_SCI, i, g_avgu_h_sci, SCI_IMM);


  //-----------------------------------------------------------------
  // Check lv32.avg.b
  //-----------------------------------------------------------------
  util_check_rr    (result, PV_AVG_B,     i, g_avg_b);
  util_check_rr    (result, PV_AVG_B_SC,  i, g_avg_b_sc);
  util_check_rr_sci(result, PV_AVG_B_SCI, i, g_avg_b_sci, SCI_IMM);


  //-----------------------------------------------------------------
  // Check pv.avgu.b
  //-----------------------------------------------------------------
  util_check_rr    (result, PV_AVGU_B,     i, g_avgu_b);
  util_check_rr    (result, PV_AVGU_B_SC,  i, g_avgu_b_sc);
  util_check_rr_sci(result, PV_AVGU_B_SCI, i, g_avgu_b_sci, SCI_IMM);
}

void check_abs(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int act;

  util_check_r(result, ABS,  i, g_abs);

  //-----------------------------------------------------------------
  // Check pv.abs.h
  //-----------------------------------------------------------------
  util_check_r(result, PV_ABS_H, i, g_abs_h);

  //-----------------------------------------------------------------
  // Check pv.abs.b
  //-----------------------------------------------------------------
  util_check_r(result, PV_ABS_B, i, g_abs_b);
}

void check_ext(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.extract.*
  //-----------------------------------------------------------------
  util_check_ri(result, PV_EXT_H, i, g_ext_h0, 0);
  util_check_ri(result, PV_EXT_H, i, g_ext_h1, 1);

  util_check_ri(result, PV_EXT_B, i, g_ext_b0, 0);
  util_check_ri(result, PV_EXT_B, i, g_ext_b1, 1);
  util_check_ri(result, PV_EXT_B, i, g_ext_b2, 2);
  util_check_ri(result, PV_EXT_B, i, g_ext_b3, 3);
}

void check_extu(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int act;

  //-----------------------------------------------------------------
  // Check pv.extractu.*
  //-----------------------------------------------------------------
  util_check_ri(result, PV_EXTU_H, i, g_extu_h0, 0);
  util_check_ri(result, PV_EXTU_H, i, g_extu_h1, 1);

  util_check_ri(result, PV_EXTU_B, i, g_extu_b0, 0);
  util_check_ri(result, PV_EXTU_B, i, g_extu_b1, 1);
  util_check_ri(result, PV_EXTU_B, i, g_extu_b2, 2);
  util_check_ri(result, PV_EXTU_B, i, g_extu_b3, 3);
}

void check_ins(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int act;
  //-----------------------------------------------------------------
  // Check pv.insert
  //-----------------------------------------------------------------
  util_check_rrr_sci(result, PV_INS_H, i, g_ins_h0, 0);
  util_check_rrr_sci(result, PV_INS_H, i, g_ins_h1, 1);

  util_check_rrr_sci(result, PV_INS_B, i, g_ins_b0, 0);
  util_check_rrr_sci(result, PV_INS_B, i, g_ins_b1, 1);
  util_check_rrr_sci(result, PV_INS_B, i, g_ins_b2, 2);
  util_check_rrr_sci(result, PV_INS_B, i, g_ins_b3, 3);
}
