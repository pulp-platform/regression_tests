/*
 * Luka Macan <luka.macan@unibo.it>
 * Francesco Conti <f.conti@unibo.it>
 * Arpan Suravi Prasad <prasadar@iis.ee.ethz.ch>
 *
 * Copyright 2023 ETH Zurich and University of Bologna
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
 * SPDX-License-Identifier: Apache-2.0
 */

#include "neureka_testbench_bsp.h"
#include <pmsis.h>

#define NEUREKA_TESTBENCH_CLUSTER_CTRL_BASE_ADDR (0x00100000)
#define NEUREKA_TESTBENCH_BASE_ADDR (0x10201000)
#define NEUREKA_TESTBENCH_EVENT (1 << 12)

void neureka_testbench_open(neureka_testbench_conf_t *conf) {
  return;
}

void neureka_testbench_close() {
  return;
}

void neureka_testbench_event_wait_and_clear() {
  eu_evt_maskWaitAndClr(NEUREKA_TESTBENCH_EVENT);
}

static const neureka_dev_t neureka_testbench_dev = {
    .hwpe_dev = (struct hwpe_dev_t){
        .base_addr = (volatile uint32_t *)NEUREKA_TESTBENCH_BASE_ADDR}};

const neureka_dev_t *neureka_testbench_get_dev() {
  return &neureka_testbench_dev;
}
