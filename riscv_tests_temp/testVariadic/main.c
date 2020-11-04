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
#include <stdarg.h>

unsigned int fn_10arg_var_proto(uint32_t a, ...);
void  poison_stack();

void check_variadic(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "variadic",          .test = check_variadic },
  {0, 0}
};

int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  int retval = 0;
  poison_stack();

  if(get_core_id() == 0) {
    retval = run_suite(testcases);
  }

  return retval;
}

void check_variadic(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;

  poison_stack();

  if(fn_10arg(0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9) != 0) {
    result->errors++;
    printf("Using 10 arguments without protype has failed\n");
  }

  if(fn_10arg_var(0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9) != 0) {
    result->errors++;
    printf("Using 10 arguments variadic without protype has failed\n");
  }

  if(fn_10arg_var_proto(0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9) != 0) {
    result->errors++;
    printf("Using 10 arguments variadic with protype has failed\n");
  }
}

void __attribute__ ((noinline)) poison_stack() {
  unsigned int i;
  volatile uint32_t temp[100];

  for(i = 0; i < 100; i++)
    temp[i] = 0;
}
