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


void check_hwlp(testresult_t *result, void (*start)(), void (*stop)());
void check_same_end(testresult_t *result, void (*start)(), void (*stop)());
void check_csr(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "hwlp",     .test = check_hwlp     },
  { .name = "same_end", .test = check_same_end },
  { .name = "csr",      .test = check_csr      },
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


void check_hwlp(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int tmp = 0, tmp2 = 0;
  unsigned int i, j;

  //-----------------------------------------------------------------
  // Check HWLOOP with lp.starti/lp.endi/lp.count
  //-----------------------------------------------------------------

  // no RVC
  i = 0; j = 0;
  asm volatile (
      ".option norvc;"
      "lp.count x0, %[N];"
      "lp.endi x0, end44;"
      "lp.starti x0, start44;"
      "start44: addi %[i], %[i], 1;"
      "end44: addi %[j], %[j], 10;"
      : [i] "+r" (i), [j] "+r" (j)
      : [N] "r" (10)
  );
  check_uint32(result, "hwloop starti/endi/count: 4-4", i, 10);
  check_uint32(result, "hwloop starti/endi/count: 4-4", j, 100);

  // 2 then 4 byte instruction combo
  i = 0; j = 0;
  asm volatile (
      ".option norvc;"
      // save a0
      "mv %[tmp], a0;"
      "li a0, 0;"
      // loop
      "lp.count x0, %[N];"
      "lp.endi x0, end24;"
      "lp.starti x0, start24;"
      ".option rvc;"
      "start24: c.addi a0, 1;"
      ".option norvc;"
      "end24: addi %[j], %[j], 10;"
      // restore a0
      "mv %[i], a0;"
      "mv a0, %[tmp];"
      : [i] "+r" (i), [j] "+r" (j), [tmp] "+r" (tmp)
      : [N] "r" (10)
      : "a0"
  );
  check_uint32(result, "hwloop starti/endi/count: 2-4", i, 10);
  check_uint32(result, "hwloop starti/endi/count: 2-4", j, 100);

  // 4 then 2 byte instruction combo
  i = 0; j = 0;
  asm volatile (
      ".option norvc;"
      // save a0
      "mv %[tmp], a0;"
      "li a0, 0;"
      // loop
      "lp.count x0, %[N];"
      "lp.endi x0, end42;"
      "lp.starti x0, start42;"
      "start42: addi %[i], %[i], 1;"
      ".option rvc;"
      "end42: c.addi a0, 10;"
      ".option norvc;"
      // restore a0
      "mv %[j], a0;"
      "mv a0, %[tmp];"
      : [i] "+r" (i), [j] "+r" (j), [tmp] "+r" (tmp)
      : [N] "r" (10)
      : "a0"
  );
  check_uint32(result, "hwloop starti/endi/count: 4-2", i, 10);
  check_uint32(result, "hwloop starti/endi/count: 4-2", j, 100);

  // RVC only
  i = 0; j = 0;
  asm volatile (
      ".option norvc;"
      // save a0, a1
      "mv %[tmp], a0;"
      "mv %[tmp2], a1;"
      "li a0, 0;"
      "li a1, 0;"
      // loop
      "lp.count x0, %[N];"
      "lp.endi x0, end22;"
      "lp.starti x0, start22;"
      ".option rvc;"
      "start22: c.addi a0, 1;"
      "end22: c.addi a1, 10;"
      ".option norvc;"
      // restore a0, a1
      "mv %[i], a0;"
      "mv %[j], a1;"
      "mv a0, %[tmp];"
      "mv a1, %[tmp2];"
      : [i] "+r" (i), [j] "+r" (j), [tmp] "+r" (tmp), [tmp2] "+r" (tmp2)
      : [N] "r" (10)
      : "a0", "a1"
  );
  check_uint32(result, "hwloop starti/endi/count: 2-2", i, 10);
  check_uint32(result, "hwloop starti/endi/count: 2-2", j, 100);

  //-----------------------------------------------------------------
  // Check HWLOOP with lp.setup
  //-----------------------------------------------------------------
  i = 0; j = 0;
  asm volatile (
      ".option norvc;"
      "lp.setup x0, %[N], endstp;"
      "addi %[i], %[i], 1;"
      "endstp: addi %[j], %[j], 10;"
      : [i] "+r" (i), [j] "+r" (j)
      : [N] "r" (10)
  );
  check_uint32(result, "hwloop setup: 4-4", i, 10);
  check_uint32(result, "hwloop setup: 4-4", j, 100);

}

void check_same_end(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i, j;

  //-----------------------------------------------------------------
  // Check HWLOOP with lp.starti/lp.endi/lp.count and same endpoint
  //-----------------------------------------------------------------

  // no RVC
  i = 0; j = 0;
  asm volatile (
      ".option norvc;"
      "lp.count  x1, %[N];"
      "lp.endi   x1, endE;"
      "lp.starti x1, startE;"
      "startE: lp.count  x0, %[N];"
      "lp.endi   x0, endI;"
      "lp.starti x0, startI;"
      "startI: addi %[i], %[i], 1;"
      "endE: endI:   addi %[j], %[j], 10;"
      : [i] "+r" (i), [j] "+r" (j)
      : [N] "r" (10)
  );
  check_uint32(result, "hwloop starti/endi/count: 4-4", i, 10  * 10);
  check_uint32(result, "hwloop starti/endi/count: 4-4", j, 100 * 10);
}

void check_csr(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int start0, end0, cnt0;
  unsigned int start1, end1, cnt1;

  //-----------------------------------------------------------------
  // Check CSR hwlp access
  //-----------------------------------------------------------------

  asm volatile ("csrw 0x7C0, %0" :: "r" (0xdeadbeef) );
  asm volatile ("csrw 0x7C1, %0" :: "r" (0xbeefdead) );
  asm volatile ("csrw 0x7C2, %0" :: "r" (0xabbadead) );
  asm volatile ("csrw 0x7C4, %0" :: "r" (0xdeadabba) );
  asm volatile ("csrw 0x7C5, %0" :: "r" (0xabbaabba) );
  asm volatile ("csrw 0x7C6, %0" :: "r" (0xbabbabab) );

  asm volatile ("csrr %0, 0x7C0" : "=r" (start0) );
  asm volatile ("csrr %0, 0x7C1" : "=r" (end0) );
  asm volatile ("csrr %0, 0x7C2" : "=r" (cnt0) );
  asm volatile ("csrr %0, 0x7C4" : "=r" (start1) );
  asm volatile ("csrr %0, 0x7C5" : "=r" (end1) );
  asm volatile ("csrr %0, 0x7C6" : "=r" (cnt1) );

  check_uint32(result, "hwloop csr write/read: start 0", start0, 0xdeadbeef);
  check_uint32(result, "hwloop csr write/read: end 0",   end0,   0xbeefdead);
  check_uint32(result, "hwloop csr write/read: cnt 0",   cnt0,   0xabbadead);

  check_uint32(result, "hwloop csr write/read: start 1", start1, 0xdeadabba);
  check_uint32(result, "hwloop csr write/read: end 1",   end1,   0xabbaabba);
  check_uint32(result, "hwloop csr write/read: cnt 1",   cnt1,   0xbabbabab);
}
