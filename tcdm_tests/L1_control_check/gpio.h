/*
 * Copyright 2019 Francesco Conti <francesco.conti88@gmail.com>
 *
 * Adapted from https://github.com/russm/lfsr64
 * This is a simple 32-bit linear feedback shift register, printing
 * pseudo-random bytes to stdout.
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "pulp.h"

static inline void wait_cycles(const unsigned cycles)
{
  /**
   * Each iteration of the loop below will take four cycles on RI5CY (one for
   * `addi` and three for the taken `bnez`; if the instructions hit in the
   * I$).  Thus, we let `i` count the number of remaining loop iterations and
   * initialize it to a fourth of the number of clock cyles.  With this
   * initialization, we must not enter the loop if the number of clock cycles
   * is less than four, because this will cause an underflow on the first
   * subtraction.
   */
  register unsigned threshold;
  asm volatile("li %[threshold], 4" : [threshold] "=r" (threshold));
  asm volatile goto("ble %[cycles], %[threshold], %l2"
          : /* no output */
          : [cycles] "r" (cycles), [threshold] "r" (threshold)
          : /* no clobbers */
          : __wait_cycles_end);
  register unsigned i = cycles >> 2;
__wait_cycles_start:
  // Decrement `i` and loop if it is not yet zero.
  asm volatile("addi %0, %0, -1" : "+r" (i));
  asm volatile goto("bnez %0, %l1"
          : /* no output */
          : "r" (i)
          : /* no clobbers */
          : __wait_cycles_start);
__wait_cycles_end:
  return;
}

static inline void gpio_set(char c) {
  *(((volatile int *) (ARCHI_GPIO_ADDR + ARCHI_GPIO_PADDIR_OUT))) = c & 0x1;
}
