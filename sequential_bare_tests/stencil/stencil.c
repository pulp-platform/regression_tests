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
#include "pulp.h"

/* Stencil code */
#include "stencil.h"

void stencil(int*,int*,int*);
void getEntries(int*,int*,int*,int*,unsigned int, unsigned int);

RT_LOCAL_DATA int h_R[N*M];
RT_LOCAL_DATA int A[N*M];
RT_LOCAL_DATA int W[N];

RT_LOCAL_DATA int neighbors[4];
RT_LOCAL_DATA int weights[4];

void check_stencil(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "stencil",   .test = check_stencil       },
  {0, 0}
};

int main()
{
  if (get_core_id() == 0)
    return run_suite(testcases);
  else
    return 0;
}

void check_stencil(testresult_t *result, void (*start)(), void (*stop)())
{
  int i,j,k;
  int error = 0;
 
  printf("Start stencil\n");
  
  for (i=0;i<N;i++) {
    for (k=0;k<M;k++)
      A[i*M+k] = i+k+1;
    /* A[i*n+k] = 1549578963*i-k; */
    /* W[i] = 3534442427*i; */
    W[i] = i+2;
  }

  for (j = 0; j<2; j++) {

    start();
    stencil(A, h_R, W);
    stop();
  }

  for (i=0;i<N;i++) {
    for (k=0;k<M;k++) {
#ifdef DEBUG_OUTPUT
      printf("%d %d\n",RESULT[i*M+k],R[i*M+k],0,0);
#endif
      if (RESULT_STENCIL[i*M+k] != h_R[i*M+k]) {
	result->errors++;
#ifdef DEBUG_OUTPUT
	printf("Error occurred at i=%d k=%d; Computed result R=%d does not match expected Result=%d\n",i,k,h_R[i*M+k],RESULT_STENCIL[i*M+k]);
#endif
      }
    }
  }
}


void stencil(int* A, int* h_R, int* W)
{
  unsigned int c,d;

  neighbors[0] = 0;
  neighbors[1] = 0;
  neighbors[2] = 0;
  neighbors[3] = 0;
  weights[0] = 0;
  weights[1] = 0;
  weights[2] = 0;
  weights[3] = 0;

  for (c = 0 ; c < N; c++)
  {
    for (d = 0 ; d < M; d++)
    {
      getEntries(neighbors, weights, A, W, c, d);
#ifdef DEBUG_OUTPUT
      printf("neighbors %d %d %d %d\n",neighbors[0],neighbors[1],neighbors[2],neighbors[3]);
      printf("weights   %d %d %d %d\n",weights[0],weights[1],weights[2],weights[3]);
#endif
      h_R[c*M+d] = A[c*M+d] + neighbors[3]*weights[3] + neighbors[0]*weights[0] + neighbors[1]*weights[1] + neighbors[2]*weights[2];

#ifdef DEBUG_OUTPUT
      printf("A: %d\n",A[c*M+d],0,0,0);
      printf("RESULT: %d\n",RESULT[c*M+d],0,0,0);
#endif
    }
  }
}

void getEntries(int* neighbors, int* weights, int* A, int* W, unsigned int c, unsigned int d)
{
  // top&buttom pixel
  if (c==0) {
    neighbors[0] = 0;
    neighbors[3] = A[(c+1)*M+d];
    weights[0] = 0;
    weights[3] = W[c+1];
  }
  else if (c==N-1) {
    neighbors[0] = A[(c-1)*M+d];
    neighbors[3] = 0;
    weights[0] = W[c-1];
    weights[3] = 0;
  }
  else {
    neighbors[0] = A[(c-1)*M+d];
    neighbors[3] = A[(c+1)*M+d];
    weights[0] = W[c-1];
    weights[3] = W[c+1];
  }

  // left&right pixel
  if (d==0) {
    neighbors[1] = 0;
    neighbors[2] = A[c*M+d+1];
    weights[1] = 0;
    weights[2] = W[c];
  }
  else if (d==M-1) {
    neighbors[1] = A[c*M+d-1];
    neighbors[2] = 0;
    weights[1] = W[c];
    weights[2] = 0;
  }
  else {
    neighbors[1] = A[c*M+d-1];
    neighbors[2] = A[c*M+d+1];
    weights[1] = W[c];
    weights[2] = W[c];
  }
}
