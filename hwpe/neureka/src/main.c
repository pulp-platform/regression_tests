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

#include <pulp.h>
#include <stdint.h>
#include <stdio.h>

#include "layer_util.h"
#include "nnx_layer.h"
#include "ecc_check.h"

#define OUTPUT_SIZE 512

extern int8_t output[];

uint32_t ecc_errs[ECC_REGS];

static int check_output() {
    int checksum = 0;
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        checksum += output[i];
    }
    return (checksum == 0x00007330);
}

int errors = 0;
unsigned int intc_data_correctable_cnt = 0;
unsigned int intc_meta_correctable_cnt = 0;
unsigned int intc_data_uncorrectable_cnt = 0;
unsigned int intc_meta_uncorrectable_cnt = 0;

int main() {

  unsigned int core_id = get_core_id();
  unsigned int cluster_id = rt_cluster_id();

  if (core_id == 0) {

    // execute NNX layer
    execute_nnx_layer(NULL);
  
    errors = check_output();
  
    *(int *) 0x1A1040A0 = errors;
    if(errors)
      printf ("[KO] Terminated test with errors!!!\n");
    else
      printf ("[OK] Terminated test with no errors!!!\n");

    // Check number of detected errors by ECC modules inside interconnect
    intc_data_correctable_cnt = hwpe_hci_ecc_get_data_correctable_count(cluster_id);
    intc_meta_correctable_cnt = hwpe_hci_ecc_get_meta_correctable_count(cluster_id);
    intc_data_uncorrectable_cnt = hwpe_hci_ecc_get_data_uncorrectable_count(cluster_id);
    intc_meta_uncorrectable_cnt = hwpe_hci_ecc_get_meta_uncorrectable_count(cluster_id);
    for (int i = 0; i < 16; i++) {
      intc_meta_correctable_cnt += tcdm_scrubber_get_mismatch_count(cluster_id, i);
    }

    printf("Data errors corrected inside Neureka: %d. Data errors uncorrectable inside Neureka: %d\n",
      ecc_errs[0], ecc_errs[1]);
    printf("Meta errors corrected inside Neureka: %d. Meta errors uncorrectable inside Neureka: %d\n",
      ecc_errs[2], ecc_errs[3]);

    printf("Data errors corrected inside intc: %d. Data errors uncorrectable inside intc: %d\n",
      intc_data_correctable_cnt, intc_data_uncorrectable_cnt);
    printf("Meta errors corrected inside intc: %d. Meta errors uncorrectable inside intc: %d\n",
      intc_meta_correctable_cnt, intc_meta_uncorrectable_cnt);
  }
  synch_barrier();
  return (errors != 0) && (intc_data_uncorrectable_cnt == 0 && intc_meta_uncorrectable_cnt == 0 && (ecc_errs[1]==0 && ecc_errs[3]==0));
}
