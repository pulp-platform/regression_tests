// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.


////////////////////////////////////////////////////////////////////////////////
// Company:        IIS @ ETHZ - Federal Institute of Technology               //
//                                                                            //
// Engineer:       Andreas Traber - atraber@student.ethz.ch                   //
//                                                                            //
// Additional contributions by:                                               //
//                                                                            //
//                                                                            //
// Description: This testbench checks the basic functionality of:             //
// - l.ff1                                                                    //
// - l.fl1                                                                    //
// - l.cnt                                                                    //
// - l.clb                                                                    //
//                                                                            //
//                                                                            //
// Revision:                                                                  //
// Revision v0.1 - File Created                                               //
//                                                                            //
//                                                                            //
//                                                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "pulp.h"

#define FF1 "p.ff1"
#define FL1 "p.fl1"
#define CNT "p.cnt"
#define CLB "p.clb"


void check_ff1(testresult_t *result, void (*start)(), void (*stop)());
void check_fl1(testresult_t *result, void (*start)(), void (*stop)());
void check_cnt(testresult_t *result, void (*start)(), void (*stop)());
void check_clb(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "ff1",        .test = check_ff1          },
  { .name = "fl1",        .test = check_fl1          },
  { .name = "cnt",        .test = check_cnt          },
  { .name = "clb",        .test = check_clb          },
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

void check_ff1(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t act;
  uint32_t exp;
  uint32_t a;

  a = 0x110110;
  asm volatile (FF1 " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.ff1", act,  4);

  a = 0x110100;
  asm volatile (FF1 " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.ff1", act,  8);

  unsigned int i;
  for(i = 0; i < 32; i++) {
    a = 1 << i;

    asm volatile (FF1 " %[d], %[a]"
                  : [d] "+r" (act)
                  : [a] "r"  (a));

    exp = i;

    check_uint32(result, "l.ff1", act,  exp);
  }

  for(i = 0; i < 32; i++) {
    a = (1 << 31) | (1 << i);

    asm volatile (FF1 " %[d], %[a]"
                  : [d] "+r" (act)
                  : [a] "r"  (a));

    exp = i;

    check_uint32(result, "l.ff1", act,  exp);
  }
}


void check_fl1(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t act;
  uint32_t exp;
  uint32_t a;

  a = 0x4FFFFFFF;
  asm volatile (FL1 " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.fl1", act,  30);

  a = 0x00000001;
  asm volatile (FL1 " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.fl1", act,  0);

  unsigned int i;
  for(i = 0; i < 32; i++) {
    a = 1 << i;

    asm volatile (FL1 " %[d], %[a]"
                  : [d] "+r" (act)
                  : [a] "r"  (a));

    exp = i;

    check_uint32(result, "l.fl1", act,  exp);
  }

  for(i = 0; i < 32; i++) {
    a = 1 | (1 << i);

    asm volatile (FL1 " %[d], %[a]"
                  : [d] "+r" (act)
                  : [a] "r"  (a));

    exp = i;

    check_uint32(result, "l.fl1", act,  exp);
  }
}

void check_cnt(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t act;
  uint32_t exp;
  uint32_t a;

  a = 0x10101010;
  asm volatile (CNT " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.cnt", act,  4);

  a = 0xFFFFFFFF;
  asm volatile (CNT " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.cnt", act,  32);

  a = 0x00000000;
  asm volatile (CNT " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.cnt", act,  0);

  unsigned int i, j;
  for(i = 0; i < 32; i++) {
    a = 0;
    for(j = 0; j <= i; j++)
      a |= 1 << j;

    asm volatile (CNT " %[d], %[a]"
                  : [d] "+r" (act)
                  : [a] "r"  (a));

    exp = i + 1;

    check_uint32(result, "l.cnt", act,  exp);
  }
}


unsigned int clb_golden(int32_t val) {
  unsigned int var_out;

  if (val == 0)
    var_out = 0;
  else if (val == (int32_t)0xffffffff)
    var_out = 31;
  else {
    if (val < 0)
      val = ~val;

    for(var_out = 0; val < (int32_t)0x40000000; var_out++)
      val <<= 1;
  }

  return var_out;
}

void check_clb(testresult_t *result, void (*start)(), void (*stop)()) {
  uint32_t act;
  uint32_t exp;
  uint32_t a;

  a = 0x7FFFFFFF;
  asm volatile (CLB " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.clb", act,  0);

  a = 0x00000001;
  asm volatile (CLB " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.clb", act,  30);

  a = 0xF0000000;
  asm volatile (CLB " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.clb", act,  3);

  a = 0xFFFFFFFE;
  asm volatile (CLB " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.clb", act,  30);

  a = 0x00000000;
  asm volatile (CLB " %[d], %[a]"
                : [d] "+r" (act)
                : [a] "r"  (a));

  check_uint32(result, "l.clb", act,  0);

  unsigned int i;
  for(i = 0; i < 32; i++) {
    a = 1 << i;

    asm volatile (CLB " %[d], %[a]"
                  : [d] "+r" (act)
                  : [a] "r"  (a));

    exp = clb_golden(a);

    check_uint32(result, "l.clb", act,  exp);
  }
}
