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

/* Fibonacci Series c language */


//#define N 10
//const int RESULT_FIB[N] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
#define N 20
const int RESULT_FIB[N] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181};
//#define N 25
//const int RESULT_FIB[N] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368};

void check_fibonacci(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "fibonacci",   .test = check_fibonacci       },
  {0, 0}
};

int main()
{
  if (get_core_id() == 0)
    return run_suite(testcases);
  else
    return 0;
}

int recFib(int);
void fib(int*, int);

RT_LOCAL_DATA int array[N];

void check_fibonacci(testresult_t *result, void (*start)(), void (*stop)())
{
  int i=0,j, c;
  int n=N;
  
  printf("Start fibonacci\n");

  start();
  fib(array, n);
  stop();


  for (i=0;i<n;i++) {
    if (RESULT_FIB[i] != array[i]) {
      printf("expected: %d, actual: %d\n",RESULT_FIB[i],array[i]);
      result->errors++;
    }
  }
}

int recFib(int n)
{
   if ( n == 0 )
      return 0;
   else if ( n == 1 )
      return 1;
   else
      return (recFib(n-1) + recFib(n-2));
}

void fib(int* array, int n)
{
  int i=0;
  int c;

  for (c=0; c<=(n-1); c++ )
    {
      array[c] = recFib(i);
      i++;
    }
}
