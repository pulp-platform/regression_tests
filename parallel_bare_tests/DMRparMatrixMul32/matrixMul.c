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

#include "pulp.h"

#include "parMatrixMul32_stimuli.h"

void check_matrix_mul(testresult_t *result, void (*start)(), void (*stop)());
void check_matrix_mul_transpose(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "matrixMul",          .test = check_matrix_mul           },
  // { .name = "matrixMulTranspose", .test = check_matrix_mul_transpose },
  {0, 0}
};

unsigned int num_cores;

int main()
{
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  num_cores = get_core_num();

  if(rt_core_id() < num_cores) {
    run_suite(testcases);
  }

  synch_barrier();

  return 0;
}

void matrix_init();
unsigned int matrix_check();

void check_matrix_mul(testresult_t *result, void (*start)(), void (*stop)()) {
  int core_id;
  unsigned int i, j, k;
  unsigned int chunk;
  unsigned int lb, ub;

  core_id = get_core_id();

  // number of rows each core has to multiply
  chunk = SIZE / (num_cores/2); // We want to use half the cores, so the chunk size must be twice.
  // lower bound
  lb = (core_id < num_cores/2) ? (core_id * chunk) : ((core_id - (num_cores/2)) * chunk); // We define the same lower bound for each couple of cores
  // upper bound
  ub = lb + chunk; // The upper bound remains the same

  if(core_id == 0) {
    matrix_init();

    for (int id = 0; id < num_cores; id++) {
      err[id] = 0;
    }

    for(int r = 0; r < num_cores; r++) {
      for(int m = 0; m < SIZE; m++) {
        for(int n = 0; n < SIZE; n++) {
          temp_res[r][m][n] = 0;
        }
      }
    }

  }

  synch_barrier();

  // start benchmark
  start();

  for(i = lb; i < ub; i++) { // Ext1 loop
    for(j = 0; j < SIZE; j++) { // Ext2 loop
      temp_res[core_id][i][j] = 0;
      for(k = 0; k < SIZE; k++) // Reduction loop
        temp_res[core_id][i][j] += g_mA[i][k] * g_mB[k][j];
    }
  }

  synch_barrier();

  for(i = lb; i < ub; i++) {
    for(j = 0; j < SIZE; j++) {
      if (core_id < num_cores/2) { // Group 1 checking on group 2
        err[core_id] += (temp_res[core_id][i][j] != temp_res[core_id+(num_cores/2)][i][j]);
      } else { // Group 2 checking on group 1
        err[core_id] += (temp_res[core_id][i][j] != temp_res[core_id-(num_cores/2)][i][j]);
      }
    }
  }

  synch_barrier();

  if (core_id < num_cores/2){
    for(i = lb; i < ub; i++) {
      for(j = 0; j < SIZE; j++) {
        g_mC[i][j] = ((err[core_id] == 0) && (err[core_id+(num_cores/2)] == 0)) ? temp_res[core_id][i][j] : -1;
      }
    }
  }

  synch_barrier();

  stop();

  if(core_id == 0) {
    result->errors = matrix_check();
  }
}

void check_matrix_mul_transpose(testresult_t *result, void (*start)(), void (*stop)()) {
  int core_id;
  unsigned int i, j, k;
  unsigned int chunk;
  unsigned int lb, ub;

  core_id = get_core_id();

  // number of rows each core has to multiply
  chunk = SIZE / num_cores;
  // lower bound
  lb = core_id * chunk;
  // upper bound
  ub = lb + chunk;

  if(core_id == 0) {
    matrix_init();
  }

  if(num_cores != 1) synch_barrier();

  // start benchmark
  start();

  // transpose array before using it
  for(i = lb; i < ub; i++) {
    for(j = 0; j < SIZE; j++) {
      g_mB_tmp[i][j] = g_mB[j][i];
    }
  }

  if(num_cores != 1) synch_barrier();

  for(i = lb; i < ub; i++) {
    for(j = 0; j < SIZE; j++) {
      g_mC[i][j] = 0;

      for(k = 0; k < SIZE; k++) {
        g_mC[i][j] += g_mA[i][k] * g_mB_tmp[j][k];
      }
    }
  }

  if(num_cores != 1) synch_barrier();

  stop();

  if(core_id == 0) {
    result->errors = matrix_check();
  }
}

void matrix_init() {
  unsigned int i, j;

  // init, copy to TCDM
  for(i = 0; i < SIZE; i++) {
    for(j = 0; j < SIZE; j++) {
      g_mA[i][j] = m_a[i * SIZE + j];
      g_mB[i][j] = m_b[i * SIZE + j];
      g_mC[i][j] = 0;
    }
  }
}

unsigned int matrix_check() {
  unsigned int errors = 0;
  unsigned int i, j;
  // check
  for(i = 0; i < SIZE; i++) {
    for(j = 0; j < SIZE; j++) {
      if(g_mC[i][j] != m_exp[i * SIZE + j]) {
        printf("At index %d, %d\n", i, j, 0, 0);
        errors++;
      }
    }
  }

  return errors;
}
