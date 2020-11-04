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
#include "pulp.h"

/* Stencil code */
#define N 32
#define M 32

void stencil_vect0();
void stencil_vect1();

RT_LOCAL_DATA char C[N+8][M+8];
RT_LOCAL_DATA char A[N+8][M+8];


#define CHKSUM 60480

void check_stencil_simple(testresult_t *result, void (*start)(), void (*stop)());
void check_stencil_split (testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "stencil_vect_simple",        .test = check_stencil_simple  },
  { .name = "stencil_vect_split",         .test = check_stencil_split   },
  {0, 0}
};

int main()
{
  if (get_core_id() == 0)
    return run_suite(testcases);
  else
    return 0;
}

void check_stencil_simple(testresult_t *result, void (*start)(), void (*stop)())
{
  int i,j,k;
  
  printf("Start stencil simple\n");

  for (i=0;i<N+8;i++) {
    for (k=0;k<M+8;k++)
      A[i][k] = 0;
  }

  for (i=4;i<N+4;i++) {
    for (k=4;k<M+4;k++)
      A[i][k] = (i+k+1)%16;
  }

    start();
    stencil_vect0();
    stop();

  // check results
  int check_sum = 0;

  for (i=4;i<N+4;i++)
    for (k=4;k<M+4;k++) {
      check_sum += (int) C[i][k];
    }

  // check test 0
#ifdef DEBUG_OUTPUT
  printf("\nchecksum = %d\n",check_sum);
#endif
  if (check_sum != CHKSUM) {
    result->errors++;
  }
}

void check_stencil_split(testresult_t *result, void (*start)(), void (*stop)())
{
  int i,j,k;
  
  printf("Start stencil\n");

  for (i=0;i<N+8;i++) {
    for (k=0;k<M+8;k++)
      A[i][k] = 0;
  }

  for (i=4;i<N+4;i++) {
    for (k=4;k<M+4;k++)
      A[i][k] = (i+k+1)%16;
  }

  start();
  stencil_vect1();
  stop();
  
  // check results
  int check_sum = 0;

  for (i=4;i<N+4;i++)
    for (k=4;k<M+4;k++) {
      check_sum += (int) C[i][k];
    }
  
  // check test 1
#ifdef DEBUG_OUTPUT
  printf("\nchecksum = %d\n",check_sum);
#endif
  if (check_sum != CHKSUM) {
    result->errors++;
  }
}


void stencil_vect1()
{

  unsigned int c,d;

  for (c = 4 ; c < N+4; c++)
  {
    // aligned data
    for (d = 4 ; d < M+4; d++){
      C[c][d] = 4*A[c][d] + A[c-1][d] + A[c+1][d];
    }
    // unaligned data
    for (d = 4; d < M+4; d++){
      C[c][d] = C[c][d] + A[c][d-1] + A[c][d-1];
    }
  }
}

void stencil_vect0()
{

  unsigned int c,d;

  for (c = 4 ; c < N+4; c++)
  {
    // aligned and unaligned data in one loop
    for (d = 4 ; d < M+4; d++){
      C[c][d] = 4*A[c][d] + A[c-1][d] + A[c+1][d] + A[c][d-1] + A[c][d+1];
    }
  }
}
