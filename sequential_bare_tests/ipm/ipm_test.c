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
#include "ipm.h"

static int x[N + 1][N + 1] __sram;
static int y[N + 1][N + 1] __sram;
static int z[N + 1][N + 1] __sram;
static int w[N + 1][N + 1] __sram;

int Ne_l2[M][M] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
int Nq_l2[M][M] = {0, 1, 0, 1, 0, 1, 0, 1, 0};

int Ne[M][M] __sram;
int Nq[M][M] __sram;


int expected_x[] = {0 ,-1 ,-2 ,-3 ,-4 ,-5 ,1 ,0 ,-1 ,-2 ,-3 ,-4 ,2 ,1 ,0 ,-1 ,-2 ,-3 ,3 ,2 ,1 ,0 ,-1 ,-2 ,4 ,3 ,2 ,1 ,0 ,-1 ,5 ,4 ,3 ,2 ,1 ,0 ,};
int expected_y[] = {0 ,-1 ,-2 ,-3 ,-4 ,-5 ,1 ,0 ,0 ,1 ,-3 ,-4 ,2 ,0 ,0 ,0 ,-2 ,-3 ,3 ,-1 ,0 ,0 ,-1 ,-2 ,4 ,3 ,2 ,1 ,0 ,-1 ,5 ,4 ,3 ,2 ,1 ,0 ,};
int expected_z[] = {0 ,-1 ,-2 ,-3 ,-4 ,-5 ,1 ,1 ,0 ,0 ,-3 ,-4 ,2 ,2 ,1 ,0 ,-2 ,-3 ,3 ,3 ,2 ,1 ,-1 ,-2 ,4 ,3 ,2 ,1 ,0 ,-1 ,5 ,4 ,3 ,2 ,1 ,0 ,};
int expected_w[] = {0 ,-1 ,-2 ,-3 ,-4 ,-5 ,1 ,0 ,-2 ,-3 ,-3 ,-4 ,2 ,0 ,-1 ,-2 ,-2 ,-3 ,3 ,0 ,0 ,-1 ,-1 ,-2 ,4 ,3 ,2 ,1 ,0 ,-1 ,5 ,4 ,3 ,2 ,1 ,0 ,};

extern void dilation(int A[N + 1][N + 1], int D[N + 1][N + 1], int B[M][M]);
extern void erosion(int A[N + 1][N + 1], int E[N + 1][N + 1], int B[M][M]);
extern void laplacian_filter(int A[N + 1][N + 1], int R[N + 1][N + 1], int B[M][M]);

void test_setup() {
  for (int i=0;i<M;i++)
    for (int k=0;k<M;k++)
      {
	Ne[i][k] = Ne_l2[i][k];
	Nq[i][k] = Nq_l2[i][k];
      }
}

void test_clear() {
  for (int i = 0; i <= N; i++)
    for (int j = 0; j <= N; j++) {
      x[i][j] = i - j;
      y[i][j] = i - j;
      z[i][j] = i - j;
      w[i][j] = i - j;
    }
}


const char* __attribute__((weak)) get_testname()
{
  return "ipm";
}

void test_run() {
  laplacian_filter(x, y, Nq);
  dilation(x, z, Nq);
  erosion(z, w, Nq);
}

int test_check() {
  int index = 0;
  for (int i = 0; i <= M; i++)
    for (int j = 0; j <= N; j++) {
      if (x[i][j] != expected_x[index] ||
          y[i][j] != expected_y[index] ||
          z[i][j] != expected_z[index] ||
          w[i][j] != expected_w[index])
        return 0;

      index++;
    }

  return 1;
}
