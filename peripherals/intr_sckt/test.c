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
 * Mantainer: Corrado Bonfanti (corrado.bonfanti@unibo.it)
 */

#include <stdio.h>
#include "pulp.h"
#include "flash_page.h"

#define REG_SPI_DIRECTION 0x60

#define OUT 1
#define IN  0

#define BUFFER_SIZE 16

#define TEST_PAGE_SIZE 256
#define TEST_PAGE_SIZE_SLV 254

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

uint32_t set_intr_sckt_reg( uint32_t value){
  uint32_t value_wr;
  uint32_t address;

  address = ARCHI_APB_SOC_CTRL_ADDR + REG_SPI_DIRECTION;
  value_wr = pulp_read32(address);
  if (value == 1)
   {
    value_wr |= (1);
    printf( "Set the select signal value for the inter-socket SPI peripheral to %1x (slave), at address:  %8x\n",  value_wr, address);
   }else{
    value_wr &= ~(1);
    printf( "Set the select signal value for the inter-socket SPI peripheral to %1x (master), at address:  %8x\n",  value_wr, address);
   }
  pulp_write32(address, value_wr);

  while(pulp_read32(address) != value_wr);
}

uint32_t read_intr_sckt_reg(){
  uint32_t value_rd;
  uint32_t address;

  address = ARCHI_APB_SOC_CTRL_ADDR + REG_SPI_DIRECTION;
  value_rd = pulp_read32(address);
  printf( "Returned value from inter-socket register (address: %8x): %1x \n", address, value_rd);
  return value_rd;
}

//
// The code below can be used to check if the burst length is correctly stored in the registers of the SPI slave module
//
void check_regs_spi_slv(volatile int *rx_slv_test, int reg2, int reg3, int ch_index, int *tx_buffer_cmd_read_reg2, int *tx_buffer_cmd_read_reg3)  {

  int poll_var;
  int u;

  u = ch_index;

  //--- read back the length of the burst to transfer from reg2 (wrap_length low) of the SPI slave module
  plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) , (unsigned int)&rx_slv_test[0], 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
  plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_read_reg2 , 6*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

  do {
    poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_RX_ADDR(u));
    printf("Polling (read reg2) remaining bytes =  %d\n", poll_var);
    poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_RX_ADDR(u));
    printf("Polling (read reg2): poll_var = %8x\n", poll_var);
  } while(poll_var != 0);

  printf("rx_slv_test[0] = %d, expected = %d\n", rx_slv_test[0], reg2);

  //--- read back the length of the burst to transfer from reg3 (wrap_length high) of the SPI slave module
  plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) , (unsigned int)&rx_slv_test[1], 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
  plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_read_reg3, 6*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

  do {
    poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_RX_ADDR(u));
    printf("Polling (read reg3): remaining bytes =  %d\n", poll_var);
    poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_RX_ADDR(u));
    printf("Polling (read reg3): poll_var = %8x\n", poll_var);
  } while(poll_var != 0);

  printf("rx_slv_test[1] = %d, expected = %d\n", rx_slv_test[1], reg3);
}

int main()
  {
    int error = 0;
    volatile int buffer_slv_test[2];
    volatile int rx_slv_test;
    int *pt_test;
    unsigned int udma_spim_channel_base;
    int u;
    int poll_var;

    //--- refer to this manual for the commands
    //--- https://www.cypress.com/file/216421/download

    //--- command sequence master
    int tx_buffer_cmd_program[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                              SPI_CMD_SOT(1),
                                              SPI_CMD_SEND_CMD(0x06,8,0),
                                              SPI_CMD_EOT(0,0),
                                              SPI_CMD_SOT(1),
                                              SPI_CMD_SEND_CMD(0x12,8,0),
                                              SPI_CMD_TX_DATA(4,4,8,0,0), //--- write 4B addr to the addr buffer (first 4 bytes of the "page" array)
                                              SPI_CMD_TX_DATA(TEST_PAGE_SIZE,0,8,0,0), //--- write 256B page data to the page buffer
                                              SPI_CMD_EOT(0,0)};

    int addr_buffer[4] = {0x00,0x00,0x00,0x00}; //--- reading address
    int tx_buffer_cmd_read[BUFFER_SIZE]    = {SPI_CMD_CFG(1,0,0),
                                              SPI_CMD_SOT(1),
                                              SPI_CMD_SEND_CMD(0x13,8,0), //--- read command
                                              SPI_CMD_TX_DATA(4,4,8,0,0), //--- send the read address
                                              SPI_CMD_RX_DATA(TEST_PAGE_SIZE,0,8,0,0),
                                              SPI_CMD_EOT(0,0)};

    int rx_page[TEST_PAGE_SIZE];
    int tx_buffer_cmd_read_WIP[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                               SPI_CMD_SOT(1),
                                               SPI_CMD_SEND_CMD(0x07,8,0),
                                               SPI_CMD_RX_DATA(1,1,8,0,0),
                                               SPI_CMD_EOT(0,0)};
    //--- command sequence: slave test
    int tx_buffer_cmd_program_slv[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                                  SPI_CMD_SOT(1),
                                                  SPI_CMD_SEND_CMD(0x02,8,0),
                                                  SPI_CMD_TX_DATA(1,0,32,0,0), //--- write 4B addr
                                                  SPI_CMD_TX_DATA(1,0,32,0,0), //--- write 4B data
                                                  SPI_CMD_EOT(0,0)};

    int tx_buffer_cmd_read_slv[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                               SPI_CMD_SOT(1),
                                               SPI_CMD_SEND_CMD(0x0b,8,0), //--- read command
                                               SPI_CMD_TX_DATA(1,0,32,0,0), //--- send the read address
                                               SPI_CMD_DUMMY(31),
                                               SPI_CMD_DUMMY(1),
                                               SPI_CMD_RX_DATA(1,0,32,0,0),
                                               SPI_CMD_EOT(0,0)};
    //--- command sequence: burst slave test
    int tx_buffer_cmd_program_slv_burst[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                                  SPI_CMD_SOT(1),
                                                  SPI_CMD_SEND_CMD(0x02,8,0),
                                                  SPI_CMD_TX_DATA(1,0,32,0,0), //--- write 4B addr
                                                  SPI_CMD_TX_DATA(TEST_PAGE_SIZE_SLV,0,32,0,0), //--- write 256 words of data
                                                  SPI_CMD_EOT(0,0)};

    int tx_buffer_cmd_read_slv_burst[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                               SPI_CMD_SOT(1),
                                               SPI_CMD_SEND_CMD(0x0b,8,0), //--- read command
                                               SPI_CMD_TX_DATA(1,0,32,0,0), //--- send the read address
                                               SPI_CMD_DUMMY(31),
                                               SPI_CMD_DUMMY(1),
                                               SPI_CMD_RX_DATA(TEST_PAGE_SIZE_SLV,0,32,0,0),
                                               SPI_CMD_EOT(0,0)};

    int tx_buffer_cmd_write_reg2[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                                  SPI_CMD_SOT(1),
                                                  SPI_CMD_SEND_CMD(0x20,8,0),
                                                  SPI_CMD_TX_DATA(1,0,8,0,0), //--- write 4B data
                                                  SPI_CMD_EOT(0,0)};

    int tx_buffer_cmd_write_reg3[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                                  SPI_CMD_SOT(1),
                                                  SPI_CMD_SEND_CMD(0x30,8,0),
                                                  SPI_CMD_TX_DATA(1,0,8,0,0), //--- write 4B data
                                                  SPI_CMD_EOT(0,0)};

    int tx_buffer_cmd_read_reg2[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                               SPI_CMD_SOT(1),
                                               SPI_CMD_SEND_CMD(0x21,8,0), //--- read command
                                               SPI_CMD_DUMMY(24),
                                               SPI_CMD_RX_DATA(1,0,8,0,0),
                                               SPI_CMD_EOT(0,0)};

    int tx_buffer_cmd_read_reg3[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                               SPI_CMD_SOT(1),
                                               SPI_CMD_SEND_CMD(0x31,8,0), //--- read command
                                               SPI_CMD_DUMMY(24),
                                               SPI_CMD_RX_DATA(1,0,8,0,0),
                                               SPI_CMD_EOT(0,0)};


    u = 6;

    // Set inter-socket reg to '0' (master)
    set_intr_sckt_reg(0);

    printf("[%d, %d] Start test flash page programming over qspi %d\n",  get_cluster_id(), get_core_id(),u);

    //--- enable all the udma channels
    plp_udma_cg_set(plp_udma_cg_get() | (0xffffffff));

    //--- get the base address of the SPIMx udma channels
    udma_spim_channel_base = hal_udma_channel_base(UDMA_CHANNEL_ID(ARCHI_UDMA_SPIM_ID(u)));
    printf("uDMA spim%d base channel address %8x\n", u,udma_spim_channel_base);

    //--- write the flash page
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) ,  (int)page          ,TEST_PAGE_SIZE*4 + 4*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_program , 68, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    //--- wait until the page is written (we could use the WIP bit instead of waiting)
    wait_cycles(100000);

    //--- try to read back data
    plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) ,  (int)rx_page     , TEST_PAGE_SIZE*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) ,  (int)addr_buffer    , 4*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_read , 26, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    wait_cycles(100000);

    for (int i = 0; i < TEST_PAGE_SIZE; ++i)
    {
      printf("read %8x, expected %8x \n",rx_page[i],page[i+4]);
      if (rx_page[i] != page[i+4])
      {
        error++;
      }
    }

    u = 0;

    // Set inter-socket reg to '1' (slave)
    set_intr_sckt_reg(1);

    printf("[%d, %d] Start test flash page programming over qspi %d\n",  get_cluster_id(), get_core_id(),u);

    //--- enable all the udma channels
    plp_udma_cg_set(plp_udma_cg_get() | (0xffffffff));

    //--- get the base address of the SPIMx udma channels
    udma_spim_channel_base = hal_udma_channel_base(UDMA_CHANNEL_ID(ARCHI_UDMA_SPIM_ID(u)));
    printf("uDMA spim%d base channel address %8x\n", u,udma_spim_channel_base);

    //
    // ATOMC READ/WRITE OPERATIONS TOWARD THE SPI SLAVE MODULE
    //
    buffer_slv_test[0] = 1;
    buffer_slv_test[1] = 0;

    //--- write the length of the burst to store into reg2 (wrap_length low) of the SPI slave module
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) , (unsigned int)&buffer_slv_test[0], 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_write_reg2 , 5*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    do {
      poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write reg2): remaining bytes =  %d\n", poll_var);
      poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write reg2): poll_var = %8x\n", poll_var);
    } while(poll_var != 0);

    //--- write the length of the burst to store into reg3 (wrap_length high) of the SPI slave module
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) , (unsigned int)&buffer_slv_test[1], 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_write_reg3 , 5*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    do {
      poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write reg3): remaining bytes =  %d\n", poll_var);
      poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write reg3): poll_var = %8x\n", poll_var);
    } while(poll_var != 0);

    for (int j = 0; j < TEST_PAGE_SIZE_SLV-54; j++) {

      buffer_slv_test[0] = addr_slv_buff[j];
      buffer_slv_test[1] = data_slv_buff[j+1];

      //--- write to L2 using spi_master n0
      plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) , (unsigned int)buffer_slv_test, 2*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
      plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_program_slv , 6*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

      //--- polling to check if the transfer is completed (when channel SADDR register = 0)
      do {
        poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_TX_ADDR(u));
        printf("Polling (write) n%d: remaining bytes =  %d\n", j, poll_var);
        poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_TX_ADDR(u));
        printf("Polling (write) n%d: poll_var = %8x\n", j, poll_var);
      } while(poll_var != 0);

      //--- try to read back data from L2
      pt_test = (unsigned int *)buffer_slv_test[0];
      rx_slv_test = pulp_read32(pt_test);
      printf("Read (FC) n%d: rx_slv_test = %8x, at L2 memory address = %p, expected %8x \n", j, rx_slv_test, pt_test, buffer_slv_test[1]);
      rx_slv_test = 0;

      //--- try to read back data from L2 using spi_master n0
      plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) , (unsigned int)&rx_slv_test, 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
      plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) , (unsigned int)&buffer_slv_test[0], 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
      plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_read_slv , 8*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

      //--- polling to check if the transfer is completed (when channel SADDR register = 0)
      do {
        poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_RX_ADDR(u));
        printf("Polling (read) n%d: remaining bytes = %d\n", j, poll_var);
        poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_RX_ADDR(u));
        printf("Polling (read) n%d: poll_var = %8x\n", j, poll_var);
      } while(poll_var != 0);


      printf("Read (SPI master) n%d: rx_slv_test = %8x, expected %8x \n", j, rx_slv_test, buffer_slv_test[1]);

      if (rx_slv_test != buffer_slv_test[1])
      {
        error++;
      }

    }

    //
    // Burst of 254 write/read operations (arbitrarily chosen based on the number of data in the buffer in "flash_page.h") --> write 254 in two registers of 8 bits (00000000 11111110)
    //
    buffer_slv_test[0] = TEST_PAGE_SIZE_SLV & (255);         // Set the 8 least significant bits of the burst length
    buffer_slv_test[1] = (TEST_PAGE_SIZE_SLV & ~(255)) >> 8; // Set the 8 most significant bits of the burst length

    //--- write the length of the burst to store into reg2 (wrap_length low) of the SPI slave module
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) , (unsigned int)&buffer_slv_test[0], 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_write_reg2 , 5*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    do {
      poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write reg2): remaining bytes =  %d\n", poll_var);
      poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write reg2): poll_var = %8x\n", poll_var);
    } while(poll_var != 0);

    //--- write the length of the burst to store into reg3 (wrap_length high) of the SPI slave module
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) , (unsigned int)&buffer_slv_test[1], 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_write_reg3 , 5*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    do {
      poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write reg3): remaining bytes =  %d\n", poll_var);
      poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write reg3): poll_var = %8x\n", poll_var);
    } while(poll_var != 0);

    check_regs_spi_slv( &rx_slv_test, buffer_slv_test[0], buffer_slv_test[1], u, tx_buffer_cmd_read_reg2, tx_buffer_cmd_read_reg3);

    //--- write to L2 using spi_master n°0
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) , (unsigned int)data_slv_buff, (TEST_PAGE_SIZE_SLV+1)*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_program_slv_burst , 6*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    //--- polling to check if the transfer is completed (when channel SADDR register = 0)
    do {
      poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write burst) remaining bytes =  %d\n", poll_var);
      poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_TX_ADDR(u));
      printf("Polling (write burst): poll_var = %8x\n", poll_var);
    } while(poll_var != 0);

    buffer_slv_test[0] = data_slv_buff[0];

    /* For debug
    //--- try to read back data from L2
    pt_test = (unsigned int *)buffer_slv_test[0];
    for (int i = 0; i < TEST_PAGE_SIZE_SLV; i++) {
      rx_page[0] = pulp_read32(pt_test+i);
      printf("Read (FC burst): rx_page = %8x, at L2 memory address = %p, expected %8x\n", rx_page[0], pt_test+i, data_slv_buff[i+1]);
     }
    */

    rx_page[0] = 0;

    //--- try to read back data from L2 using spi_master n°0
    plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) , (unsigned int)rx_page, TEST_PAGE_SIZE_SLV*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) , (unsigned int)&buffer_slv_test[0], 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (unsigned int)tx_buffer_cmd_read_slv_burst , 8*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    //--- polling to check if the transfer is completed (when channel SADDR register = 0)
    do {
      poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_RX_ADDR(u));
      printf("Polling (read burst): remaining bytes = %d\n", poll_var);
      poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_RX_ADDR(u));
      printf("Polling (read burst): poll_var = %8x\n", poll_var);
    } while(poll_var != 0);

    for (int i = 0; i < TEST_PAGE_SIZE_SLV; i++) {
      printf("Read (SPI master burst): rx_page[%d] = %8x, expected %8x \n", i, rx_page[i], data_slv_buff[i+1] );

      if (rx_page[i] != data_slv_buff[i+1])
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
