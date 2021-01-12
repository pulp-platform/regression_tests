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

#define ADDR1   0x1c01AAAA
#define ADDR2   0x1c080000 
#define DATA1   0x55555555
#define DATA2   0xAAAAAAAA
#define VCDADDR 0x10000000
#define REG_CORESTATUS 0x1C000000  

uint32_t addr[2] = { ADDR1, ADDR2};
uint32_t data[2] = { DATA1, DATA2};

int main()
{

  uint32_t read ;
  uint32_t idx = 0;
  uint32_t error=0;
  uint32_t i;
  *(int*)(REG_CORESTATUS) = 0xABBAABBA;

   for( i=addr[0]; i<addr[1]; i+=1024) {

      pulp_write32(i,data[idx]);
      read=pulp_read32(i);
      if(read!=data[idx]) {error=1; break;}
      idx=1-idx;
  }
  
  *(int*)(REG_CORESTATUS) = 0xDEADCACA;
  

  return error;
  
}
