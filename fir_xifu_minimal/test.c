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

#include <stdio.h>

int main()
{

  // // inst[4:2]=110 [6:5]=10 [1:0]=11
  // parameter logic [6:0] INSTR_OPCODE = 7'b1011011;

  // // R type
  // parameter logic [2:0] INSTR_XFIRDOTP_FUNCT3 = 3'b010;

  // // I type
  // parameter logic [2:0] INSTR_XFIRLW_FUNCT3 = 3'b000;

  // // S type
  // parameter logic [2:0] INSTR_XFIRSW_FUNCT3 = 3'b001;

  unsigned int x = 0x01020304;
  unsigned int y = 0x01010101;
  unsigned int z = 0;
  unsigned int px = (unsigned int) &x;
  unsigned int py = (unsigned int) &y;
  unsigned int pz = (unsigned int) &z;

  // load t0 / x5
  asm volatile("addi t0, %0, 0" ::"r"(px));
  // load t1 / x6
  asm volatile("addi t1, %0, 0" ::"r"(py));
  // load t2 / x7
  asm volatile("addi t2, %0, 0" ::"r"(pz));

  // XFIRLW xr0, 0(t0)
  asm volatile(".word (0x000     << 20) /* imm    */ | \
                      (0b00101   << 15) /* rs1    */ | \
                      (0b000     << 12) /* funct3 */ | \
                      (0b00000   <<  7) /* rd     */ | \
                      (0b1011011 <<  0) /* opcode */   \n");

  // XFIRLW xr1, 0(t1)
  asm volatile(".word (0x000     << 20) /* imm    */ | \
                      (0b00110   << 15) /* rs1    */ | \
                      (0b000     << 12) /* funct3 */ | \
                      (0b00001   <<  7) /* rd     */ | \
                      (0b1011011 <<  0) /* opcode */   \n");

  // XFIRDOTP xr2, xr1, xr0
  asm volatile(".word (0x0       << 25) /* empty  */ | \
                      (0b00001   << 20) /* rs2    */ | \
                      (0b00000   << 15) /* rs1    */ | \
                      (0b010     << 12) /* funct3 */ | \
                      (0b00010   <<  7) /* rd     */ | \
                      (0b1011011 <<  0) /* opcode */   \n");

  // XFIRSW 0(t2), xr2
  asm volatile(".word (0x00      << 25) /* imm_hi */ | \
                      (0b00010   << 20) /* rs2    */ | \
                      (0b00111   << 15) /* rs1    */ | \
                      (0b001     << 12) /* funct3 */ | \
                      (0b00000   <<  7) /* imm_lo */ | \
                      (0b1011011 <<  0) /* opcode */   \n");

  if(z == 0x40a06) {
    printf("Hello %08x!\n", z);
    return 0;
  }
  else {
    printf("No bueno %08x!\n", z);
    return 1;
  }

}
