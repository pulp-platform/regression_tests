/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Mantainer: Luca Valente luca.valente2@unibo.it
 */

#include "pulp.h"
#include "stdio.h"
#define ADDR1   0x1c01AAAA // SOC_MEM_MAP_AXI_PLUG_START_ADDR 32'h1000_0000
#define ADDR2   0x1c01AAAA  // SOC_MEM_MAP_AXI_PLUG_END_ADDR 32'h1040_0000
#define DATA1   0x55555555
#define DATA2   0xAAAAAAAA
#define VCDADDR 0x1C000000
#define REG_CORESTATUS 0x1C000000  


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


uint32_t addr[2] = { ADDR1, ADDR2};
uint32_t data[2] = { DATA1, DATA2};

int main()
{

  uint32_t read[2] ;



  *(int*)(REG_CORESTATUS) = 0xABBAABBA;

      *(uint32_t *)(addr[0]) = data[0];
      
      wait_cycles(20000);

      read[0]=pulp_read32(addr[0]);
      
  
  *(int*)(VCDADDR) = 0xDEADCACA;
  

  return 0;
  
}
