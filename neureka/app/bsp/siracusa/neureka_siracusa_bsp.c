/*
 * Luka Macan <luka.macan@unibo.it>
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

#include "neureka_siracusa_bsp.h"
#include <pmsis.h>

#define NEUREKA_SIRACUSA_CLUSTER_CTRL_BASE_ADDR (0x00200000)
#define NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_OFFS 0x18
#define NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_ADDR                                \
  (NEUREKA_SIRACUSA_CLUSTER_CTRL_BASE_ADDR +                                   \
   NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_OFFS)
#define NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_MASK_HCI_PRIO 0x100
#define NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_MASK_HCI_MAXSTALL 0xff
#define NEUREKA_SIRACUSA_MAX_STALL (8)
#define NEUREKA_SIRACUSA_EVENT (1 << 12)
#define NEUREKA_SIRACUSA_BASE_ADDR (0x00201000)
#define NEUREKA_SIRACUSA_WEIGHT_MEM_BASE_ADDR (0x10400000)
#define NEUREKA_SIRACUSA_WEIGHT_MEM_MRAM_OFFSET (0x00000000)
#define NEUREKA_SIRACUSA_WEIGHT_MEM_SRAM_OFFSET (0x00400000)

void neureka_siracusa_hci_setpriority_neureka() {
  *(volatile uint32_t *)NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_ADDR |=
      NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_MASK_HCI_PRIO;
}

void neureka_siracusa_hci_setpriority_core() {
  *(volatile uint32_t *)NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_ADDR &=
      ~NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_MASK_HCI_PRIO;
}

void neureka_siracusa_hci_reset_max_stall() {
  *(volatile uint32_t *)NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_ADDR &=
      ~NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_MASK_HCI_MAXSTALL;
}

void neureka_siracusa_hci_set_max_stall(uint32_t max_stall) {
  *(volatile uint32_t *)NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_ADDR |=
      max_stall & NEUREKA_SIRACUSA_CLUSTER_CTRL_HWPE_MASK_HCI_MAXSTALL;
}

void neureka_siracusa_open(neureka_siracusa_conf_t *conf) {
  neureka_siracusa_hci_setpriority_neureka();
  neureka_siracusa_hci_set_max_stall(conf->max_stall);
}

void neureka_siracusa_close() {
  neureka_siracusa_hci_reset_max_stall();
  neureka_siracusa_hci_setpriority_core();
}

void neureka_siracusa_event_wait_and_clear() {
  eu_evt_maskWaitAndClr(NEUREKA_SIRACUSA_EVENT);
}

static const neureka_dev_t neureka_siracusa_dev = {
    .hwpe_dev = (struct hwpe_dev_t){
        .base_addr = (volatile uint32_t *)NEUREKA_SIRACUSA_BASE_ADDR}};

const neureka_dev_t *neureka_siracusa_get_dev() {
  return &neureka_siracusa_dev;
}
