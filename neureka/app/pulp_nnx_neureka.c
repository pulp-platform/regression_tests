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

#include "pulp_nnx_neureka.h"
#include "hwpe.h"
#include "neureka.h"
#include "pulp_nnx_util.h"
#include <pmsis.h>
#include <stdint.h>
#include <sys/types.h>

void neureka_nnx_init(neureka_dev_t *dev, neureka_bsp_conf_t *conf) {
  neureka_bsp_open(conf);
  hwpe_soft_clear(&dev->hwpe_dev);
}

void neureka_nnx_term(neureka_dev_t *dev) {
  hwpe_soft_clear(&dev->hwpe_dev);
  neureka_bsp_close();
}

int neureka_nnx_dispatch_check(neureka_dev_t *dev) {
  return !neureka_task_queue_full(dev);
}

void neureka_nnx_dispatch_wait(neureka_dev_t *dev) {
  while (!neureka_nnx_dispatch_check(dev)) {
    neureka_bsp_event_wait_and_clear();
  }
}

int neureka_nnx_dispatch(neureka_dev_t *dev, neureka_task_t *task) {
  if (hwpe_task_queue_acquire_task(&dev->hwpe_dev, &task->id)) {
    return 1;
  }
  hwpe_task_queue_write_task(&dev->hwpe_dev, (uint32_t *)&task->data,
                             (int)(sizeof(neureka_task_data_t) / 4));
  hwpe_task_queue_release_and_run(&dev->hwpe_dev);
  return 0;
}

int neureka_nnx_resolve_check(neureka_dev_t *dev, neureka_task_t *task) {
#if __PLATFORM__ == ARCHI_PLATFORM_GVSOC
  // GVSOC model has a broken running_id so resolve_check
  // conservativly looks if the task queue is empty.
  return neureka_task_queue_empty(dev);
#else
  uint8_t prev_task_id = task->id - 1;
  return !(hwpe_last_task_id(&dev->hwpe_dev) == prev_task_id ||
           (hwpe_last_task_id(&dev->hwpe_dev) == task->id &&
            !neureka_task_queue_empty(dev)));
#endif
}

void neureka_nnx_resolve_wait(neureka_dev_t *dev, neureka_task_t *task) {
  while (!neureka_nnx_resolve_check(dev, task)) {
    neureka_bsp_event_wait_and_clear();
  }
}
