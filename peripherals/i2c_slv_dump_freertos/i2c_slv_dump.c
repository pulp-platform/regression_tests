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
 *
 * Author: Antonio Mastrandrea (a.mastrandrea@unibo.it)
 */

/* The test checks I2C slave W transactions
 * The test interacts with a simulated external I2C master in the RTL testbench (tb_i2c_slv_dump.sv or tb_i2c_slv_dump_fpga.sv).
 * Data are seamlessly written in L2 and the result is checked and dumped through stdout.
 * The test does not use interrupts. Synchronization happens at the testbench level.
 */

/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>

/* c stdlib */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

/* system includes */
#include "system.h"
#include "io.h"
#include "timer.h"
#include "timer_hal.h"
#include "timer_irq.h"
#include "fll.h"
#include "irq.h"
#include "gpio.h"

/* pmsis */
#include "target.h"
#include "os.h"

#include "memory_map.h"

void vApplicationMallocFailedHook(void);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
void vApplicationTickHook(void);

#define I2CSLAVE_START_ADDR         0X1A140000
#define REG1    0x00    //
#define REG2    0x04    //
#define REG3    0x08    //

int main()
{

  /* Init board hardware. */
  system_init();

  volatile unsigned int *r1, *r2,*r3;
  volatile char *rc;
  char check_var;
  int error = 0;
  r1 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG1);
  r2 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG2);
  r3 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG3);

  printf("[PMS] READ I2C SLV registers (default values):\n\r");
  printf("[PMS] \tr1       is 0x%x, &r1 = %p\n\r", *(r1), r1);
  printf("[PMS] \tr2       is 0x%x, &r2 = %p\n\r", *(r2), r2);
  printf("[PMS] \tr3       is 0x%x, &r3 = %p\n\r", *(r3), r3);

  //write address of rc[0] to REG2 (BASE ADDR of i2c slave):
  printf("write address of rc[0] to REG2:\n");
  rc = (char *)(*(r2));
  printf("\t[PMS] New BASE ADDRESS of i2c slave is 0x%x\n\r", rc);

  int j=1;

  printf("[PMS] READ buffer after i2c transaction:\n\r");

  for(int i=0;i<256;i++)
    {
#ifndef DUMP_ONLY
      check_var = i;
      if (rc[i] != check_var) {
        printf("[PMS] Error at L2 address %p, received value = 0x%2x, expected = 0x%02x\n\r", &rc[i], rc[i], check_var);
        error++;
      }
#else
      printf("[PMS] SRAM address %p, received value = 0x%2x\n\r", &rc[i], rc[i]);
#endif
    }

  return error;
}

void vApplicationMallocFailedHook(void)
{
  /* vApplicationMallocFailedHook() will only be called if
     configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
     function that will get called if a call to pvPortMalloc() fails.
     pvPortMalloc() is called internally by the kernel whenever a task, queue,
     timer or semaphore is created.  It is also called by various parts of the
     demo application.  If heap_1.c or heap_2.c are used, then the size of the
     heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
     FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
     to query the size of free heap space that remains (although it does not
     provide information on how the remaining heap might be fragmented). */
  taskDISABLE_INTERRUPTS();
  printf("error: application malloc failed\n");
  __asm volatile("ebreak");
  for (;;)
    ;
}

void vApplicationIdleHook(void)
{
  /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
     to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
     task.  It is essential that code added to this hook function never attempts
     to block in any way (for example, call xQueueReceive() with a block time
     specified, or call vTaskDelay()).  If the application makes use of the
     vTaskDelete() API function (as this demo application does) then it is also
     important that vApplicationIdleHook() is permitted to return to its calling
     function, because it is the responsibility of the idle task to clean up
     memory allocated by the kernel to any task that has since been deleted. */
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
  (void)pcTaskName;
  (void)pxTask;

  /* Run time stack overflow checking is performed if
     configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
     function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  printf("error: stack overflow\n");
  __asm volatile("ebreak");
  for (;;)
    ;
}

void vApplicationTickHook(void)
{
}
