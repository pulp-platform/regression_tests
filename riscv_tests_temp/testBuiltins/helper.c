// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "pulp.h"
#include "math.h"

long long add64(long long a, long long b) {
  return a + b;
}

long long div64(long long a, long long b) {
  return a / b;
}
long long mul64(long long a, long long b) {
  return a * b;
}


int add(int a, int b) {
  return a + b;
}

int div(int a, int b) {
  return a / b;
}

int mul(int a, int b) {
  return a * b;
}


float fmul(float a, float b) {
  return a * b;
}

double fmul64(double a, double b) {
  return a * b;
}

float fdiv(float a, float b) {
  return a / b;
}

double fdiv64(double a, double b) {
  return a / b;
}

float fadd(float a, float b) {
  return a + b;
}

double fadd64(double a, double b) {
  return a + b;
}

float fcos(float a, float b) {
  return cosf(a);
}

double fcos64(double a, double b) {
  return cos(a);
}

float fsqrt(float a, float b) {
  return sqrtf(a);
}

double fsqrt64(double a, double b) {
  return sqrt(a);
}
