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

// Some CLIC irq low-level function definition with pulp-runtime
// Remove when updating the test with Freertos

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "clic.h"
#include "csr.h"
#include "io.h"
#include "bits.h"
#include "assert.h"

void irq_clic_enable(int id)
{
	assert(0 <= id && id < CLIC_PARAM_NUM_SRC);
	/* TODO: enable selective hardware vectoring for interrupt. We might
	 * later make this configurable */
	writew(1 << CLIC_CLICINTATTR_SHV_BIT,
	       (uintptr_t)(CLIC_BASE_ADDR + CLIC_CLICINTATTR_REG_OFFSET(id)));

	writew(1ul,
	       (uintptr_t)(CLIC_BASE_ADDR + CLIC_CLICINTIE_REG_OFFSET(id)));

	/* TODO: fix this quick hack which is there just to get going */
	irq_clic_set_lvl_and_prio(id, 1, 1);
	/* TODO: assume edge triggered interrupt by default */
	irq_clic_set_trigger_type(id, CLIC_TRIG_EDGE | CLIC_TRIG_POSITIVE);
}

void irq_clic_set_trigger_type(int id, int flags)
{
	uint32_t reg = readw(
		(uintptr_t)(CLIC_BASE_ADDR + CLIC_CLICINTATTR_REG_OFFSET(id)));
	reg &= ~(CLIC_CLICINTATTR_TRIG_MASK << CLIC_CLICINTATTR_TRIG_OFFSET);
	reg |= (flags & CLIC_CLICINTATTR_TRIG_MASK)
	       << CLIC_CLICINTATTR_TRIG_OFFSET;
	writew(reg,
	       (uintptr_t)(CLIC_BASE_ADDR + CLIC_CLICINTATTR_REG_OFFSET(id)));
}

void irq_clic_set_lvl_and_prio(int id, int lvl, int prio)
{
	/* TODO: probe CLICINTCTLBITS */
	uint32_t nlbits =
		readw((uintptr_t)(CLIC_BASE_ADDR + CLIC_CLICCFG_REG_OFFSET)) >>
			CLIC_CLICCFG_NLBITS_OFFSET &
		CLIC_CLICCFG_NLBITS_MASK;

	uint32_t shift = 8 - nlbits;
	uint32_t val = ((((uint32_t)lvl & BIT_MASK(nlbits)) << shift |
			 ((uint32_t)prio & BIT_MASK(shift))) &
			0xff);
	writew(val,
	       (uintptr_t)(CLIC_BASE_ADDR + CLIC_CLICINTCTL_REG_OFFSET(id)));
}

void pulp_irq_init()
{
	/* min threshold, thereby propagating all interrupts */
	csr_write(CSR_MINTTHRESH, 0x0);
	/* set nlbits to four which gives 4 bits for level and priority */
	/* TODO: implement freertos level interrupts */
	writeb((0x4 << CLIC_CLICCFG_NLBITS_OFFSET),
	       CLIC_BASE_ADDR + CLIC_CLICCFG_REG_OFFSET);
}
