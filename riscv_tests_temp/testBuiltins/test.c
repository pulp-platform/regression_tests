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

#define NB_DIV 256
#define NB_ADD 256
#define NB_MUL 256
#define NB_COS 64
#define NB_SQRT 64
#define NB_FLOAT_DIV 128
#define NB_FLOAT_ADD 128
#define NB_FLOAT_MUL 128

long long add64(long long a, long long b);
long long div64(long long a, long long b);
int add(int a, int b);
int div(int a, int b);

float fmul(float a, float b);
double fmul64(double a, double b);

float fadd(float a, float b);
double fadd64(double a, double b);

float fdiv(float a, float b);
double fdiv64(double a, double b);

float fcos(float a, float b);
double fcos64(double a, double b);

float fsqrt(float a, float b);
double fsqrt64(double a, double b);

#define bench(str, time, func, nbIter, vala, valb)	\
  do { \
    int i; \
    reset_timer(); \
    for (i=0; i<nbIter; i++) \
      { \
	start_timer();				\
	func(vala, valb); \
	stop_timer();				\
      } \
    time = get_time() / nbIter; \
  } while (0);

    //printf("%s cycles: %d\n", str, time);	\


int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if (get_core_id() != 0) return 0;

  unsigned int divC, div64C, addC, add64C, mulC, mul64C, fmulC, fmul64C, faddC, fadd64C, fdivC, fdiv64C, fcosC, fcos64C, fsqrtC, fsqrt64C;

  bench("Div", divC, div, NB_DIV, 0x38552eb9, 0x7);
  bench("Div64", div64C, div64, NB_DIV, 0x38552eb9820a1e6c, 0x7);
  bench("Add64", add64C, add64, NB_ADD, 0x38552eb9820a1e6c, 0x385a38e6c92ef625);
  bench("Add", addC, add, NB_ADD, 0x38552eb98, 0x385a38e6c);
  bench("Mul", mulC, mul, NB_MUL, 0x38552eb9, 0x385a38e6c);
  bench("Mul64", mul64C, mul64, NB_MUL, 0x38552eb9820a1e6c, 0x385a38e6c92ef625);

  bench("Float mul", fmulC, fmul, NB_FLOAT_MUL, 5.3826f, 230946.494f);
  //bench("Double mul", fmul64C, fmul64, NB_FLOAT_MUL, 544030.37252534, 34827432665.00833);

  bench("Float add", faddC, fadd, NB_FLOAT_ADD, 5.3826f, 230946.494f);
  //bench("Double add", fadd64C, fadd64, NB_FLOAT_ADD, 544030.37252534, 34827432665.00833);

  bench("Float div", fdivC, fdiv, NB_FLOAT_DIV, 5.3826f, 230946.494f);
  //bench("Double div", fdiv64C, fdiv64, NB_FLOAT_DIV, 544030.37252534, 34827432665.00833);

  bench("Float cos", fcosC, fcos, NB_COS, 1.84624f, 0.0f);
  //bench("Double cos", fcos64C, fcos64, NB_COS, 1.2038464653635, 0.0);

  bench("Float sqrt", fsqrtC, fsqrt, NB_SQRT, 3483.3343f, 0.0f);
  //bench("Double sqrt", fsqrt64C, fsqrt64, NB_SQRT, 286352323.987666, 0.0);

  printf("\n");
  printf("           32b  |     64b  |   float  |  double\n", divC, div64C, fdivC, fdiv64C);
  printf("----------------|----------|----------|--------\n");
  printf("Div     %6d  |  %6d  |  %6d  |  %6d\n", divC, div64C, fdivC, fdiv64C);
  printf("Add     %6d  |  %6d  |  %6d  |  %6d\n", addC, add64C, faddC, fadd64C);
  printf("Mul     %6d  |  %6d  |  %6d  |  %6d\n", mulC, mul64C, fmulC, fmul64C);
  printf("Cos          -  |       -  |  %6d  |  %6d\n", fcosC, fcos64C);
  printf("Sqrt         -  |       -  |  %6d  |  %6d\n", fsqrtC, fsqrt64C);


  return 0;
}
