/*
 * Copyright (C) 2018-2019 ETH Zurich and University of Bologna
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
 * Authors:  Arpan Suravi Prasad <prasadar@iis.ee.ethz.ch>
 */

#ifndef __HAL_FIR_H__
#define __HAL_FIR_H__

/* REGISTER MAP */
#define ARCHI_CL_EVT_ACC0 0
#define ARCHI_CL_EVT_ACC1 1
#define __builtin_bitinsert(a,b,c,d) (a | (((b << (32-c)) >> (32-c)) << d))


#define FIR_TRIGGER          0x00
#define FIR_ACQUIRE          0x04
#define FIR_FINISHED         0x08
#define FIR_STATUS           0x0c
#define FIR_RUNNING_JOB      0x10
#define FIR_SOFT_CLEAR       0x14

#define FIR_REG_X_ADDR       0x20
#define FIR_REG_H_ADDR       0x24
#define FIR_REG_Y_ADDR       0x28
#define FIR_REG_SHIFT_LENGTH 0x2c

/* LOW-LEVEL HAL */
#define FIR_ADDR_BASE 0x1A10C000
#define FIR_ADDR_SPACE 0x00000100

#define HWPE_WRITE(value, offset) *(int *)(FIR_ADDR_BASE + offset) = value
#define HWPE_READ(offset)         *(int *)(FIR_ADDR_BASE + offset)

static inline void fir_x_addr_set(unsigned int value) {
  HWPE_WRITE(value, FIR_REG_X_ADDR);
}

static inline void fir_y_addr_set(unsigned int value) {
  HWPE_WRITE(value, FIR_REG_Y_ADDR);
}

static inline void fir_h_addr_set(unsigned int value) {
  HWPE_WRITE(value, FIR_REG_H_ADDR);
}

static inline void fir_shift_length_set(
  unsigned int shift,
  unsigned int length
) {
  unsigned int res = 0;
  res |= ((length & 0xffff) << 16) |
         ((shift  & 0x1f));
  HWPE_WRITE(res, FIR_REG_SHIFT_LENGTH);
}

static inline void fir_trigger_job() {
  HWPE_WRITE(0, FIR_TRIGGER);
}

static inline int fir_acquire_job() {
  return HWPE_READ(FIR_ACQUIRE);
}

static inline unsigned int fir_get_status() {
  return HWPE_READ(FIR_STATUS);
}

static inline void fir_soft_clear() {
  volatile int i;
  HWPE_WRITE(0, FIR_SOFT_CLEAR);
}
#define FIR_BUSYWAIT()              do {} while((*(int volatile *)(FIR_ADDR_BASE + FIR_STATUS)) != 0)

int fir_compare_int(uint32_t *actual_y, uint32_t *golden_y, int len) {
  uint32_t actual_word = 0;
  uint32_t golden_word = 0;
  uint32_t actual = 0;
  uint32_t golden = 0;

  int errors = 0;
  int non_zero_values = 0;

  int max_value_saturated = 0x80; // FIXME

  for (int i=0; i<len; i++) {
    actual_word = *(actual_y+i);
    golden_word = *(golden_y+i);

    int error = (int) (actual_word != golden_word);
    errors += (int) (actual_word != golden_word);

#ifndef NVERBOSE
    if(error) {
      if(errors==1) printf("  golden     <- actual     @ address    @ index\n");
      printf("  0x%08x <- 0x%08x @ 0x%08x @ 0x%08x\n", golden_word, actual_word, (actual_y+i), i*4);
    }
#endif /* NVERBOSE */
    non_zero_values += (int) (actual_word != 0 && actual_word != max_value_saturated);
  }
  return errors;
}

#endif /* __HAL_FIR_H__ */
