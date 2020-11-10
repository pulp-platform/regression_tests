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

#define BUFFER_SIZE 16
#define UART_BAUDRATE 115200

int uart_read_nb(int uart_id, void *buffer, uint32_t size)
{
  int periph_id = ARCHI_UDMA_UART_ID(uart_id);
  int channel = UDMA_CHANNEL_ID(periph_id);

  unsigned int base = hal_udma_channel_base(channel);

  plp_udma_enqueue(base, (int)buffer, size, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_8);

  //uart_wait_rx_done(periph_id);

  return 0;
}

int uart_write_nb(int uart_id, void *buffer, uint32_t size)
{
  int periph_id = ARCHI_UDMA_UART_ID(uart_id);
  int channel = UDMA_CHANNEL_ID(periph_id) + 1;

  unsigned int base = hal_udma_channel_base(channel);

  plp_udma_enqueue(base, (int)buffer, size, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_8);

  //uart_wait_tx_done(periph_id);

  return 0;
}

int main()
{

int error = 0;
int tx_buffer[BUFFER_SIZE] = {'S','t','a','y',' ','a','t',' ','h','o','m','e','!','!','!','!'};
int rx_buffer[BUFFER_SIZE];

for (int u = 0; u < 2; ++u)
{
  for (int j = 0; j < BUFFER_SIZE; ++j)
  {
    rx_buffer[j] = 0;
  }

  printf("[%d, %d] Start test uart %d\n",  get_cluster_id(), get_core_id(), u);
  uart_open(u,UART_BAUDRATE);

  for (int i = 0; i < BUFFER_SIZE; ++i)
  {
    uart_write_nb(u,tx_buffer + i,1); //--- non blocking write
    uart_read(u,rx_buffer + i,1);     //--- blocking read
    
    if (tx_buffer[i] == rx_buffer[i])
    {
      printf("PASS: tx %c, rx %c\n", tx_buffer[i],rx_buffer[i]);
    }else{
      printf("FAIL: tx %c, rx %c\n", tx_buffer[i],rx_buffer[i]);
      error++;
    }
  }
}
  return error;
}
