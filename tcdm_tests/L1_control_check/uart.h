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

#define UART_STOP_BITS 1
#define LSB_FIRST

int myputchar(char c) {
  // start bit
  gpio_set(0);
  wait_cycles(UART_SYMBOL_CYCLES);
  for (int i=0; i<8; i++) {
#ifdef LSB_FIRST
    char ci = (c >> i);
#else
    char ci = (c >> (8-i-1));
#endif
    gpio_set(ci);
    wait_cycles(UART_SYMBOL_CYCLES);
  }
  gpio_set(1);
  wait_cycles(UART_SYMBOL_CYCLES*UART_STOP_BITS);
  return 0;
}
    
static void putint(
   int x
) {
   int i,j;
   char c;
   unsigned int integer = x;
   unsigned int integer_bcd[10]; // max precision of 15 digits
   unsigned nb_integer_digits = 0;
   // 3) convert integer to BCD
   for(i=0; i<10; i++) {
      integer_bcd[i] = integer % 10;
      integer = integer / 10;
      if (integer == 0) {
         nb_integer_digits = i+1;
         // break;
      }
   }
   // 5) print to char
   for(j=nb_integer_digits-1,i=1; j>=0; j--,i++) {
      c = ((char) integer_bcd[j]) + 48;
      myputchar(c);
   }
   myputchar('\n');
}
