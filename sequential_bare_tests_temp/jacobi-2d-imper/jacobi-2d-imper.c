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
#include <stdio.h>
#include <stdlib.h>
#include "pulp.h"

#define N 20
#define T 2

float a[N][N];
float b[N][N];

void init_array()
{
    int i, j;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            a[i][j] = ((float)j)/N;
        }
    }
}


int main()
{
  if (get_core_id() == 0)
    {
      int t, i, j;
      float t_start, t_end;

      init_array();

      reset_timer();
      start_timer();

      for (t=0; t<T; t++) {
        for (i=2; i<N-1; i++) {
          for (j=2; j<N-1; j++) {
            b[i][j]= 0.2f*(a[i][j]+a[i][j-1]+a[i][1+j]+a[1+i][j]+a[i-1][j]);
          }
        }
        for (i=2; i<N-1; i++) {
          for (j=2; j<N-1; j++)   {
            a[i][j]=b[i][j];
          }
        }

      }

      stop_timer();
      printf("Cycles: %d\n", get_time());
    }

    return 0;
}
