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

unsigned int g_errors = 0;

unsigned int getNbErrors()
{
  return g_errors;
}

void print_okay(const int testnr, const char *testsuite) {
  printf("Test suite OK: %s\n", testsuite);
}

void print_fail(const int testnr, const char *testsuite) {
  g_errors++;
  printf("Test FAIL: %d (suite %s)\n", testnr, testsuite);
}


void print_test_summary()
{
  volatile int* ptr = (int*)(0x10001000+get_core_id()*4*2);

  printf("==== SUMMARY: ");
  ptr[1] = g_errors;

  if (g_errors == 0) {
    printf("OOOOOOK!!!!!!\n");
    ptr[0] = 0xABBAABBA;
  } else {
    printf("NOT OK!!!!!\n");
    ptr[0] = 0xDEADBEEF;
  }
}
