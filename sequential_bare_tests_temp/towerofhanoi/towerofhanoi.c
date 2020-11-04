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

#define NR_PLATES 12

void ToH(int, char*, char*, char*);

void computeGold(int, char*, char*, char*);
void check(testresult_t *result, void (*start)(), void (*stop)());

RT_LOCAL_DATA char A[NR_PLATES];
RT_LOCAL_DATA char B[NR_PLATES];
RT_LOCAL_DATA char C[NR_PLATES];

testcase_t testcases[] = {
  { .name = "towerofhanoi",   .test = check       },
  {0, 0}
};

int main() {
  if (get_core_id() == 0)
    return run_suite(testcases);
  else
    return 0;
}

void check(testresult_t *result, void (*start)(), void (*stop)())
{
  int i,j;

  printf("Start towerofhanoi\n");

  for (i=0;i<NR_PLATES;i++){
    A[i] = i;
    B[i] = 0;
    C[i] = 0;
  }

  start();
  computeGold(NR_PLATES, A, B, C);
  stop();

  for (i=0;i<NR_PLATES;i++) {
    if (B[i] != i) {
#ifdef DEBUG_OUTPUT
      printf("expected: %d, actual: %d\n",i,B[i]);
#endif
      result->errors++;
    }
  }
  return;
}

void computeGold(int n, char* A, char* B, char* C)
{
  ToH(n-1,A,B,C);
}

void ToH(int n, char* A, char* B, char* C)
{
  if(n==0)
    {
      B[n] = A[n];
      A[n] = 0;
    }
  else {
    ToH(n-1,A,C,B);
    B[n] = A[n];
    A[n] = 0;
    ToH(n-1,C,B,A);
  }
 
}
