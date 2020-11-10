#include <stdio.h>
#include "pulp.h"

//#define REG_RX_SADDR     0x00
//#define REG_RX_SIZE      0x04
//#define REG_RX_CFG       0x08
//#define REG_RX_INTCFG    0x0C
//#define REG_TX_SADDR     0x10
//#define REG_TX_SIZE      0x14
//#define REG_TX_CFG       0x18
//#define REG_TX_INTCFG    0x1C
//#define REG_STATUS       0x20
//#define REG_UART_SETUP   0x24
//#define REG_ERROR        0x28
//#define REG_IRQ_EN       0x2C
//#define REG_VAL_wrID     0x30
//#define REG_DATA         0x34

int main()
{

  uint8_t wr_reg_offsets[14] = {0x00,0x04,0x08,0x0C,0x10,0x14,0x18,0x1C,0x20,0x24,0x28,0x2C,0x30,0x34};

  int error = 0;
  int address;
  int val_wr = 0xffffffff;
  int cg_val;
  static inline int val_rd = 0;

  for (int u = 0; u < 2; ++u)
  {
    plp_udma_cg_set(plp_udma_cg_get() | (1<<u));
    printf("UART # %d\n", u);
    for (int i = 0; i < 14; ++i)
    {
      address = ARCHI_UDMA_ADDR + UDMA_PERIPH_OFFSET(ARCHI_UDMA_UART_ID(u)) + wr_reg_offsets[i]; 
      pulp_write32(address, val_wr); 
      printf("write %x @ %x\n", val_wr, address);
    }
    cg_val = plp_udma_cg_get();
    cg_val &= ~(1<<u);
    plp_udma_cg_set(cg_val);
  }

  return error;
}
