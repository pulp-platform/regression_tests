#include <stdio.h>
#include "pulp.h"

int main()
{

  uint8_t wr_reg_offsets[14] = {0x00,0x04,0x08,0x0C,0x10,0x14,0x18,0x1C,0x20,0x24};

  int error = 0;
  int address;
  int val_wr = 0xffffffff;
  int cg_val;
  static inline int val_rd = 0xdeadbeef;

for (int u = 0; u < 2; ++u)
{
  plp_udma_cg_set(plp_udma_cg_get() | (1<<ARCHI_UDMA_I2C_ID(u)));
  printf("I2C # %d\n", u);
  for (int i = 0; i < 10; ++i)
  {
    address = ARCHI_UDMA_ADDR + UDMA_PERIPH_OFFSET(ARCHI_UDMA_I2C_ID(u)) + wr_reg_offsets[i]; 
    pulp_write32(address, val_wr); 
    printf("write %x @ %x\n", val_wr, address);
  }
  cg_val = plp_udma_cg_get();
  cg_val &= ~(1<<ARCHI_UDMA_I2C_ID(u));
  plp_udma_cg_set(cg_val);
}

  return error;
}

