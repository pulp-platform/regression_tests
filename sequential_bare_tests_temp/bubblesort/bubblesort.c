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
#include <stdio.h>

/* Bubble sort code */

#define N 100

void check_bubbleSort(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "bubbleSort",          .test = check_bubbleSort           },
  {0, 0}
};

int main()
{
  int coreid;
  
  coreid = get_core_id();

  if(coreid == 0)
    return run_suite(testcases);
  else
    return 0;
}

void bubbleSort(volatile int*,int);


RT_LOCAL_DATA int array[N];

void check_bubbleSort(testresult_t *result, void (*start)(), void (*stop)()) {
  int i,j;
  int n = N;
  
  printf("Start bubblesort\n");
  
  start();
  
  for (j = 0; j<2; j++) {
    
    for (i=0;i<n;i++)
      array[i] = 2*n-i;
    
    reset_timer();
    
    start_timer();
    
    bubbleSort(array, n);
    
    stop_timer();
    
  }
  
  stop();

  for (i=0;i<n;i++) {
    if (array[N-1-i] != 2*n-i) {
      printf("expected: %d, actual: %d\n",2*n-i,array[N-1-i]);
      result->errors++;
    }
  }
}


void bubbleSort(volatile int* array, int n)
{
  int c,d;
  int swap;

  for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (array[d] > array[d+1]) /* For decreasing order use < */
      {
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
      }
    }
  }
}
