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

#ifndef __NEUREKA_TESTBENCH_BSP_H__
#define __NEUREKA_TESTBENCH_BSP_H__

#include "pulp.h"
#include "neureka.h"
#include <stdint.h>

typedef struct neureka_testbench_conf_t {
  int max_stall;
} neureka_testbench_conf_t;

void neureka_testbench_open(neureka_testbench_conf_t *conf);
void neureka_testbench_close();
void neureka_testbench_event_wait_and_clear();
const neureka_dev_t *neureka_testbench_get_dev();

#endif // !__NEUREKA_TESTBENCH_BSP_H__
