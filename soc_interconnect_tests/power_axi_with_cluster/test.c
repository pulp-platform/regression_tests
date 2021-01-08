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

#define ADDR1   0x10000000 // SOC_MEM_MAP_AXI_PLUG_START_ADDR 32'h1000_0000
#define ADDR2   0x10200000  // SOC_MEM_MAP_AXI_PLUG_END_ADDR 32'h1040_0000
#define DATA1   0x55555555
#define DATA2   0xAAAAAAAA
#define VCDADDR 0x1C000000
#define REG_CORESTATUS 0x1C000000  

uint32_t addr[2] = { ADDR1, ADDR2};
uint32_t data[2] = { DATA1, DATA2};

int main()
{

  uint32_t read ;
  uint32_t i ;
  uint32_t idx = 0 ;


  *(int*)(REG_CORESTATUS) = 0xABBAABBA;
   for(uint32_t i=addr[0]; i<addr[1]; i+=1028) {

      pulp_write32(i,data[idx]);
      read=pulp_read32(i);
      #ifdef CHECK_CORRECTNESS
      if (read!=data[idx]) 
      {
       printf("error at %d\n",i);
       break; }
      #endif
       idx=1-idx;

  }

  
  *(int*)(VCDADDR) = 0xDEADCACA;
  

  return 0;
  
}
