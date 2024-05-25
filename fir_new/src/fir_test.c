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
#include "common.h"

#include "h_stim32.h"
#include "x_stim32.h"
#include "y_gold32.h"
#include "fir.h"

#define NB_TAPS     50
#define NB_SAMPLES  512
#define RIGHT_SHIFT 15
#define VERBOSE

int16_t pad_input[NB_TAPS+NB_SAMPLES] __sram;
int16_t output[NB_SAMPLES] __sram;

const char* get_testname() {
  return "fir16";
}

void test_setup() {
  for (int i=0; i<NB_TAPS-1; i++) {
    pad_input[i] = 0;
  }
  for (int i=NB_TAPS-1; i<NB_SAMPLES+NB_TAPS-1; i++) {
    pad_input[i] = ((int16_t *) x_stim)[i-NB_TAPS+1];
  }
}

void test_run() {
  fir16(pad_input, (int16_t *) h_stim, output, NB_SAMPLES, NB_TAPS, RIGHT_SHIFT);
}

int test_check() {
  int16_t *y_gold16 = (int16_t *) y_gold;
  int err = 0;
  for (int i=0; i<NB_SAMPLES; i++) {
    if(output[i] != y_gold16[i]) {
      err++;
#ifdef VERBOSE
      printf(" ERROR output vs gold: @%d: %04x vs %04x\n", i, output[i], y_gold16[i]);
#endif
    }
  }
  return err;
}

int main() {
  test_setup();
  reset_timer();
  start_timer();
  test_run();
  stop_timer();
  int t = get_time();
  printf("Test ended in %d cycles\n", t);
  return test_check();
}
