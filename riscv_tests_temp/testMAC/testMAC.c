// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

// This testbench checks the basic functionality of the following instructions:
//
// mul
//
// p.mac
//
// p.mac.zl.zl
// p.mac.zl.zh
// p.mac.zh.zl
// p.mac.zh.zh
//
// p.mac.zl.sl
// p.mac.zl.sh
// p.mac.zh.sl
// p.mac.zh.sh
//
// p.mac.sl.zl
// p.mac.sl.zh
// p.mac.sh.zl
// p.mac.sh.zh
//
// p.mac.sl.sl
// p.mac.sl.sh
// p.mac.sh.sl
// p.mac.sh.sh

#include <stdio.h>
#include "pulp.h"

#include "testMAC_stimuli.h"


void check_mac(testresult_t *result, void (*start)(), void (*stop)());
void check_mac_subword(testresult_t *result, void (*start)(), void (*stop)());
void check_mul(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "mac",         .test = check_mac         },
  { .name = "mac_subword", .test = check_mac_subword },
  { .name = "mul",         .test = check_mul         },
  {0, 0},
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


#define util_check_mac(asm_str, i, act, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      act = prefix ## _c[i]; \
      asm volatile (asm_str " %[d], %[a], %[b];" \
                    : [d] "+r" (act) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r"  (prefix ## _b[i])); \
      check_uint32(result, asm_str, act, prefix ## _exp[i]); \
    }


void check_mul(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int tmp = 0;

  //-----------------------------------------------------------------
  // Check mul
  //-----------------------------------------------------------------
  for(i = 0; i < (sizeof(g_mul_a)/4); i++) {
    asm volatile ("mul %[d], %[a], %[b]\n"
                  : [d] "+r" (tmp)
                  : [a] "r"  (g_mul_a[i]),
                    [b] "r"  (g_mul_b[i]));
    check_uint32(result, "mul", tmp, g_mul_exp[i]);
  }
}


void check_mac(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int tmp = 0;

  //-----------------------------------------------------------------
  // Check p.mac
  //-----------------------------------------------------------------
  util_check_mac("p.mac", i, tmp, g_mac);
}

void check_mac_subword(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int tmp = 0;

  //-----------------------------------------------------------------
  // Check p.mac with subword selection
  //-----------------------------------------------------------------
  util_check_mac("p.macu", i, tmp, g_mac_zl_zl);
  util_check_mac("p.machhu", i, tmp, g_mac_zh_zh);

  util_check_mac("p.macs", i, tmp, g_mac_sl_sl);
  util_check_mac("p.machhs", i, tmp, g_mac_sh_sh);
}
