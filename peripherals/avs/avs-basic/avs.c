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
 * Mantainer: Corrado Bonfanti (corrado.bonfanti@unibo.it)
 *            Alessandro Ottaviano (aottaviano@iis.ee.ethz.ch)
 */

/* The test checks AVS Master W/R data transactions.
 * All Write transactions are Write and Commit type
 * The test interacts with a simulated AVS slave in the RTL testbench (tb_avs.sv or tb_avs_fpga.sv).
 *
 * WRITE AND COMMIT:
 * AVS Master writes and commit the data
 * AVS master and slave generate and check CRC for signal integrity.
 *
 * READ:
 * Idle state. AVS Slave asynchronously requests a read from Master.
 * Master is wfi and performs the read once notified.
 * AVS master and slave generate and check CRC for signal integrity.
 */

#include "pulp.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "csr.h"
#include "io.h"
#include "bits.h"
#include "clic.h"

#define FRAME_SIZE 32
#define GENERATOR  0x0b
#define LENGTH_MES 29
#define LENGTH_DIV 4

void clic_setup_mtvec(void);
void clic_setup_mtvt(void);

void dec_to_bin(int n, int *arr, int length)
{
	int k = 0;

	for (int i = length - 1; i >= 0; i--) {
		k = n >> i;

		if (k & 1)
			arr[i] = 1;
		else
			arr[i] = 0;
	}
}

void avs_div_mod2(int message, int generator, int *remainder, int *quotient)
{

	int dividend[LENGTH_MES + LENGTH_DIV - 1];
	int divisor[LENGTH_DIV];
	int temp;

	dec_to_bin(message, dividend, LENGTH_MES + LENGTH_DIV - 1);
	dec_to_bin(generator, divisor, LENGTH_DIV);

	for (int i = LENGTH_MES + LENGTH_DIV - 2; i >= LENGTH_DIV - 1; i--) {
		temp = i;
		if (dividend[i] == 1) {
			temp = i;
			for (int j = LENGTH_DIV - 1; j >= 0; j--) {
				if (dividend[temp] == divisor[j]) {
					dividend[temp] = 0;
				} else {
					dividend[temp] = 1;
				}
				temp = temp - 1;
			}
			quotient[i - (LENGTH_DIV - 1)] = 1;
		} else {
			quotient[i - (LENGTH_DIV - 1)] = 0;
		}
		temp = i - 1;
		for (int j = LENGTH_DIV - 2; j >= 0; j--) {
			remainder[j] = dividend[temp];
			temp = temp - 1;
		}
	}
}

int var_glb = 0;

__attribute__((interrupt("machine"))) void __irq_avs_slv_read_req()
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

	int error = 0;

	//--- refer to this manual for the commands
	//--- https://www.cypress.com/file/216421/download

	//--- command sequence
	int tx_avs_cmd[FRAME_SIZE] = {SPI_CMD_CFG(1, 0, 1),
				      SPI_CMD_TX_DATA(1, 0, 32, 0, 0),
				      SPI_CMD_RX_DATA(1, 0, 32, 0, 0)};

	int tx_frame, rx_frame;
	int u = 0;
	int crc[LENGTH_DIV];
	int div[LENGTH_DIV];
	int temp;
	int quotient[LENGTH_MES];
	int remainder;

	// Set SPI event
	soc_eu_fcEventMask_setEvent(ARCHI_SOC_EVENT_SPIM_REQ(u));

	// Enable global core level CLINT interrupts (MSTATUS CSR)
	hal_irq_enable();

	// Enable CLINT interrupt line 26
	//irq_clint_enable(ARCHI_FC_EVT_SOC_EVT);

	// Enable CLIC interrupt line 26
	irq_clic_enable(ARCHI_FC_EVT_SOC_EVT);

	// Example of write frame command (data to write: 0000001111101000)
	const int write_data = 0x03e8;
	int message_wr = 0x080003e8;
	// Example of read frame command (01110000000001111111111111111)
	int message_rd = 0x0e00ffff;

	// Write frame
	tx_frame = message_wr << LENGTH_DIV - 1;
	avs_div_mod2(tx_frame, GENERATOR, crc, quotient);

	// Setting the last 3 bits equal to the CRC
	for (int i = 0; i < (LENGTH_DIV - 1); i++) {
		tx_frame |= crc[i] << i;
	}

	printf("\n[%d, %d] Start AVS write test over qspi %d, tx_frame = 0x%08x\n",
	       get_cluster_id(), get_core_id(), u, tx_frame);

	//--- enable all the udma channels
	plp_udma_cg_set(plp_udma_cg_get() | (0xffffffff));

	// Set AVS mode for SPI 0
	pulp_write32(UDMA_SPIM_AVS(u), 0x01);

	//--- get the base address of the SPIMx udma channels
	unsigned int udma_spim_channel_base =
		hal_udma_channel_base(UDMA_CHANNEL_ID(ARCHI_UDMA_SPIM_ID(u)));
	printf("uDMA spim%d base channel address %8x\n", u,
	       udma_spim_channel_base);

	plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u), (int)&tx_frame, 1 * 4,
			 UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
	plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u), (int)&rx_frame, 1 * 4,
			 UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
	plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (int)tx_avs_cmd, 3 * 4,
			 UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

	while (plp_udma_busy(UDMA_SPIM_RX_ADDR(u)))
		;

	printf("Checking the integrity of the write subframe from the slave device..\nrx_frame = 0x%08x\n",
	       rx_frame);
	avs_div_mod2(rx_frame, GENERATOR, crc, quotient);
	for (int i = 0; i < (LENGTH_DIV - 1); i++) {
		remainder |= crc[i] >> i;
	}

	if (remainder != 0) {
		error++;
		printf("The remainder of the write subframe is different from zero, data received is not correct\n");
	}

	// Read request from AVS slave device
	printf("Wait for interrupt request from AVS slave\n");
	while (var_glb == 0) {
		hal_itc_wait_for_interrupt();
	};

	// Clear event mask
	soc_eu_fcEventMask_clearEvent(ARCHI_SOC_EVENT_SPIM_REQ(u));

	// Read frame
	tx_frame = message_rd << (LENGTH_DIV - 1);
	avs_div_mod2(tx_frame, GENERATOR, crc, quotient);

	// Setting the last 3 bits equal to the CRC
	for (int i = 0; i < (LENGTH_DIV - 1); i++) {
		tx_frame |= crc[i] << i;
	}
	avs_div_mod2(tx_frame, GENERATOR, crc, quotient);

	printf("\n[%d, %d] Start AVS read test over qspi %d, tx_frame = 0x%08x\n",
	       get_cluster_id(), get_core_id(), u, tx_frame);

	//--- get the base address of the SPIMx udma channels
	udma_spim_channel_base =
		hal_udma_channel_base(UDMA_CHANNEL_ID(ARCHI_UDMA_SPIM_ID(u)));
	printf("uDMA spim%d base channel address %8x\n", u,
	       udma_spim_channel_base);

	plp_udma_enqueue(UDMA_SPIM_TX_ADDR(u), (int)&tx_frame, 1 * 4,
			 UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
	plp_udma_enqueue(UDMA_SPIM_RX_ADDR(u), (int)&rx_frame, 1 * 4,
			 UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);
	plp_udma_enqueue(UDMA_SPIM_CMD_ADDR(u), (int)tx_avs_cmd, 3 * 4,
			 UDMA_CHANNEL_CFG_EN | UDMA_CHANNEL_CFG_SIZE_32);

	while (plp_udma_busy(UDMA_SPIM_RX_ADDR(u)))
		;

	printf("Checking the integrity of the read subframe from the slave device..\nrx_frame = 0x%08x\n",
	       rx_frame);
	avs_div_mod2(rx_frame, GENERATOR, crc, quotient);
	for (int i = 0; i < (LENGTH_DIV - 1); i++) {
		remainder |= crc[i] >> i;
	}

	if (remainder != 0) {
		error++;
		printf("The remainder of the read subframe is different from zero, the frame received is not correct\n");
	}

	printf("\nChecking read back data from the slave subframe..\n");
	// Select returned data bits
	rx_frame = (rx_frame >> 8);
	rx_frame = rx_frame & ~(1 << 16);

	if (rx_frame != write_data) {
		error++;
		printf("Error, value received %08x, expected %08x\n", rx_frame,
		       write_data);
	}

	if (error == 0) {
		printf("TEST SUCCEDED\n");
	} else {
		printf("TEST FAILED with %d errors\n", error);
	}

	return error;
}
