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

#define N 100
#define T 10
RT_LOCAL_DATA float h[N];
RT_LOCAL_DATA float e[N+1];
#define coeff1 0.5f
#define coeff2 0.7f

void init_array()
{
    int i, j;

        for (j=0; j<N; j++) {
            h[j] = ((float)j)/N;
            e[j] = ((float)j)/N;
        }
}

int main()
{
    int t, i, j, k, l;

    init_array();

    reset_timer();
    start_timer();

    for (t=1; t<=T; t++){
      for (i=1; i<=N-1; i++) {
        e[i] = e[i] - coeff1*(h[i]-h[i-1]);
      }
      for (i=0; i<N-1; i++) {
        h[i] = h[i] - coeff2*(e[i+1]-e[i]);
      }
    }

    printf("Cycles: %d\n", get_time());

    return 0;
}
