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
 * Mantainer: Luca Valente (luca.valente2@unibo.it)
 */

#include <stdio.h>
#include "pulp.h"

//ARCHI_APB_SOC_CTRL_ADDR (pad mux regs are in the soc control)
//ARCHI_GPIO_ADDR (base address of the GPIO IP)
//--- this application writes and read back all the pad mux regs

#define REG_PADFUN0_OFFSET 0x10
#define REG_PADFUN1_OFFSET 0x14
#define REG_PADFUN2_OFFSET 0x18
#define REG_PADFUN3_OFFSET 0x1C

#define REG_PADCFG0_OFFSET  0x24
#define REG_PADCFG1_OFFSET  0x28
#define REG_PADCFG2_OFFSET  0x2C
#define REG_PADCFG3_OFFSET  0x30
#define REG_PADCFG4_OFFSET  0x34
#define REG_PADCFG5_OFFSET  0x38
#define REG_PADCFG6_OFFSET  0x3C
#define REG_PADCFG7_OFFSET  0x40
#define REG_PADCFG8_OFFSET  0x44
#define REG_PADCFG9_OFFSET  0x48
#define REG_PADCFG10_OFFSET 0x4C
#define REG_PADCFG11_OFFSET 0x50
#define REG_PADCFG12_OFFSET 0x54
#define REG_PADCFG13_OFFSET 0x58
#define REG_PADCFG14_OFFSET 0x5C
#define REG_PADCFG15_OFFSET 0x60

#define OUT 1
#define IN  0

int pad_fun_offset[4] = {REG_PADFUN0_OFFSET,REG_PADFUN1_OFFSET,REG_PADFUN2_OFFSET,REG_PADFUN3_OFFSET};
int pad_cfg_offset[16] = {REG_PADCFG0_OFFSET,REG_PADCFG1_OFFSET,REG_PADCFG2_OFFSET,REG_PADCFG3_OFFSET,REG_PADCFG4_OFFSET,REG_PADCFG5_OFFSET,REG_PADCFG6_OFFSET,REG_PADCFG7_OFFSET,REG_PADCFG8_OFFSET,REG_PADCFG9_OFFSET,REG_PADCFG10_OFFSET,REG_PADCFG11_OFFSET,REG_PADCFG12_OFFSET,REG_PADCFG13_OFFSET,REG_PADCFG14_OFFSET,REG_PADCFG15_OFFSET};


uint32_t lfsr(uint32_t input)
{
    uint32_t start_state = 0x02A0ACE1;  /* Any nonzero start state will work. */
    int32_t lfsr = start_state;

    for (int i = 0; i < input; ++i)
    {
      lfsr ^= lfsr >> 7;
      lfsr ^= lfsr << 9;
      lfsr ^= lfsr >> 13;
    }

    return lfsr % 48;
}

uint32_t configure_gpio(uint32_t number, uint32_t direction){
  //uint32_t which_reg_fun = number / 16; //select the correct register 
  uint32_t address ; // = ARCHI_APB_SOC_CTRL_ADDR + pad_fun_offset[which_reg_fun];

  //--- set alternate 1 on GPIO
  uint32_t value_wr ; // = pulp_read32(address);
  // value_wr |= (1 << ((number - which_reg_fun*16)*2));
  // pulp_write32(address, value_wr);

  //--- set GPIO
  if(number < 32)
  {
    if (direction == OUT)
    {
      //--- enable GPIO
      address = ARCHI_GPIO_ADDR + GPIO_GPIOEN_OFFSET;
      value_wr = pulp_read32(address); 
      value_wr &= ~(1 << number);
      pulp_write32(address, value_wr);
      //--- set direction
      address = ARCHI_GPIO_ADDR + GPIO_PADDIR_OFFSET;
      pulp_write32(address, value_wr);
    }else if (direction == IN){
      //--- enable GPIO
      address = ARCHI_GPIO_ADDR + GPIO_GPIOEN_OFFSET;
      value_wr = pulp_read32(address); 
      value_wr |= (1 << number);
      pulp_write32(address, value_wr);
      //--- set direction
      address = ARCHI_GPIO_ADDR + GPIO_PADDIR_OFFSET;
      pulp_write32(address, value_wr);
    }
  }else{  
    if (direction == OUT)
    {
      //--- enable GPIO
      address = ARCHI_GPIO_ADDR + GPIO_GPIOEN_32_63_OFFSET;
      value_wr = pulp_read32(address); 
      value_wr &= ~(1 << (number-32));
      pulp_write32(address, value_wr);
      //--- set direction
      address = ARCHI_GPIO_ADDR + GPIO_PADDIR_32_63_OFFSET;
      pulp_write32(address, value_wr);
    }else if (direction == IN){
      //--- enable GPIO
      address = ARCHI_GPIO_ADDR + GPIO_GPIOEN_32_63_OFFSET;
      value_wr = pulp_read32(address); 
      value_wr |= (1 << (number-32));
      pulp_write32(address, value_wr);
      //--- set direction
      address = ARCHI_GPIO_ADDR + GPIO_PADDIR_32_63_OFFSET;
      pulp_write32(address, value_wr);
    }
  }

  while(pulp_read32(address) != value_wr);

}

uint32_t set_gpio(uint32_t number, uint32_t value){
  uint32_t value_wr;
  uint32_t address;
  if (number < 32)
  {
    address = ARCHI_GPIO_ADDR + GPIO_PADOUT_OFFSET;
    value_wr = pulp_read32(address);
    if (value == 1)
     {
      value_wr |= (1 << (number));
     }else{
      value_wr &= ~(1 << (number));
     }
    pulp_write32(address, value_wr);
  }else{
    address = ARCHI_GPIO_ADDR + GPIO_PADOUT_32_63_OFFSET;
    value_wr = pulp_read32(address); 
    if (value == 1)
     {
      value_wr |= (1 << (number % 32));
     }else{
      value_wr &= ~(1 << (number % 32));
     }
    pulp_write32(address, value_wr);
  }

  while(pulp_read32(address) != value_wr);
}

uint32_t get_gpio(uint32_t number){
  uint32_t value_rd;
  uint32_t address;
  if (number < 32)
  {
    address = ARCHI_GPIO_ADDR + GPIO_PADIN_OFFSET;
    value_rd = pulp_read32(address); 
  }else{
    address = ARCHI_GPIO_ADDR + GPIO_PADIN_32_63_OFFSET;
    value_rd = pulp_read32(address); 
  }
  return value_rd & (1 << (number % 32));
}


int main()
{


  uint32_t error = 0;
  uint32_t address;
  uint32_t val_wr = 0x00000000;
  uint32_t val_rd = 0;
  uint32_t gpio_out;
  uint32_t gpio_in;
  uint32_t val_rd1;
  uint32_t gpio_val;

  printf("[%d, %d] Start test\n",  get_cluster_id(), get_core_id());

  printf("GPIO[i+16] driven by GPIO[i] in Hardware \n");

  printf("[PRE-TEST] errors = %0d\n",error);
  
  printf("Set GPIOs[31:16] as input, the remaining as output\n");
  address = ARCHI_GPIO_ADDR + GPIO_PADDIR_OFFSET;
  val_wr = 0x0000FFFF;
  pulp_write32(address, val_wr);
  while(pulp_read32(address) != val_wr);
    
    

  printf("Setting first 16 GPIOS outputs=1\n");
  address = ARCHI_GPIO_ADDR + GPIO_PADOUT_OFFSET;
  val_wr = pulp_read32(address);
  val_wr = 0x0000FFFF;
  pulp_write32(address, val_wr);
  while(pulp_read32(address) != val_wr);

  printf("Enable clock to allow sampling for GPIOs[31:16]\n");
  address = ARCHI_GPIO_ADDR + GPIO_GPIOEN_OFFSET;
  val_wr = 0xFFFF0000;
  pulp_write32(address, val_wr);
  while(pulp_read32(address) != val_wr);

  printf("Reading Input and Output register\n");
  address = ARCHI_GPIO_ADDR + GPIO_PADIN_OFFSET;
  val_rd = pulp_read32(address);
  printf("gpio_in  reg value = %08x\n", val_rd); // gpio_val);
  address = ARCHI_GPIO_ADDR + GPIO_PADOUT_OFFSET;
  val_rd1 = pulp_read32(address);
  printf("gpio_out reg value = %08x\n", val_rd1);
  printf("expected gpio_in values = %08x\n", (val_rd1 << 16));
  error = val_rd ^ (val_rd1 << 16);
  
  printf("[POST-TEST] errors = %0d\n",error);

  return error;
}
