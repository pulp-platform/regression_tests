// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include <stdint.h>
#include <stdarg.h>

unsigned int __attribute__ ((noinline)) fn_10arg(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g, uint32_t h, uint32_t i, uint32_t j) {
  if(a != 0x0 || b != 0x1 || c != 0x2 || d != 0x3 || e != 0x4 || f != 0x5 || g != 0x6 || h != 0x7 || i != 0x8 || j != 0x9) {
    return 1;
  }

  return 0;
}

unsigned int __attribute__ ((noinline)) fn_10arg_var(uint32_t a, ...) {
  va_list ptr;

  va_start(ptr, a);

  uint32_t b = va_arg(ptr, uint32_t);
  uint32_t c = va_arg(ptr, uint32_t);
  uint32_t d = va_arg(ptr, uint32_t);
  uint32_t e = va_arg(ptr, uint32_t);
  uint32_t f = va_arg(ptr, uint32_t);
  uint32_t g = va_arg(ptr, uint32_t);
  uint32_t h = va_arg(ptr, uint32_t);
  uint32_t i = va_arg(ptr, uint32_t);
  uint32_t j = va_arg(ptr, uint32_t);

  va_end(ptr);

  if(a != 0x0 || b != 0x1 || c != 0x2 || d != 0x3 || e != 0x4 || f != 0x5 || g != 0x6 || h != 0x7 || i != 0x8 || j != 0x9) {
    return 1;
  }

  return 0;
}

unsigned int __attribute__ ((noinline)) fn_10arg_var_proto(uint32_t a, ...) {
  va_list ptr;

  va_start(ptr, a);

  uint32_t b = va_arg(ptr, uint32_t);
  uint32_t c = va_arg(ptr, uint32_t);
  uint32_t d = va_arg(ptr, uint32_t);
  uint32_t e = va_arg(ptr, uint32_t);
  uint32_t f = va_arg(ptr, uint32_t);
  uint32_t g = va_arg(ptr, uint32_t);
  uint32_t h = va_arg(ptr, uint32_t);
  uint32_t i = va_arg(ptr, uint32_t);
  uint32_t j = va_arg(ptr, uint32_t);

  va_end(ptr);

  if(a != 0x0 || b != 0x1 || c != 0x2 || d != 0x3 || e != 0x4 || f != 0x5 || g != 0x6 || h != 0x7 || i != 0x8 || j != 0x9) {
    return 1;
  }

  return 0;
}
