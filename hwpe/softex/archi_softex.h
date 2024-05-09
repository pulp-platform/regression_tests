/*
 * Andrea Belano <andrea.belano@studio.unibo.it>
 *
 * Copyright 2024 ETH Zurich and University of Bologna
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

#ifndef __ARCHI_SOFTEX__
#define __ARCHI_SOFTEX__

#define DATA_WIDTH      256

/* PULP Cluster Archi defines */
#define ARCHI_CLUST_CTRL_BASE 0x50200000
#define ARCHI_CLUST_HWPE_BASE 0x50201000
#define DMA_COMMAND_QUEUE     0x50204400
#define DMA_STATUS_REGISTER   0x50204404
#define ARCHI_CL_HWPE_EVT0 12
#define ARCHI_CL_HWPE_EVT1 13
#define FC_DMA_EVENT 8
#define CL_DMA_EVENT 22
#define CLUST_CTRL_HWPE_EN 0x18
#define CLUST_CTRL_HWPE_EN_MASK 0x800
#define __builtin_bitinsert(a,b,c,d) (a | (((b << (32-c)) >> (32-c)) << d))

#define SOFTEX_BASE_ADD    ARCHI_CLUST_HWPE_BASE
#define SOFTEX_CG_EN_MSK      0x4000
// Commands
#define SOFTEX_TRIGGER     0x00
#define SOFTEX_ACQUIRE     0x04
#define SOFTEX_FINISHED    0x08
#define SOFTEX_STATUS      0x0C
#define SOFTEX_RUNNING_JOB 0x10
#define SOFTEX_SOFT_CLEAR  0x14

#define SOFTEX_REG_OFFS    0x20

#define SOFTEX_IN_ADDR         SOFTEX_REG_OFFS + 0x00
#define SOFTEX_OUT_ADDR        SOFTEX_REG_OFFS + 0x04
#define SOFTEX_TOT_LEN         SOFTEX_REG_OFFS + 0x08
#define SOFTEX_COMMANDS        SOFTEX_REG_OFFS + 0x0C
#define SOFTEX_CACHE_BASE_ADDR SOFTEX_REG_OFFS + 0x10
#define SOFTEX_CAST_CTRL       SOFTEX_REG_OFFS + 0x14


#define SOFTEX_CMD_ACC_ONLY        0x00000001
#define SOFTEX_CMD_DIV_ONLY        0x00000002
#define SOFTEX_CMD_ACQUIRE_SLOT    0x00000004
#define SOFTEX_CMD_LAST            0x00000008
#define SOFTEX_CMD_SET_CACHE_ADDR  0x00000010
#define SOFTEX_CMD_NO_OP           0x00000020
#define SOFTEX_CMD_INT_INPUT       0x00000040
#define SOFTEX_CMD_INT_OUTPUT      0x00000080

/* DMA Archi */
#define DMA_TX  0
#define DMA_RX  1
#define DMA_INC 1

#define PLP_DMA_TYPE_BIT    0x00000011
#define PLP_DMA_INCR_BIT    0x00000012
#define PLP_DMA_2D_BIT      0x00000013
#define PLP_DMA_ELE_BIT     0x00000014
#define PLP_DMA_ILE_BIT     0x00000015
#define PLP_DMA_BLE_BIT     0x00000016
#define PLP_DMA_2D_TCDM_BIT 0x0000017

#endif