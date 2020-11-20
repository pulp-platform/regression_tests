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
#include <stdint.h>
#include "./hyperbus_test.h"

#define BUFFER_SIZE 32

/* to execute this test, you have o instantiate the psram in tb_pulp.sv, setting USE_PSRAM to 1*/
int main() {

    int tx_buffer[BUFFER_SIZE],rx_buffer[BUFFER_SIZE];
    int a;
    int *p;
    int hyper_addr;
    int error =0;
    int id1, id2;

    udma_8spi_setup();
   
    for (int i=0; i< (BUFFER_SIZE); i++)
    {
        tx_buffer[i] = 0xafff0000+i;
    } 
    hyper_addr = 0;
    printf("hyper_addr: %d \n", hyper_addr);
    id1=udma_hyper_id_alloc();
    udma_hyper_dwrite((BUFFER_SIZE*4),(unsigned int) hyper_addr, (unsigned int)tx_buffer, 128,id1);
    printf("BUSY: %d ID:%d \n", udma_hyper_busy(id1), id1);

    id2=udma_hyper_id_alloc();
    udma_hyper_dread((BUFFER_SIZE*4),(unsigned int) hyper_addr, (unsigned int)rx_buffer, 128,id2);
    printf("BUSY: %d, ID:%d \n", udma_hyper_busy(id2),id2);
    udma_hyper_wait(id2);

    for (int i=0; i< BUFFER_SIZE; i++)
     {      
       printf("rx_buffer[%d] = %x, expectedf: %x \n", i, rx_buffer[i], tx_buffer[i]);
       error += rx_buffer[i] ^ tx_buffer[i];
   
      }

if(error!=0) printf("error \n");
else printf("ok\n");

printf("Fin. \n");
return error;
  
    
}

