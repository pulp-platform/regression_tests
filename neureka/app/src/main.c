/*
 * Copyright (C) 2020-2024 ETH Zurich and University of Bologna
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
 * Authors:  Francesco Conti <fconti@iis.ee.ethz.ch>
 *           Gianna Paulin <pauling@iis.ee.ethz.ch>
 *           Renzo Andri <andrire@iis.ee.ethz.ch>
 *           Arpan Suravi Prasad <prasadar@iis.ee.ethz.ch>
 *           Luka Macan <luka.macan@unibo.it>
 * Main Test Program for N-EUREKA
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pulp.h>

#include "layer_util.h"
#include "nnx_layer.h"
#include "output.h"
#include "input.h"
#include "weight.h"

int main() {
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  int err = 0;
  if(rt_core_id()==0)
  {
    // execute NNX layer
    execute_nnx_layer(NULL);

    printf("Checking outputs");

    // output checking
    err = check_output();
    
  }
  synch_barrier();
  return err;

}
