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

#define N 5

void computeGold(volatile int, volatile float [N][N]);
RT_LOCAL_DATA float a[N][N];

int main(){

  if (get_core_id() == 0)
  {
    int l;
    int T=20;

    for (l = 0; l<1; l++){
      computeGold(T,a);
    }
  }

  return 0;
}


void init_array(){
    int i, j;

    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            a[i][j] = i*i+j*j;
        }
    }
}

void computeGold(volatile int T, volatile float a[N][N]){
  int t,i,j;

  init_array();

  reset_timer();
  start_timer();

  for (t=0; t<=T-1; t++)  {
    for (i=1; i<=N-2; i++)  {
      for (j=1; j<=N-2; j++)  {
        a[i][j] = (a[i-1][j-1] + a[i-1][j] + a[i-1][j+1] 
            + a[i][j-1] + a[i][j] + a[i][j+1]
            + a[i+1][j-1] + a[i+1][j] + a[i+1][j+1])/9.0f;
      }
    }
  }
  stop_timer();
  printf("Cycles: %d\n", get_time());
}
