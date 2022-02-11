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
 * Author: Corrado Bonfanti (corrado.bonfanti@unibo.it)
 * Author: Antonio Mastrandrea (a.mastrandrea@unibo.it)
 */

/* The test checks I2C slave W transactions
 * The test interacts with a simulated external I2C master in the RTL testbench (tb_i2c_slv_irq.sv or tb_i2c_slv_irq_fpga.sv).
 * Data are seamlessly written in L2 and the result is checked afterwards.
 * The test uses interrupts. The I2C slave module triggers an interrupt once the last data of the packet has been written, which
 * notifies the core.
 */

#include <stdio.h>
#include "pulp.h"

#include "csr.h"
#include "io.h"
#include "bits.h"
#include "clic.h"

#define I2CSLAVE_START_ADDR 0X1A140000
#define REG1		    0x00 //
#define REG2		    0x04 //
#define REG3		    0x08 //

#define assert(expression)                                                     \
	do {                                                                   \
		if (!(expression)) {                                           \
			printf("%s:%d: assert error\n", __FILE__, __LINE__);   \
			exit(1);                                               \
		}                                                              \
	} while (0)

void clic_setup_mtvec(void);
void clic_setup_mtvt(void);

int var_glb = 0;

__attribute__((interrupt("machine"))) void __irq_i2c_slv_handler()
{
	var_glb = 1;
}

int main()
{

	/* redirect vector table to our custom one */
	printf("set up vector table\n");
	clic_setup_mtvec();
	clic_setup_mtvt();

	/* make sure irq (itc) is a good state */
	pulp_irq_init();

	volatile unsigned int *r1, *r2, *r3;
	volatile char *rc;
	volatile int boot_addr;
	char check_var;
	int tmp;
	int error = 0;
	r1 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG1);
	r2 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG2);
	r3 = (volatile unsigned int *)(I2CSLAVE_START_ADDR + REG3);

	printf("\nREAD I2C registers (default values):\n");
	printf("\tr1       is 0x%x, r1 = %p\n", *(r1), r1);
	printf("\tr2       is 0x%x, r2 = %p\n", *(r2), r2);
	printf("\tr3       is 0x%x, r3 = %p\n", *(r3), r3);

	printf("READ buffer:\n");
	printf("Address &rc:   %p\n", &rc);
	printf("\t%d\t", 0);

	// Write address of rc[0] to REG2 (BASE ADDR of i2c slave):
	printf("write address of rc[0] to REG2:\n");
	rc = (char *)(*(r2));
	printf("\tNew BASE ADDRESS of i2c slave is 0x%x\n", rc);

	// Set to '0' all elements pointed by r2
	for (int i = 0; i < 256; i++) {
		rc[i] = 0;
	}

	// Enable global core level CLINT interrupts (MSTATUS CSR)
	hal_irq_enable();

	// Enable CLIC interrupt line 13
	irq_clic_enable(ARCHI_FC_EVT_I2C_SLV_BMC);

	// Enable interrupt (bit 0 of register 3)
	tmp = *r3;
	*r3 = tmp | 0x1;

	int j = 1;

	printf("Wait for I2C BMC master to transfer data through I2C BMC slave into L2\n");
	while (var_glb == 0) {
		hal_itc_wait_for_interrupt();
	};

	printf("READ buffer after i2c transaction:\n");

	for (int i = 0; i < 256; i++) {
		check_var = i;
		if (rc[i] != check_var) {
			printf("Error at L2 address %p, received value = 0x%02x, expected = 0x%02x\n",
			       &rc[i], rc[i], check_var);
			error++;
		}
	}

	if (error == 0) {
		printf("Test succeeded\n");
	} else {
		printf("Test failed\n");
	}

	return error;
}
