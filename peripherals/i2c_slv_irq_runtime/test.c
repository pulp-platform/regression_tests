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
 *
 * Author: Corrado Bonfanti (corrado.bonfanti@unibo.it)
 * Author: Antonio Mastrandrea (a.mastrandrea@unibo.it)
 */

#include <stdio.h>
#include "pulp.h"

#define I2CSLAVE_START_ADDR         0X1A140000
#define REG1    0x00    //
#define REG2    0x04    //
#define REG3    0x08    //

#define MTVEC 0x305
#define MIE   0X304

int var_glb = 0;

__attribute__((interrupt)) static void __irq_handler() {
  var_glb = 1;
}

int main()
{
  volatile unsigned int *r1, *r2,*r3;
  volatile char *rc;
  volatile int boot_addr;
  char check_var;
  int tmp;
  int error = 0;
  r1 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG1);
  r2 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG2);
  r3 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG3);

  printf("\nREAD I2C registers (default values):\n");
  printf("\tr1       is 0x%x, r1 = %p\n", *(r1), r1);
  printf("\tr2       is 0x%x, r2 = %p\n", *(r2), r2);
  printf("\tr3       is 0x%x, r3 = %p\n", *(r3), r3);

  printf("READ buffer:\n");
  printf("Address &rc:   %p\n",&rc);
  printf("\t%d\t",0);

  // Write address of rc[0] to REG2 (BASE ADDR of i2c slave):
  printf("write address of rc[0] to REG2:\n");
  rc = (char *)(*(r2));
  printf("\tNew BASE ADDRESS of i2c slave is 0x%x\n", rc);

  // Set to '0' all elements pointed by r2
  for(int i=0;i<256;i++) {
    rc[i] = 0;
  }

  // Set mtvec address to the proper value
  hal_spr_write(MTVEC, 0x1C008001);
  // enable interrupts (i2c slave bmc) MSTATUS
  hal_irq_enable();
  //set MIE(11) to 1
  asm volatile ("csrs %0, %1" : : "I" (MIE), "r"(1<<ARCHI_FC_EVT_I2C_SLV_BMC));

  // Interrupts mask in the ITC
  rt_irq_mask_set(1 << ARCHI_FC_EVT_I2C_SLV_BMC);
  // Interrupt handler
  rt_irq_set_handler(ARCHI_FC_EVT_I2C_SLV_BMC, __irq_handler);

  // Enable interrupt (bit 0 of register 3)
  tmp = *r3;
  *r3 = tmp | 0x1;

  int j=1;

  printf("Wait for I2C BMC slave receive data and write it into L2\n");
  while (var_glb==0) {
    hal_itc_wait_for_interrupt();
  };

  // Clean interrupt mask
  rt_irq_clr(1 << ARCHI_FC_EVT_I2C_SLV_BMC);
  rt_irq_mask_clr(1 << ARCHI_FC_EVT_I2C_SLV_BMC);
  
  printf("READ buffer after i2c transaction:\n");

  for(int i=0;i<256;i++)
  {
    check_var = i;
    if (rc[i] != check_var) {
      printf("Error at L2 address %p, received value = 0x%02x, expected = 0x%02x\n", &rc[i], rc[i], check_var);
      error++;
    }
  }

  if (error == 0) {
    printf("Test succeeded\n");
  }
  else {
    printf("Test failed\n");
  }

  return error;
}
