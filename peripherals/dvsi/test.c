#include <stdio.h>
#include "pulp.h"
#include "golden.h"

#define BUFFER_SIZE 16
#define UART_BAUDRATE 115200


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


#define UDMA_DVSI_OFFSET(id)            UDMA_PERIPH_OFFSET(ARCHI_UDMA_DVSI_ID(id))
#define REG_DVSI_CROP_TOP_BOTTOM(id)    (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x18) //BASEADDR+0x18
#define REG_DVSI_CROP_LEFT_RIGHT(id)    (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x1C) //BASEADDR+0x1C

#define REG_DVSI_CFG_GLOB(id)           (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x20) //BASEADDR+0x20
#define REG_DVSI_CFG_XYRES(id)          (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x24) //BASEADDR+0x24
#define REG_DVSI_CFG_TIMER(id)          (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x28) //BASEADDR+0x28
#define REG_DVSI_L2_START_ADDR(id)      (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x2C) //BASEADDR+0x2C
#define REG_DVSI_L2_ADDR_STEP(id)       (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x30) //BASEADDR+0x30

#define REG_DVSI_TRIGGER_THRESHOLD(id)  (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x34) //BASEADDR+0x34
#define REG_DVSI_TRIGGER_TDELTA(id)     (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x38) //BASEADDR+0x38
#define REG_DVSI_INT_MODE(id)           (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x3C) //BASEADDR+0x3C

#define REG_DVSI_BIAS0(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x40)
#define REG_DVSI_BIAS1(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x44)
#define REG_DVSI_BIAS2(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x48)
#define REG_DVSI_BIAS3(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x4C)
#define REG_DVSI_BIAS4(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x50)
#define REG_DVSI_BIAS5(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x54)
#define REG_DVSI_BIAS6(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x58)
#define REG_DVSI_BIAS7(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x5C)
#define REG_DVSI_BIAS8(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x60)
#define REG_DVSI_BIAS9(id)              (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x64)
#define REG_DVSI_BIAS10(id)             (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x68)
#define REG_DVSI_PARAMS(id)             (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x6C)

#define REG_DVSI_CONTROL(id)            (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x00)
#define REG_DVSI_STATUS(id)             (ARCHI_UDMA_ADDR + UDMA_DVSI_OFFSET(id) + 0x04)  //(read only)

//--- stream shortcut defines
#define EXT_DEST_OFFSET 0
#define EXT_STREAM_OFFSET   8
#define EXT_STREAM_ID_OFFSET 16
#define EXT_SOT_OFFSET   24
#define EXT_EOT_OFFSET   25

//--- this is supposed to go through the udma (not working for the moment)
//#define SNE_SHORTCUT (0x01 << EXT_STREAM_OFFSET) | (0x01 << EXT_STREAM_OFFSET) | (0x01 << EXT_STREAM_ID_OFFSET)

//---enable simple hardware shortcut to steer dvsi data to sne
#define SNE_SHORTCUT (0x01 << 26)

int main()
{

int error = 0;
//--- rx buffer
int rx_buffer[BUFFER_SIZE];


  for (int j = 0; j < BUFFER_SIZE; ++j)
  {
    rx_buffer[j] = 0;
  }


  //--- clear the rx buffer
  for (int j = 0; j < BUFFER_SIZE; ++j)
  {
    rx_buffer[j] = 0;
  }

  //--- set to alternate 3 (for the moment on all pads)
  printf("Set alternate 3\n");
  int val_wr = 0xffffffff;
  int address;
  int val_rd;

  int pad_fun_offset[4] = {REG_PADFUN0_OFFSET,REG_PADFUN1_OFFSET,REG_PADFUN2_OFFSET,REG_PADFUN3_OFFSET};

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

  printf("[%d, %d] Start test dvsi \n",  get_cluster_id(), get_core_id());

  //--- enable all the udma channels (see below for selective enable)
  plp_udma_cg_set(plp_udma_cg_get() | (0xffffffff));

  //--- get the base address of the SPIMx udma channels
  unsigned int udma_dvsi_channel_base = hal_udma_channel_base(UDMA_CHANNEL_ID(ARCHI_UDMA_DVSI_ID(0)));
  printf("uDMA dvs%d base channel address %8x\n", 0,udma_dvsi_channel_base);

  //--- dvs bias configuration interface
  pulp_write32(REG_DVSI_BIAS0(             0),100000     );
  pulp_write32(REG_DVSI_BIAS1(             0),0          );
  pulp_write32(REG_DVSI_BIAS2(             0),0          );
  pulp_write32(REG_DVSI_BIAS3(             0),10000      );
  pulp_write32(REG_DVSI_BIAS4(             0),400        );
  pulp_write32(REG_DVSI_BIAS5(             0),10000      );
  pulp_write32(REG_DVSI_BIAS6(             0),100000     );
  pulp_write32(REG_DVSI_BIAS7(             0),100000     );
  pulp_write32(REG_DVSI_BIAS8(             0),100000     );
  pulp_write32(REG_DVSI_BIAS9(             0),10000      );
  pulp_write32(REG_DVSI_BIAS10(            0),0          );
  pulp_write32(REG_DVSI_PARAMS(            0),2          );

  pulp_write32(REG_DVSI_CFG_GLOB(          0), 0x00010116);

  //--- dvs start acquisition
  pulp_write32(REG_DVSI_CFG_XYRES(         0), 0x00004d1d);
  pulp_write32(REG_DVSI_CFG_TIMER(         0), 0x08ff008f);
  pulp_write32(REG_DVSI_L2_START_ADDR(     0), 0x1c020000);
  pulp_write32(REG_DVSI_L2_ADDR_STEP(      0), 0x00000004);
  pulp_write32(REG_DVSI_TRIGGER_THRESHOLD( 0), 0x000000ff);
  pulp_write32(REG_DVSI_TRIGGER_TDELTA(    0), 0x0000ffff);
  pulp_write32(REG_DVSI_INT_MODE(          0), 0x00000002);

  //pulp_write32(REG_DVSI_CONTROL(          0), (1 << 17) | (1 << 18));

  uint32_t volatile * golden_frame_base  = (uint32_t volatile *) (0x1c060000);
  uint32_t volatile * dvsi_frame_base  = (uint32_t volatile *) (0x1c020000);
  //printf("golden image base: %8x\n",golden_frame_base);
  printf("input image base addr: %8x\n",dvsi_frame_base);
  uint8_t pixel_data;
  uint8_t xaddr;
  uint8_t yaddr;
  uint32_t volatile * pixel_addr;
  uint32_t volatile * pixel_addr_dvsi;
  uint8_t dvsi_pixel_data;

  printf("[PRE-TEST] errors = %0d\n",error);

  //--- uncomment to send data to sne
  //pulp_write32(REG_DVSI_CONTROL(0),SNE_SHORTCUT);

  //--- run dvs acquisition (1 frame)
  pulp_write32(REG_DVSI_CFG_GLOB(          0), 0x00000137 | (0 << 17) | (1 << 18));
  pulp_write32(REG_DVSI_CFG_GLOB(          0), 0x00000166 | (0 << 17) | (1 << 18));

  //--- wait until it's done (new fram is in memory @ 0x1c010000)
  while(0 == pulp_read8(REG_DVSI_STATUS(id)) & 0x00000001);

  //pulp_write32(REG_DVSI_CFG_GLOB(          0), 0x00000136);

  uint32_t check_golden_data;
  uint32_t check_dvsi_data;
  uint32_t evt_data;
  uint32_t evt_addr;

  for (uint32_t i = 0; i < 198; i++)
  {
    pixel_addr_dvsi = dvsi_frame_base + (i);
    check_dvsi_data = pulp_read32(pixel_addr_dvsi);
    evt_data = ((evt[i] & 0x00ff0000) >> 16);
    evt_addr = ((evt[i] & 0x000000ff) << 8) | ((evt[i] & 0x0000ff00) >> 8);
    check_golden_data = evt_data | (evt_addr << 8);
    if (check_golden_data != check_dvsi_data)
    {
      printf("ERROR @ %08x, g=%08x, r=%08x\n",pixel_addr_dvsi,check_golden_data,check_dvsi_data);
      error++;
    }else {
      //printf("---> CHECK OK @ %08x, g=%08x, r=%08x\n",pixel_addr_dvsi,check_golden_data,check_dvsi_data);

    }
  }

  printf("[POST-TEST] errors = %d\n",error);


  return error;
}
