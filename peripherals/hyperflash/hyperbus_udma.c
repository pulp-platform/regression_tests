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
//#include <rt/rt_api.h>
//#include <rt/rt_freq.h>
#include <stdint.h>
#include "hyperbus_test.h"
//#include </home/vivid/pulpissimo/pulp-sdk/runtime/hal/include/hal/eu/eu_v3.h>


#define BUFFER_SIZE 8


int main() {

    int tx_buffer[BUFFER_SIZE],rx_buffer[BUFFER_SIZE];
    int a;
    int *p;
    int hyper_addr, hyper_waddr;
    udma_hyper_flash_setup();
    int error = 0;
    int pass = 0;
    //udma_hyperflash_wpwrite(1, 0x1234, 0);
    //udma_hyper_dread(2, 2, (unsigned int)rx_buffer, 0,0);
 
    for (int i=0; i< (BUFFER_SIZE); i++)
    {
        tx_buffer[i] = 0xffff0000+i;
    } 
    hyper_waddr = 0;
    udma_hyperflash_bwrite((BUFFER_SIZE*2), hyper_waddr,(unsigned int) tx_buffer,0);
    printf("Busy: %d \n", udma_hyper_busy(0));
    hyper_addr = 0;
    udma_hyper_dread((BUFFER_SIZE*4), hyper_addr, (unsigned int)rx_buffer, 0,0);
    udma_hyper_wait(0); 

    for (int i=0; i< BUFFER_SIZE; i++)
     {      
       printf("rx_buffer[%d] = %x, expected: %x \n", i, rx_buffer[i], tx_buffer[i]); 
       error += rx_buffer[i] ^ tx_buffer[i];
      }
   if (error!=0) { 
       pass=1;
       printf("errors\n");
       }
  
   return pass;
    
}
