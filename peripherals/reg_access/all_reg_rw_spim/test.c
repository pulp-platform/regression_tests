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

int main()
{

  uint8_t wr_reg_offsets[14] = {0x00,0x04,0x08,0x0C,0x10,0x14,0x18,0x1C,0x20,0x24,0x28,0x2C,0x30};

  int error = 0;
  int address;
  int val_wr = 0xffffffff;
  int cg_val;
  static inline int val_rd = 0xdeadbeef;

for (int u = 0; u < 1; ++u)
{
  plp_udma_cg_set(plp_udma_cg_get() | (1<<ARCHI_UDMA_SPIM_ID(u)));
  printf("QSPI # %d\n", u);
  for (int i = 0; i < 6; ++i)
  {
    address = ARCHI_UDMA_ADDR + UDMA_PERIPH_OFFSET(ARCHI_UDMA_SPIM_ID(u)) + wr_reg_offsets[i]; 
    pulp_write32(address, val_wr); 
    printf("write %x @ %x, ", val_wr, address);
  }
  cg_val = plp_udma_cg_get();
  cg_val &= ~(1<<ARCHI_UDMA_SPIM_ID(u));
  plp_udma_cg_set(cg_val);
}

  return error;
}
