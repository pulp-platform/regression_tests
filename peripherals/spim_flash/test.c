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
 * Mantainer: Luca Valente (luca.valente2@unibo.it), Corrado Bonfanti (corrado.bonfanti@unibo.it)
 */

#include <stdio.h>
#include "pulp.h"
#include "flash_page.h"

#define BUFFER_SIZE 16

#define TEST_PAGE_SIZE 256

int main()
{

int error = 0;
int u = 0;
int poll_var;

//--- refer to this manual for the commands
//--- https://www.cypress.com/file/216421/download

//--- command sequence
int tx_buffer_cmd_program[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                          SPI_CMD_SOT(0),
                                          SPI_CMD_SEND_CMD(0x06,8,0),
                                          SPI_CMD_EOT(0,0),
                                          SPI_CMD_SOT(0),
                                          SPI_CMD_SEND_CMD(0x12,8,0),
                                          SPI_CMD_TX_DATA(4,0,8,0,0), //--- write 4B addr to the addr buffer (first 4 bytes of the "page" array)
                                          SPI_CMD_TX_DATA(TEST_PAGE_SIZE,TEST_PAGE_SIZE,8,0,0), //--- write 256B page data to the page buffer
                                          SPI_CMD_EOT(0,0)};

int addr_buffer[4] = {0x00,0x00,0x00,0x00}; //--- reading address
int tx_buffer_cmd_read[BUFFER_SIZE]    = {SPI_CMD_CFG(1,0,0),
                                          SPI_CMD_SOT(0),
                                          SPI_CMD_SEND_CMD(0x13,8,0), //--- read command
                                          SPI_CMD_TX_DATA(4,0,8,0,0), //--- send the read address
                                          SPI_CMD_RX_DATA(TEST_PAGE_SIZE,0,8,0,0),
                                          SPI_CMD_EOT(0,0)};

int rx_page[TEST_PAGE_SIZE];
int tx_buffer_cmd_read_WIP[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                           SPI_CMD_SOT(0),
                                           SPI_CMD_SEND_CMD(0x05,8,0),
                                           SPI_CMD_RX_DATA(1,0,8,0,0),
                                           SPI_CMD_EOT(0,0)};

volatile int sr1;
int tx_buffer_cmd_erase[BUFFER_SIZE] = {SPI_CMD_CFG(1,0,0),
                                           SPI_CMD_SOT(0),
                                           SPI_CMD_SEND_CMD(0x06,8,0),
                                           SPI_CMD_EOT(0,0),
                                           SPI_CMD_SOT(0),
                                           SPI_CMD_SEND_CMD(0x60,8,0),
                                           SPI_CMD_EOT(0,0)};

volatile int rems_resp[6];
int tx_buffer_cmd_read_ID[BUFFER_SIZE]    = {SPI_CMD_CFG(1,0,0),
                                          SPI_CMD_SOT(0),
                                          SPI_CMD_SEND_CMD(0x9F,8,0), //--- read command
                                          SPI_CMD_RX_DATA(6,0,8,0,0),
                                          SPI_CMD_EOT(0,0)};

 for (u=0;u<1;u++) { // test SPI1

    //--- enable all the udma channels
    plp_udma_cg_set(plp_udma_cg_get() | (0xffffffff));
    
    /*
    //--- erase the flash
    printf("[%d, %d] Erase entire flash content over qspi %d\n",  get_cluster_id(), get_core_id(),u);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_erase , 28, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    //--- check WIP ("Work-In-Progress" flag of the "Status Register 1" of the flash memory)
    sr1 = 0;
    do {
      plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) ,  (unsigned int)&sr1, 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
      plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_read_WIP, 20, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
      //--- polling to check if the transfer is completed (when channel SADDR register = 0)
      do {
        poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_RX_ADDR(u));
        poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_RX_ADDR(u));
      } while(poll_var != 0);
      sr1 &= (1);
    } while( sr1 != 0);
    */

    printf("[%d, %d] Start test flash page programming over qspi %d\n",  get_cluster_id(), get_core_id(),u);
    
    //--- get the base address of the SPIMx udma channels
    unsigned int udma_spim_channel_base = hal_udma_channel_base(UDMA_CHANNEL_ID(ARCHI_UDMA_SPIM_ID(u)));

    printf("uDMA spim%d base channel address %8x\n", u,udma_spim_channel_base);


    //--- check flash ID for debugging (refer to the manual)
    for(int i = 0; i < 6; i++) {
      rems_resp[i] = 0;
    }
    plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) ,  (unsigned int)rems_resp, 6*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_read_ID, 20, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    //--- polling to check if the transfer is completed (when the "SADDR" register of the SPI channel is equal to 0)
    do {
      poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_RX_ADDR(u));
      poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_RX_ADDR(u));
    } while(poll_var != 0);

    for(int i = 0; i < 6; i++) {
      printf("rems_resp[%d] = %8x\n", i, rems_resp[i]);
    }

    //--- write the flash page
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) ,  (int)page          ,TEST_PAGE_SIZE*4 + 4*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_program , 36, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    //--- check WIP ("Work-In-Progress" flag of the "Status Register 1" of the flash memory)
    sr1 = 0;
    do {
      plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) ,  (unsigned int)&sr1, 1*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
      plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_read_WIP, 20, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
      //--- polling to check if the transfer is completed (when the "SADDR" register of the SPI channel is equal to 0)
      do {
        poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_RX_ADDR(u));
        poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_RX_ADDR(u));
      } while(poll_var != 0);
      sr1 &= (1);
    } while( sr1 != 0);

    //--- try to read back data
    plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) ,  (int)rx_page     , TEST_PAGE_SIZE*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) ,  (int)addr_buffer    , 4*4, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
    plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd_read , 26, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

    //--- polling to check if the transfer is completed (when the "SADDR" register of the SPI channel is equal to 0)
    do {
      poll_var = pulp_read32(UDMA_CHANNEL_SIZE_OFFSET + UDMA_SPIM_RX_ADDR(u));
      poll_var = pulp_read32(UDMA_CHANNEL_SADDR_OFFSET + UDMA_SPIM_RX_ADDR(u));
    } while(poll_var != 0);

    for (int i = 0; i < TEST_PAGE_SIZE; ++i)
    {
      printf("read %8x, expected %8x \n",rx_page[i],page[i+4]);
      if (rx_page[i] != page[i+4])
      {
        error++;
      }
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
