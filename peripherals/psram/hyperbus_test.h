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


#include <pulp.h>

#define UDMA_HYPERBUS_OFFSET ( ARCHI_UDMA_ADDR + 128*9 )
#define HYPERBUS_DEVICE_NUM 8
#define CONFIG_REG_OFFSET 0x80

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

static inline void udma_hyper_setup(){
  pulp_write32(ARCHI_UDMA_ADDR, 1 << HYPERBUS_DEVICE_NUM); // clock for the hyper bus module is activated
  //pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x24, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x01 ); // REG_T_EN_LATENCY_ADD
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x0C, 0xffffffff ); // REG_T_CS_MAX

  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x20, 0x00); // DRAM memory is selected
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x04, 0x06); // T latench access is set to 6 cycles

}

static inline void udma_8spi_setup(){
  pulp_write32(ARCHI_UDMA_ADDR, 1 << HYPERBUS_DEVICE_NUM); // clock for the hyper bus module is activated
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x0C, 0xffffffff ); // REG_T_CS_MAX
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x20, 0x02); // PSRAM is selected
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x04, 0x06); // T latench access is set to 6 cycles

/* Setup for PSRAM side (MR0) */
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x28, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x2C, 0x00 ); // 2D COUNT for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x30, 0x00 ); // 2D STRIDE for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x34, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x38, 0x00 ); // 2D COUNT for l2
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x3C, 0x00 ); // 2D STRIDE for l2
  pulp_write32(UDMA_HYPERBUS_OFFSET + 8*CONFIG_REG_OFFSET + 0x00, 0x04 ); // page boundary is not considered
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x1C, 0x00 );  // Address (MR0)
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x20, 0x2900); // Data to be written (Fixed latency setup)
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x18, 0x02); // Write is declared for the external mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x14, 0x14); // Write transaction is kicked
  pulp_write32(UDMA_HYPERBUS_OFFSET + 0*CONFIG_REG_OFFSET + 0x14, 0x00); // Write transaction information is reset
}

static inline void udma_hyper_flash_setup(){
  int i=0;
  pulp_write32(ARCHI_UDMA_ADDR, 1 << HYPERBUS_DEVICE_NUM); // clock for the hyper bus module is activated
  for(i=0; i< 8; i++){
      pulp_write32(UDMA_HYPERBUS_OFFSET + i*CONFIG_REG_OFFSET + 0x28, 0x00 ); // 2D TRAN is deactivated
      pulp_write32(UDMA_HYPERBUS_OFFSET + i*CONFIG_REG_OFFSET + 0x2C, 0x00 ); // 2D COUNT for ext mem
      pulp_write32(UDMA_HYPERBUS_OFFSET + i*CONFIG_REG_OFFSET + 0x30, 0x00 ); // 2D STRIDE for ext mem
      pulp_write32(UDMA_HYPERBUS_OFFSET + i*CONFIG_REG_OFFSET + 0x34, 0x00 ); // 2D TRAN is deactivated
      pulp_write32(UDMA_HYPERBUS_OFFSET + i*CONFIG_REG_OFFSET + 0x38, 0x00 ); // 2D COUNT for l2
      pulp_write32(UDMA_HYPERBUS_OFFSET + i*CONFIG_REG_OFFSET + 0x3C, 0x00 ); // 2D STRIDE for l2
  }
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x24, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x00 ); // REG_T_EN_LATENCY_ADD
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x0C, 0xffffffff ); // REG_T_CS_MAX
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x20, 0x01); // Flash memory is selected
  pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x04, 0x0f); // T latench access is set to 16 cycles
}

static inline void udma_hyper_sleep(){
  int a;
  a = pulp_read32(ARCHI_UDMA_ADDR);
  pulp_write32(ARCHI_UDMA_ADDR, (1 << HYPERBUS_DEVICE_NUM)^a ); // Clock gating is activated
}

// Burst write is conducted for the hyper flash. len <- burst length in bytes, ext_addr <- start address of the external memory, l2_addr <- start_address of the L2 memory, page_bound <- page boundary in the external memory
static inline void udma_hyper_dwrite(unsigned int len, unsigned int ext_addr, unsigned int l2_addr, unsigned int page_bound, unsigned int tran_id){

  int memsel;
  memsel = pulp_read32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x20);
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x28, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x2C, 0x00 ); // 2D COUNT for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x30, 0x00 ); // 2D STRIDE for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x34, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x38, 0x00 ); // 2D COUNT for l2
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x3C, 0x00 ); // 2D STRIDE for l2

  switch(page_bound){
     case 128:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x00 ); // page boundary is set to every 128 bytes
        break;
     case 256:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x01 ); // page boundary is set to every 256 bytes
        break;
     case 512:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x02 ); // page boundary is set to every 128 bytes
        break;
     case 1024:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x03 ); // page boundary is set to every 256 bytes
        break;
     default:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x04 ); // page boundary is not considered
  }


  if(memsel==2) pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x00 ); // REG_T_EN_LATENCY_ADD
  else pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x01 );
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x0C, l2_addr ); // Data address 
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x10, len );     // Data size to be sent
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x1C, ext_addr );     // Data size to be sent
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x18, 0x01);     // Write is declared for the external mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x14, 0x14);     // Write transaction is kicked
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x14, 0x00);     // Write transaction information is reset
}


static inline void udma_hyper_twd_dwrite(unsigned int len, unsigned int ext_addr, unsigned int l2_addr, unsigned int page_bound, unsigned int twd_act_ext, unsigned int twd_count_ext,unsigned int twd_stride_ext, unsigned int twd_act_l2, unsigned int twd_count_l2, unsigned int twd_stride_l2, unsigned int tran_id){

  int memsel;
  memsel = pulp_read32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x20);

  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x28, twd_act_ext    ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x2C, twd_count_ext  ); // 2D COUNT for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x30, twd_stride_ext ); // 2D STRIDE for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x34, twd_act_l2     ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x38, twd_count_ext  ); // 2D COUNT for l2
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x3C, twd_stride_ext ); // 2D STRIDE for l2

  switch(page_bound){
     case 128:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x00 ); // page boundary is set to every 128 bytes
        break;
     case 256:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x01 ); // page boundary is set to every 256 bytes
        break;
     case 512:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x02 ); // page boundary is set to every 128 bytes
        break;
     case 1024:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x03 ); // page boundary is set to every 256 bytes
        break;
     default:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x04 ); // page boundary is not considered
  }

  if(memsel==2) pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x00 ); // REG_T_EN_LATENCY_ADD
  else pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x01 );

  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x0C, l2_addr ); // Data address 
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x10, len );     // Data size to be sent
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x1C, ext_addr );     // Data size to be sent
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x18, 0x01);     // Write is declared for the external mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x14, 0x14);     // Write transaction is kicked
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x14, 0x00);     // Write transaction information is reset
}


// Word write for Hyper flash
static inline void udma_hyperflash_wwrite(unsigned int ext_addr, short int data, unsigned int tran_id){
  pulp_write32(UDMA_HYPERBUS_OFFSET + 8*CONFIG_REG_OFFSET + 0x00, 0x04 ); // page boundary is not considered
  //pulp_write32(UDMA_HYPERBUS_OFFSET + 8*CONFIG_REG_OFFSET + 0x24, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + 8*CONFIG_REG_OFFSET + 0x08, 0x00 ); // REG_T_EN_LATENCY_ADD
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x1C, ext_addr<<1); // Address for the external memory
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x20, data); // Data to be written
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x18, 0x00); // Write is declared for the external mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x14, 0x14); // Write transaction is kicked
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x14, 0x00); // Write transaction information is reset
  
}
static inline int udma_hyper_nb_tran(unsigned int tran_id){
  return pulp_read32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x24) >> 1;
}


// Burst write for Hyper flash. Page boundary consideration and byte addressing mode are NOT supported. nb_word <- burst length in words, hyper_waddr <- start address of the hyperflash (word addressing), l2_addr <- start_address for L2
static inline void udma_hyperflash_bwrite(unsigned int nb_word, unsigned int hyper_waddr, unsigned int l2_addr, unsigned int tran_id){

    udma_hyperflash_wwrite(0x555, 0x00aa, tran_id);
    udma_hyperflash_wwrite(0x2aa, 0x0055, tran_id);
    udma_hyperflash_wwrite(hyper_waddr, 0x0025, tran_id);
    udma_hyperflash_wwrite(hyper_waddr, nb_word-1, tran_id);
    for(int i=0; i< nb_word; i++ ){
       while(udma_hyper_nb_tran(tran_id)>7){}
       udma_hyperflash_wwrite(hyper_waddr+i, *((short int *) l2_addr+i), tran_id);
       //printf("%d th data= %x \n", hyper_waddr+i,  *((short int *) l2_addr+i));
    }
    udma_hyperflash_wwrite(hyper_waddr, 0x0029, tran_id);
    wait_cycles(125000);
}

static inline void udma_hyperflash_erase(unsigned int sector_addr, unsigned int tran_id){
    udma_hyperflash_wwrite(0x555, 0x00aa, tran_id);
    udma_hyperflash_wwrite(0x2aa, 0x0055, tran_id);
    udma_hyperflash_wwrite(0x555, 0x0080, tran_id);
    udma_hyperflash_wwrite(0x555, 0x00aa, tran_id);
    udma_hyperflash_wwrite(0x2aa, 0x0055, tran_id);
    udma_hyperflash_wwrite(sector_addr, 0x0030, tran_id);
    wait_cycles(125000);
}

// Linear read is conducted. len <- burst length in bytes, ext_addr <- start address of the external memory, l2_addr <- start_address of the L2 memory, page_bound <- page boundary in the external memory
//

static inline void udma_hyper_dread(unsigned int len, unsigned int ext_addr, unsigned int l2_addr, unsigned int page_bound, unsigned int tran_id){

  int memsel;
  memsel = pulp_read32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x20);
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x28, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x2C, 0x00 ); // 2D COUNT for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x30, 0x00 ); // 2D STRIDE for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x34, 0x00 ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x38, 0x00 ); // 2D COUNT for l2
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x3C, 0x00 ); // 2D STRIDE for l2

  switch(page_bound){
     case 128:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x00 ); // page boundary is set to every 128 bytes
        break;
     case 256:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x01 ); // page boundary is set to every 256 bytes
        break;
     case 512:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x02 ); // page boundary is set to every 128 bytes
        break;
     case 1024:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x03 ); // page boundary is set to every 256 bytes
        break;
     default:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x04 ); // page boundary is not considered
  }

  if(memsel!=1) pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x01 ); // REG_T_EN_LATENCY_ADD
  else pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x00 ); 
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x00, l2_addr ); // Data address 
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x04, len );     // Data size to be sent
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x1C, ext_addr );     // Data size to be sent
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x18, 0x05);     // Read is declared for the external mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x08, 0x14);     // Read transaction is kicked
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x08, 0x00);     // Write transaction information is reset
}

static inline void udma_hyper_twd_dread(unsigned int len, unsigned int ext_addr, unsigned int l2_addr, unsigned int page_bound, unsigned int twd_act_ext, unsigned int twd_count_ext,unsigned int twd_stride_ext, unsigned int twd_act_l2, unsigned int twd_count_l2, unsigned int twd_stride_l2, unsigned int tran_id){

  int memsel;
  memsel = pulp_read32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x20);
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x28, twd_act_ext    ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x2C, twd_count_ext  ); // 2D COUNT for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x30, twd_stride_ext ); // 2D STRIDE for ext mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x34, twd_act_l2     ); // 2D TRAN is deactivated
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x38, twd_count_ext  ); // 2D COUNT for l2
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x3C, twd_stride_ext ); // 2D STRIDE for l2


  switch(page_bound){
     case 128:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x00 ); // page boundary is set to every 128 bytes
        break;
     case 256:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x01 ); // page boundary is set to every 256 bytes
        break;
     case 512:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x02 ); // page boundary is set to every 128 bytes
        break;
     case 1024:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x03 ); // page boundary is set to every 256 bytes
        break;
     default:
        pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x00, 0x04 ); // page boundary is not considered
  }

  if(memsel!=1) pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x01 ); // REG_T_EN_LATENCY_ADD
  else pulp_write32(UDMA_HYPERBUS_OFFSET + CONFIG_REG_OFFSET*8 + 0x08, 0x00 );
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x00, l2_addr ); // Data address 
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x04, len );     // Data size to be sent
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x1C, ext_addr );     // Data size to be sent
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x18, 0x05);     // Read is declared for the external mem
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x08, 0x14);     // Read transaction is kicked
  pulp_write32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x08, 0x00);     // Write transaction information is reset
}

// If the hyperbus module is doing something.
static inline int udma_hyper_busy(unsigned int tran_id){
  return pulp_read32(UDMA_HYPERBUS_OFFSET + tran_id*CONFIG_REG_OFFSET + 0x24) & 0x00000001;
}

static inline void udma_hyper_wait(unsigned int tran_id){
   while(udma_hyper_busy(tran_id)){
   }
}

static inline int udma_hyper_id_alloc(){
  return pulp_read32(UDMA_HYPERBUS_OFFSET + 8*CONFIG_REG_OFFSET + 0x24);
}

