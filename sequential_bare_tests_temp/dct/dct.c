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

#define M 8
double cos1[M][M+13];
double temp2d[M][M+23];
double block[M][M+43];
double sum2[M][M];

void init_array()
{
    int i, j;

    for (i=0; i<M; i++) {
        for (j=0; j<M; j++) {
            cos1[i][j] = (1+(i*j)%1024)/2.0f;
            block[i][j] = (1+(i*j)%1024)/2.0f;
        }
    }
}

int main()
{
  if (get_core_id() == 0)
    {
        int i, j, k, l, m, n, o, t;

        init_array();

	reset_timer();
        start_timer();

        for (i = 0; i < M; i++)
                for (j = 0; j < M; j++) {
                    temp2d[i][j] = 0.0;
                    for (k = 0; k < M; k++)
                        temp2d[i][j] = temp2d[i][j] + block[i][k] * cos1[j][k];
        }

        for (i = 0; i < M; i++)
                for (j = 0; j < M; j++) {
                    sum2[i][j] = 0.0;
                    for (k = 0; k < M; k++)
                        sum2[i][j] = sum2[i][j] + cos1[i][k] * temp2d[k][j];
                    block[i][j] = (sum2[i][j]);
        }

        stop_timer();
        printf("Cycles: %d\n", get_time());

    }

  return 0;
}
