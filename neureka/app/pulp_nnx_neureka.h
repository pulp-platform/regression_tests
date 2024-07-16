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

#include "neureka.h"
#include "neureka_bsp.h"
#include "neureka_task.h"
#include <stdint.h>

/* PULP-NNX interface */

void neureka_nnx_init(neureka_dev_t *dev, neureka_bsp_conf_t *conf);
void neureka_nnx_term(neureka_dev_t *dev);

/** neureka_nnx_dispatch_check
 *
 * Check whether you can dispatch to the accelerator.
 */
int neureka_nnx_dispatch_check(neureka_dev_t *dev);

/** neureka_nnx_dispatch_wait
 *
 * Block until you can dispatch to the accelerator.
 */
void neureka_nnx_dispatch_wait(neureka_dev_t *dev);

/** neureka_nnx_dispatch
 *
 * Dispatch a task to the accelerator.
 * Fails with return code 1 if the task cannot be dispatched. Otherwise returns
 * 0.
 */
int neureka_nnx_dispatch(neureka_dev_t *dev, neureka_task_t *task);

/** neureka_nnx_resolve_check
 *
 * Check whether the task has been resolved.
 */
int neureka_nnx_resolve_check(neureka_dev_t *dev, neureka_task_t *task);

/** neureka_nnx_resolve_wait
 *
 * Block until you can resolve the task.
 */
void neureka_nnx_resolve_wait(neureka_dev_t *dev, neureka_task_t *task);
