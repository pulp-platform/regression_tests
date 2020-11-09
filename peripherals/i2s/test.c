#include <stdio.h>
#include "pulp.h"
#include "gpio_bare.h"

#define BUFFER_SIZE 8
#define UART_BAUDRATE 115200

#define UDMA_I2S_OFFSET(id)           UDMA_PERIPH_OFFSET(ARCHI_UDMA_I2S_ID(id))
#define UDMA_I2S_RX_CHANNEL(id)        (ARCHI_UDMA_ADDR + UDMA_I2S_OFFSET(id) + UDMA_CHANNEL_RX_OFFSET)
#define UDMA_I2S_TX_CHANNEL(id)        (ARCHI_UDMA_ADDR + UDMA_I2S_OFFSET(id) + UDMA_CHANNEL_TX_OFFSET)

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


int main()
{

int error = 0;
//--- tx data buffer
int tx_buffer[BUFFER_SIZE] = {0x000000af,0x000000cf,0x000000cc,0x000000dd,0x000000ee,0x000000ff,0x00000011,0x00000022};
//--- rx buffer
int rx_buffer[BUFFER_SIZE];

for (int u = 0; u < 1; ++u)
{
  for (int j = 0; j < BUFFER_SIZE; ++j)
  {
    rx_buffer[j] = 0;
  }


  //--- clear the rx buffer
  for (int j = 0; j < BUFFER_SIZE; ++j)
  {
    rx_buffer[j] = 0;
  }

  printf("[%d, %d] Start test i2c %d\n",  get_cluster_id(), get_core_id(),u);

  //--- enable all the udma channels (see below for selective enable)
  plp_udma_cg_set(plp_udma_cg_get() | (0xffffffff));

  configure_gpio(28,OUT); // pad timer0_ch0
  configure_gpio(29,OUT); // pad timer0_ch1
  configure_gpio(30,OUT); // pad timer0_ch2
  configure_gpio(31,OUT); // pad timer0_ch3

  configure_gpio(34,OUT); // pad cam_data0
  configure_gpio(35,OUT); // pad cam_data1
  configure_gpio(36,OUT); // pad cam_data2
  configure_gpio(37,OUT); // pad cam_data3
  configure_gpio(38,OUT); // pad cam_data4

  set_gpio(28,1);
  set_gpio(28,0);
  set_gpio(28,1);

  set_gpio(29,0);
  set_gpio(30,1);
  set_gpio(31,0);
  set_gpio(34,0);
  set_gpio(35,1);
  set_gpio(36,0);
  set_gpio(37,0);
  set_gpio(38,0);

  //--- get the base address of the SPIMx udma channels
  unsigned int udma_i2s_channel_base = hal_udma_channel_base(UDMA_CHANNEL_ID(ARCHI_UDMA_I2S_ID(u)));
  printf("uDMA i2s%d base channel address %8x\n", u,udma_i2s_channel_base);

  //plp_udma_enqueue(UDMA_I2C_DATA_ADDR(u) ,  (int)rx_buffer     , 8, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_8);
  int i2s_mst_cfg = 0;
  int i2s_slv_cfg = 0;
  int i2s_clk_cfg = 0;

  pulp_write32(udma_i2s_channel_base + UDMA_I2S_I2S_MST_SETUP_OFFSET, 0x00000000);
  pulp_write32(udma_i2s_channel_base + UDMA_I2S_I2S_SLV_SETUP_OFFSET, 0x00000000);
  pulp_write32(udma_i2s_channel_base + UDMA_I2S_I2S_CLKCFG_SETUP_OFFSET, 0x00000000);


  i2s_mst_cfg |= (1 << UDMA_I2S_I2S_MST_SETUP_MASTER_EN_BIT) | (7 << UDMA_I2S_I2S_MST_SETUP_MASTER_BITS_BIT) | (0 << UDMA_I2S_I2S_MST_SETUP_MASTER_WORDS_BIT);
  i2s_slv_cfg &= ~(1 << UDMA_I2S_I2S_SLV_SETUP_SLAVE_EN_BIT);
  i2s_clk_cfg |= (1 << UDMA_I2S_I2S_CLKCFG_SETUP_MASTER_CLK_EN_BIT) | (1 << UDMA_I2S_I2S_CLKCFG_SETUP_MASTER_CLK_DIV_BIT) | (1 << UDMA_I2S_I2S_CLKCFG_SETUP_COMMON_CLK_DIV_BIT);

  pulp_write32(udma_i2s_channel_base + UDMA_I2S_I2S_MST_SETUP_OFFSET, i2s_mst_cfg);  //--- important! clock must be enabled after setting the peripheral

  pulp_write32(udma_i2s_channel_base + UDMA_I2S_I2S_CLKCFG_SETUP_OFFSET, i2s_clk_cfg);
  
  //--- data transmission
  plp_udma_enqueue(UDMA_I2S_TX_CHANNEL(u) ,  (int)tx_buffer , 32, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
  wait_cycles(30000);
  plp_udma_enqueue(UDMA_I2S_RX_CHANNEL(u) ,  (int)rx_buffer , 32, UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
}
  return error;
}
