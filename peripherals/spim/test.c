#include <stdio.h>
#include "pulp.h"

#define BUFFER_SIZE 16

#define CONFPAD(bit,val) val<<(2*(bit%16))
int main()
{
    unsigned int nb,delay;
    int error = 0;
    unsigned int tx_cfg;
    unsigned int nb_words, nb_bits;
    //clock configuration buffer
    int buffer_clk_cfg[] = { SPI_CMD_CFG(1,1,1) };
    unsigned int writeval;

    //enable all perigheral clock
    plp_udma_cg_set(plp_udma_cg_get() | (0xffffffff));


    for (unsigned char u = 0; u < 3; ++u) {
      printf("\n uDMA SPIM test %0d\n", u);

      if (u==2)
      {
        printf("Configure PAD\n", u);
        //Set pads 28,29,30,31 to config 2'b10
        writeval = CONFPAD(28,2) | CONFPAD(29,2) | CONFPAD(30,2) | CONFPAD(31,2);
        printf("Set PADFUNC1 to 0x%x\n", writeval);
        hal_apb_soc_padfun_set(1,writeval);
      }


      //send clock configuration
      plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)buffer_clk_cfg , sizeof(buffer_clk_cfg), UDMA_CHANNEL_CFG_SIZE_32);

      //transmit 8 bits data
      //////////////////////
      //send clear command
      plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)0, 0, UDMA_CHANNEL_CFG_CLEAR);

      //rx/tx data buffers
      volatile unsigned char tx_buffer_char[8] = {0x5A, 0x82, 0x00, u, 0x03, 0x01, 0x02, 0x03 };
      volatile unsigned char rx_buffer_char[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


      //set config for 8 bits data
      nb_words = sizeof(tx_buffer_char) / sizeof(tx_buffer_char[0]);
      nb_bits = sizeof(tx_buffer_char[0])*8;
      //command buffer
      int tx_buffer_cmd[] =   {
                                  SPI_CMD_SOT(0),
                                  SPI_CMD_FUL( sizeof(tx_buffer_char) / sizeof(tx_buffer_char[0]), 0, sizeof(tx_buffer_char[0])*8, 0),
                                  SPI_CMD_EOT(0,0)
                              };


      for (nb = 0; nb < 2; nb++ )
      {
        plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u) ,  (int)tx_buffer_char, sizeof(tx_buffer_char), UDMA_CHANNEL_CFG_SIZE_8);
        plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u) ,  (int)rx_buffer_char, sizeof(rx_buffer_char), UDMA_CHANNEL_CFG_SIZE_8);
        plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u),  (int)tx_buffer_cmd , sizeof(tx_buffer_cmd), UDMA_CHANNEL_CFG_SIZE_32);
        for (delay = 0; delay < 2000; delay++){
          asm volatile("nop");
        }
        printf("Rx buffer: ");
        for(int i=0; i < 8;i++)
        {
            printf("%02X ", rx_buffer_char[i]);
            if (rx_buffer_char[i]!=tx_buffer_char[i])
            {
              printf("\nError on RX buffer, expected : 0x%02x\n", tx_buffer_char[i]);
              error++;
            }
        }
        printf("\n");
    }
  }

  return error;
}