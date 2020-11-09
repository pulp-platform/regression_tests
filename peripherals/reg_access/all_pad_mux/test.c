#include <stdio.h>
#include "pulp.h"

//ARCHI_APB_SOC_CTRL_ADDR (pad mux regs are in the soc control)
//ARCHI_GPIO_ADDR (base address of the GPIO IP)
//--- this application writes and read back all the pad mux regs

#define REG_PADFUN0_OFFSET 0x10
#define REG_PADFUN1_OFFSET 0x14
#define REG_PADFUN2_OFFSET 0x18
#define REG_PADFUN3_OFFSET 0x1C

#define REG_PADCFG0_OFFSET  0x24
#define REG_PADCFG1_OFFSET  0x28
#define REG_PADCFG2_OFFSET  0x2C
#define REG_PADCFG3_OFFSET  0x30
#define REG_PADCFG4_OFFSET  0x34
#define REG_PADCFG5_OFFSET  0x38
#define REG_PADCFG6_OFFSET  0x3C
#define REG_PADCFG7_OFFSET  0x40
#define REG_PADCFG8_OFFSET  0x44
#define REG_PADCFG9_OFFSET  0x48
#define REG_PADCFG10_OFFSET 0x4C
#define REG_PADCFG11_OFFSET 0x50
#define REG_PADCFG12_OFFSET 0x54
#define REG_PADCFG13_OFFSET 0x58
#define REG_PADCFG14_OFFSET 0x5C
#define REG_PADCFG15_OFFSET 0x60

int main()
{

  int pad_fun_offset[4] = {REG_PADFUN0_OFFSET,REG_PADFUN1_OFFSET,REG_PADFUN2_OFFSET,REG_PADFUN3_OFFSET};
  int pad_cfg_offset[16] = {REG_PADCFG0_OFFSET,REG_PADCFG1_OFFSET,REG_PADCFG2_OFFSET,REG_PADCFG3_OFFSET,REG_PADCFG4_OFFSET,REG_PADCFG5_OFFSET,REG_PADCFG6_OFFSET,REG_PADCFG7_OFFSET,REG_PADCFG8_OFFSET,REG_PADCFG9_OFFSET,REG_PADCFG10_OFFSET,REG_PADCFG11_OFFSET,REG_PADCFG12_OFFSET,REG_PADCFG13_OFFSET,REG_PADCFG14_OFFSET,REG_PADCFG15_OFFSET};


  int error = 0;
  int address;
  int val_wr = 0x00000000;
  int val_rd = 0;

  printf("[%d, %d] Start test\n",  get_cluster_id(), get_core_id());
  //--- set to alternate 1 (gpio)
  printf("Set alternate 1\n");
  val_wr = 0x55555555;
  for (int i = 0; i < 4; ++i)
  {
    address = ARCHI_APB_SOC_CTRL_ADDR + pad_fun_offset[i]; 
    pulp_write32(address, val_wr);
    val_rd = 0;
    val_rd = pulp_read32(address); 
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
    if (val_rd != val_wr)
    {
      error++;
    }
  }

  printf("writing all GPIO IP regs\n");
  //--- set GPIOs 0 to 31 direction
  address = ARCHI_GPIO_ADDR + GPIO_PADDIR_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
  printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }
  //--- set GPIOs 32 to 64 direction (only 58 are actually connected)
  address = ARCHI_GPIO_ADDR + GPIO_PADDIR_32_63_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }

  //--- set GPIOs 0 to 31 output enable
  address = ARCHI_GPIO_ADDR + GPIO_GPIOEN_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }
  //--- set GPIOs 32 to 64 output enable
  address = ARCHI_GPIO_ADDR + GPIO_GPIOEN_32_63_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }

  //--- set GPIOs 0 to 31 value
  address = ARCHI_GPIO_ADDR + GPIO_PADOUT_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }
  //--- set GPIOs 32 to 64 value
  address = ARCHI_GPIO_ADDR + GPIO_PADOUT_32_63_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }

  ////--- set GPIOs 0 to 31 set
  //address = ARCHI_GPIO_ADDR + GPIO_PADOUTSET_OFFSET;
  //val_wr = 0xffffffff;
  //pulp_write32(address, val_wr);
  //val_rd = 0;
  //val_rd = pulp_read32(address);
  //  printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  //if (val_wr != val_rd)
  //{
  //  error++;
  //}
  ////--- set GPIOs 32 to 64 set
  //address = ARCHI_GPIO_ADDR + GPIO_PADOUTSET_32_63_OFFSET;
  //val_wr = 0xffffffff;
  //pulp_write32(address, val_wr);
  //val_rd = 0;
  //val_rd = pulp_read32(address);
  //  printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  //if (val_wr != val_rd)
  //{
  //  error++;
  //}

  //--- pad configuration from gpio ip

  //--- set GPIOs 0 to 31 cfg
  address = ARCHI_GPIO_ADDR + GPIO_PADCFG0_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }
  //--- set GPIOs 0 to 8 cfg
  address = ARCHI_GPIO_ADDR + GPIO_PADCFG1_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }
    //--- set GPIOs 0 to 8 cfg
  address = ARCHI_GPIO_ADDR + GPIO_PADCFG2_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }
    //--- set GPIOs 0 to 8 cfg
  address = ARCHI_GPIO_ADDR + GPIO_PADCFG3_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }

  //--- set GPIOs 32 to 63 cfg
  address = ARCHI_GPIO_ADDR + GPIO_PADCFG_32_39_OFFSET;
  val_wr = 0xffffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }
  //--- set GPIOs 0 to 8 cfg
  address = ARCHI_GPIO_ADDR + GPIO_PADCFG_40_47_OFFSET;
  val_wr = 0x0fffffff;
  pulp_write32(address, val_wr);
  val_rd = 0;
  val_rd = pulp_read32(address);
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  if (val_wr != val_rd)
  {
    error++;
  }
    //--- set GPIOs 0 to 8 cfg
  //address = ARCHI_GPIO_ADDR + GPIO_PADCFG_48_55_OFFSET;
  //val_wr = 0xffffffff;
  //pulp_write32(address, val_wr);
  //val_rd = 0;
  //val_rd = pulp_read32(address);
  //  printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  //if (val_wr != val_rd)
  //{
  //  error++;
  //}
  //  //--- set GPIOs 0 to 8 cfg
  //address = ARCHI_GPIO_ADDR + GPIO_PADCFG_56_63_OFFSET;
  //val_wr = 0xffffffff;
  //pulp_write32(address, val_wr);
  //val_rd = 0;
  //val_rd = pulp_read32(address);
  //  printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
  //if (val_wr != val_rd)
  //{
  //  error++;
  //}
 
  //--- set to alternate 2
  printf("Set alternate 2\n");
  val_wr = 0xaaaaaaaa;
  for (int i = 0; i < 4; ++i)
  {
    address = ARCHI_APB_SOC_CTRL_ADDR + pad_fun_offset[i]; 
    pulp_write32(address, val_wr);
    val_rd = 0;
    val_rd = pulp_read32(address); 
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
    if (val_rd != val_wr)
    {
      error++;
    }
  }

  //--- set to alternate 3
  printf("Set alternate 3\n");
  val_wr = 0xffffffff;
  for (int i = 0; i < 4; ++i)
  {
    address = ARCHI_APB_SOC_CTRL_ADDR + pad_fun_offset[i]; 
    pulp_write32(address, val_wr);
    val_rd = 0;
    val_rd = pulp_read32(address); 
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
    if (val_rd != val_wr)
    {
      error++;
    }
  }

  uint8_t pad_cfg_val = 0;

  printf("Toggle all pad cfg\n");
  for (int i = 0; i < 16; ++i)
  {

    val_wr = 0;
    pad_cfg_val = 0x1f;
    val_wr = (pad_cfg_val << 24) | (pad_cfg_val << 16) | (pad_cfg_val << 8) | (pad_cfg_val);
    address = ARCHI_APB_SOC_CTRL_ADDR + pad_cfg_offset[i]; 
    pulp_write32(address, val_wr);
    val_rd = 0;
    val_rd = pulp_read32(address); 
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
    if (val_rd != val_wr)
    {
      error++;
    }
  }

  for (int i = 0; i < 16; ++i)
  {

    val_wr = 0;
    pad_cfg_val = 0x1a;
    val_wr = (pad_cfg_val << 24) | (pad_cfg_val << 16) | (pad_cfg_val << 8) | (pad_cfg_val);
    address = ARCHI_APB_SOC_CTRL_ADDR + pad_cfg_offset[i]; 
    pulp_write32(address, val_wr);
    val_rd = 0;
    val_rd = pulp_read32(address); 
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
    if (val_rd != val_wr)
    {
      error++;
    }
  }

  for (int i = 0; i < 16; ++i)
  {
    val_wr = 0;
    pad_cfg_val = 0x0c;
    val_wr = (pad_cfg_val << 24) | (pad_cfg_val << 16) | (pad_cfg_val << 8) | (pad_cfg_val);
    address = ARCHI_APB_SOC_CTRL_ADDR + pad_cfg_offset[i]; 
    pulp_write32(address, val_wr);
    val_rd = 0;
    val_rd = pulp_read32(address); 
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
    if (val_rd != val_wr)
    {
      error++;
    }
  }

  for (int i = 0; i < 16; ++i)
  {
    val_wr = 0x00000000;
    address = ARCHI_APB_SOC_CTRL_ADDR + pad_cfg_offset[i]; 
    pulp_write32(address, val_wr);
    val_rd = 0;
    val_rd = pulp_read32(address); 
    printf("%08x: wr = %08x, rd = %08x\n",address,val_wr,val_rd);
    if (val_rd != val_wr)
    {
      error++;
    }
  }


  return error;
}
