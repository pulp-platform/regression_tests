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
#include "common.h"


void fft(short *data, int len, short *wprBase, short *wpiBase) {

  int max = len;
  len <<= 1;
  int wstep = 1;
  while (max > 2) {
    
    short *wpr = wprBase;
    short *wpi = wpiBase;

    for (int m = 0; m < max; m +=2) {
      short wr = *wpr;
      short wi = *wpi;
      wpr+= wstep;
      wpi+= wstep;

      int step = max << 1;

      for (int i = m; i < len; i += step) {
        int j = i + max;

        short tr = data[i] - data[j];
        short ti = data[i+1] - data[j+1];

        data[i] += data[j];
        data[i+1] += data[j+1];

        int xr = ((wr * tr + wi * ti) << 1) + 0x8000;
        int xi = ((wr * ti - wi * tr) << 1) + 0x8000;

        data[j] = xr >> 16;
        data[j+1] = xi >> 16;
      }
    }
    max >>= 1;
    wstep <<= 1;
  }

  {
    int step = max << 1;

    for (int i = 0; i < len; i += step) {
      int j = i + max;

      short tr = data[i] - data[j];
      short ti = data[i+1] - data[j+1];

      data[i] += data[j];
      data[i+1] += data[j+1];


      data[j] = tr;
      data[j+1] = ti;
    }
  }


  #define SWAP(a, b) tmp=(a); (a)=(b); (b)=tmp

  data--;
  int j = 1;
  for (int i = 1; i < len; i += 2) {
    if(j > i) {
      short tmp;
      SWAP(data[j], data[i]);
      SWAP(data[j+1], data[i+1]);
    }
    int m = len>> 1;
    while (m >= 2 && j >m) {
      j -= m;
      m >>= 1;
    }
    j += m;
  }
}
