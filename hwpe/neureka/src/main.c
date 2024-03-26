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

#include "layer_util.h"
#include "nnx_layer.h"

#define OUTPUT_SIZE 512

extern int8_t output[];

static int check_output() {
    int checksum = 0;
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        checksum += output[i];
    }
    return (checksum == 0x00007330);
}

int errors = 0;

int main() {

  if (get_core_id() == 0) {

    // execute NNX layer
    execute_nnx_layer(NULL);
  
    errors = check_output();
  
    *(int *) 0x1A1040A0 = errors;
    if(errors)
      printf ("[KO] Terminated test with errors!!!\n");
    else
      printf ("[OK] Terminated test with no errors!!!\n");

  }
  synch_barrier();
  return errors;

}
