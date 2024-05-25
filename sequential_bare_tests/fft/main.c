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

/* 
 * Mantainer: Luca Valente, luca.valente2@unibo.it
 */
#include <stdio.h>

#include "kiss_fft.h"
#include "kiss_fftr.h"
#include "_kiss_fft_guts.h"
#include <stdint.h>
#include "pulp.h"

#include "stimuli.h"
#include "expresp.h"

extern struct kiss_fftr_state g_fftr_state;
extern struct kiss_fftr_state g_ifftr_state;

RT_LOCAL_DATA kiss_fft_cpx freq[257];
RT_LOCAL_DATA int16_t buffer_out[516];

//--------------------------------------------------------------------------
// main function
//--------------------------------------------------------------------------
int main() {
  unsigned int i;
  kiss_fftr_cfg fftr_cfg = &g_fftr_state;
  kiss_fftr_cfg ifftr_cfg = &g_ifftr_state;

  int core_id = get_core_id();

  unsigned int errors = 0;

#if ARCHI_HAS_CLUSTER
  synch_barrier();
#endif

  // Work!
  if(core_id == 0) {
    reset_timer();
    start_timer();

    // perform FFT
    kiss_fftr(fftr_cfg, g_stimuli, freq);

    // perform IFFT
    kiss_fftri(ifftr_cfg, freq, buffer_out);
    stop_timer();
  }

#if ARCHI_HAS_CLUSTER
  synch_barrier();
#endif

  if(core_id == 0) {
    // now check the responses
    for(i = 0; i < 512; i++) {
      if((buffer_out[i] & 0xFFFF) != (g_expresp[i] & 0xFFFF)) {
        errors++;
        printf("Error: Is %X, expected %X, at %X\n", buffer_out[i], g_expresp[i], &g_expresp[i]);
      }
    }

    printf("#Cycles 0, %d\n", get_time());

    if(errors) {
      printf("Core %d, %d errors found\n", core_id, errors);
      printf("NOT OK!!!!!\n");
    } else {
      printf("Core %d, OK\n", core_id);
      printf("OOOOOOK!!!!!!\n");
    }

  }

  return errors;
}
