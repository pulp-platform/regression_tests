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
#include "flash_page.h"

#define REG_PADFUN0_OFFSET  0x10
#define REG_PADFUN1_OFFSET  0x14
#define REG_PADFUN2_OFFSET  0x18
#define REG_PADFUN3_OFFSET  0x1C
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

#define BUFFER_SIZE 16

#define TEST_PAGE_SIZE 256

int pad_fun_offset[4] = {REG_PADFUN0_OFFSET,REG_PADFUN1_OFFSET,REG_PADFUN2_OFFSET,REG_PADFUN3_OFFSET};
int pad_cfg_offset[16] = {REG_PADCFG0_OFFSET,REG_PADCFG1_OFFSET,REG_PADCFG2_OFFSET,REG_PADCFG3_OFFSET,REG_PADCFG4_OFFSET,REG_PADCFG5_OFFSET,REG_PADCFG6_OFFSET,REG_PADCFG7_OFFSET,REG_PADCFG8_OFFSET,REG_PADCFG9_OFFSET,REG_PADCFG10_OFFSET,REG_PADCFG11_OFFSET,REG_PADCFG12_OFFSET,REG_PADCFG13_OFFSET,REG_PADCFG14_OFFSET,REG_PADCFG15_OFFSET};

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



uint32_t configure_gpio(uint32_t number, uint32_t direction, uint32_t alternate){
  uint32_t which_reg_fun = number / 16; //select the correct register 
  uint32_t address = ARCHI_APB_SOC_CTRL_ADDR + pad_fun_offset[which_reg_fun];

  //--- set alternate 1/2/3 on GPIO
  uint32_t value_wr = pulp_read32(address);
  value_wr |= ((alternate & 0x00000003) << ((number - which_reg_fun*16)*2));
  pulp_write32(address, value_wr);

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

int error = 0;

//--- refer to this manual for the commands
//--- https://www.cypress.com/file/216421/download

//--- command sequence
int tx_buffer_cmd_program[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                          SPI_CMD_SOT(0),
                                          SPI_CMD_SEND_CMD(0x06,8,0),
                                          SPI_CMD_EOT(0,0),
                                          SPI_CMD_SOT(0),
                                          SPI_CMD_SEND_CMD(0x12,8,0),
                                          SPI_CMD_TX_DATA(4,4,8,0,0), //--- write 4B addr to the addr buffer (first 4 bytes of the "page" array)
                                          SPI_CMD_TX_DATA(TEST_PAGE_SIZE,TEST_PAGE_SIZE,8,0,0), //--- write 256B page data to the page buffer
                                          SPI_CMD_EOT(0,0)}; 

int addr_buffer[4] = {0x00,0x00,0x00,0x00}; //--- reading address
int tx_buffer_cmd_read[BUFFER_SIZE]    = {SPI_CMD_CFG(1,0,0),
                                          SPI_CMD_SOT(0),
                                          SPI_CMD_SEND_CMD(0x13,8,0), //--- read command
                                          SPI_CMD_TX_DATA(4,4,8,0,0), //--- send the read address
                                          SPI_CMD_RX_DATA(TEST_PAGE_SIZE,TEST_PAGE_SIZE,8,0,0),
                                          SPI_CMD_EOT(0,0)};

int rx_page[TEST_PAGE_SIZE];
int tx_buffer_cmd_read_WIP[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                           SPI_CMD_SOT(0),
                                           SPI_CMD_SEND_CMD(0x07,8,0),
                                           SPI_CMD_RX_DATA(1,1,8,0,0),
                                           SPI_CMD_EOT(0,0)};

int u = 0; //--- select spi0


printf("[%d, %d] Start test flash page programming over qspi %d\n",  get_cluster_id(), get_core_id(),u);

configure_gpio(28,OUT,1); //--- using this GPIO as CS for the flash
set_gpio(28,1);

//--- enable all the udma channels
plp_udma_cg_set(plp_udma_cg_get() | (0xffffffff));

//--- get the base address of the SPIMx udma channels
unsigned int udma_spim_channel_base = hal_udma_channel_base(UDMA_CHANNEL_ID(ARCHI_UDMA_SPIM_ID(u)));
set_gpio(28,0);
printf("uDMA spim%d base channel address %8x\n", u,udma_spim_channel_base);
set_gpio(28,1);

//--- write the flash page
plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) ,  (int)page          ,TEST_PAGE_SIZE*4 + 4*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_program , 68, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

//--- wait until the page is written (we could use the WIP bit instead of waiting)
wait_cycles(50000);

//--- try to read back data
plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) ,  (int)rx_page     , TEST_PAGE_SIZE*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) ,  (int)addr_buffer    , 4*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_read , 26, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

wait_cycles(50000);

for (int i = 0; i < TEST_PAGE_SIZE; ++i)
{
  printf("read %8x, expected %8x \n",rx_page[i],page[i+4]);
  if (rx_page[i] != page[i+4])
  {
    error++;
  }
}

  if (error == 0)
  {
    printf("TEST SUCCEDED\n");
  }else{
    printf("TEST FAILED with %d errors\n", error);
  }

  return error;
}
