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
#ifndef OR10N_TESTS_H
#define OR10N_TESTS_H
#define OR10N_TESTS_PRINTF
#include <stdint.h>
#include <archi/pulp.h>


#define SR_OVERFLOW     0x800
#define SR_CARRY        0x400


unsigned int g_num_checks = 0;
unsigned int g_errors = 0;

#define test_init() test_init_int(__FILE__)
// since the global variables are not initialized we have to do that in a special function here
void test_init_int(const char* filename) {
  g_num_checks = 0;
  g_errors = 0;

#ifdef OR10N_TESTS_PRINTF
  printf("Starting %s\n", filename);
#endif
}

void test_check(const char* str, uint32_t act, uint32_t exp) {
  g_num_checks++;

  if(act != exp) {
    g_errors++;
#ifdef OR10N_TESTS_PRINTF
    printf("%s: Is %X, expected %X\n", str, act, exp);
#endif
  }
}

void test_check_flags(const char* str, uint32_t spr, uint32_t exp, uint32_t flags) {
  g_num_checks++;

  if((spr & flags) != (exp & flags)) {
    g_errors++;
#ifdef OR10N_TESTS_PRINTF
    printf("%s: SPR is %X, is %X, expected %X\n", str, spr, spr & flags, exp & flags);
#endif
  }
}

void test_check_overflow(const char* str, uint32_t spr, uint32_t exp) {
  g_num_checks++;

  if((spr & SR_OVERFLOW) != (exp & SR_OVERFLOW)) {
    g_errors++;
#ifdef OR10N_TESTS_PRINTF
    if(exp & SR_OVERFLOW)
      printf("%s: Overflow should have been set\n", str);
    else
      printf("%s: Overflow should not have been set\n", str);
#endif
  }
}

void test_check_carry(const char* str, uint32_t spr, uint32_t exp) {
  g_num_checks++;

  if((spr & SR_CARRY) != (exp & SR_CARRY)) {
    g_errors++;
#ifdef OR10N_TESTS_PRINTF
    if(exp & SR_CARRY)
      printf("%s: Carry should have been set\n", str);
    else
      printf("%s: Carry should not have been set\n", str);
#endif
  }
}

unsigned int test_get_num_errors(void) {
  return g_errors;
}

void test_report(void) {
#ifdef OR10N_TESTS_PRINTF
  printf("%d of %d checks failed\n", g_errors, g_num_checks);

  if(g_errors == 0)
    printf ("OOOOOOK!!!!!!\n");
  else
    printf("NOT OK!!!!!\n");
#endif
}

#endif
