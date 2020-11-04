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
#include <stdio.h>

// Stencil code
#include "stencil.h"

__attribute__ ((section(".heapsram"))) int D[N*M];
__attribute__ ((section(".heapsram"))) int R[N*M];
__attribute__ ((section(".heapsram"))) int W[N];

__attribute__ ((section(".heapsram"))) int neighbors[4];
__attribute__ ((section(".heapsram"))) int weights[4];

void stencil(int*,int*,int*);
void getEntries(int*,int*,int*,int*,unsigned int, unsigned int);


// matrixMul code
#include "matrixMul.h"

__attribute__ ((section(".heapsram"))) int h_A[WA * HA];
__attribute__ ((section(".heapsram"))) int h_B[WB * HB];
__attribute__ ((section(".heapsram"))) int h_C[WC * HC];

void computeGoldMatrixMul(volatile int*,volatile int*,volatile int*, unsigned int, unsigned int, unsigned int);


// sudokusolver code
#include "sudokusolver.h"

__attribute__ ((section(".heapsram"))) int grid_init[SUDOKUSIZE*SUDOKUSIZE];
__attribute__ ((section(".heapsram"))) int grid_solved[SUDOKUSIZE*SUDOKUSIZE];
__attribute__ ((section(".heapsram"))) int solved[1];

int safe(int*, int, int, int);
void solve(int*, int, int, int*);
void sudokusolver(int*, int*);
// --

// towerofhanoi code
#define NR_PLATES 12

__attribute__ ((section(".heapsram"))) char A[NR_PLATES];
__attribute__ ((section(".heapsram"))) char B[NR_PLATES];
__attribute__ ((section(".heapsram"))) char C[NR_PLATES];

void ToH(int, char*, char*, char*);
void computeGoldToH(int, char*, char*, char*);
// --

static int globalErrors = 0;

int main()
{
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
  
  // Common variables
  int coreid;
  int error=0;

  // ToH variables
  int n_toh, i_toh, j_toh;

  // MatrixMul variables
  int i_mm;

  // Sudokusolver variables
  int i_ss,j_ss,k_ss;

  // stencil variables
  int i_st,j_st,k_st;

  coreid = rt_core_id();

  if (coreid == 1) {
    n_toh = NR_PLATES;

    printf("Start Tower of Hanoi\n");

    for (j_toh=0; j_toh<2; j_toh++) {
      for (i_toh=0;i_toh<n_toh;i_toh++){
        A[i_toh] = i_toh;
        B[i_toh] = 0;
        C[i_toh] = 0;
      }

    computeGoldToH(n_toh, A, B, C);
    printf("Iteration %d completed\n",j_toh);
    }

    for (i_toh=0;i_toh<n_toh;i_toh++) {
      if (B[i_toh] != i_toh) {
        error = error + 1;
      }
    }

  } else if (coreid == 0) {
   printf("start sudokusolver\n");

   // store sudoku to solve in grid_init
   for (i_ss=0;i_ss<9;i_ss++){
     for (j_ss=0;j_ss<9;j_ss++){
        grid_init[i_ss*SUDOKUSIZE+j_ss] = 0;
     }
   }
  /*   /\* grid_init[0*SUDOKUSIZE+7] = 1; grid_init[0*SUDOKUSIZE+8] = 2; grid_init[1*SUDOKUSIZE+0] = 4; grid_init[1*SUDOKUSIZE+4] = 9; grid_init[2*SUDOKUSIZE+7] = 5; *\/ */
  /*   /\* grid_init[3*SUDOKUSIZE+1] = 7; grid_init[3*SUDOKUSIZE+3] = 2; grid_init[4*SUDOKUSIZE+0] = 6; grid_init[4*SUDOKUSIZE+6] = 4; grid_init[5*SUDOKUSIZE+3] = 1; *\/ */
  /*   /\* grid_init[5*SUDOKUSIZE+5] = 8; grid_init[6*SUDOKUSIZE+1] = 1; grid_init[6*SUDOKUSIZE+2] = 8; grid_init[7*SUDOKUSIZE+4] = 3; grid_init[7*SUDOKUSIZE+6] = 7; *\/ */
  /*   /\* grid_init[8*SUDOKUSIZE+0] = 5; grid_init[8*SUDOKUSIZE+2] = 2; *\/ */

   grid_init[0*SUDOKUSIZE+1] = 9; grid_init[0*SUDOKUSIZE+2] = 3; grid_init[0*SUDOKUSIZE+3] = 1; grid_init[0*SUDOKUSIZE+5] = 5; grid_init[0*SUDOKUSIZE+6] = 6; grid_init[0*SUDOKUSIZE+7] = 4;
   grid_init[1*SUDOKUSIZE+0] = 7; grid_init[1*SUDOKUSIZE+8] = 5;
   grid_init[2*SUDOKUSIZE+0] = 5; grid_init[2*SUDOKUSIZE+2] = 1; grid_init[2*SUDOKUSIZE+3] = 2; grid_init[2*SUDOKUSIZE+5] = 9; grid_init[2*SUDOKUSIZE+6] = 3; grid_init[2*SUDOKUSIZE+8] = 7;
   grid_init[3*SUDOKUSIZE+0] = 2; grid_init[3*SUDOKUSIZE+8] = 3;
   grid_init[4*SUDOKUSIZE+1] = 3; grid_init[4*SUDOKUSIZE+2] = 6; grid_init[4*SUDOKUSIZE+3] = 9; grid_init[4*SUDOKUSIZE+5] = 7; grid_init[4*SUDOKUSIZE+6] = 5; grid_init[4*SUDOKUSIZE+7] = 2;
   grid_init[5*SUDOKUSIZE+0] = 9; grid_init[5*SUDOKUSIZE+8] = 1;
   grid_init[6*SUDOKUSIZE+0] = 3; grid_init[6*SUDOKUSIZE+2] = 2; grid_init[6*SUDOKUSIZE+3] = 4; grid_init[6*SUDOKUSIZE+5] = 8; grid_init[6*SUDOKUSIZE+6] = 1; grid_init[6*SUDOKUSIZE+8] = 9;
   grid_init[7*SUDOKUSIZE+0] = 6; grid_init[7*SUDOKUSIZE+8] = 4;
   grid_init[8*SUDOKUSIZE+1] = 4; grid_init[8*SUDOKUSIZE+2] = 7; grid_init[8*SUDOKUSIZE+3] = 3; grid_init[8*SUDOKUSIZE+5] = 2; grid_init[8*SUDOKUSIZE+6] = 8; grid_init[8*SUDOKUSIZE+7] = 5;

   // loop two times. (cold/hot IC)
   for (k_ss=0;k_ss<2;k_ss++) {
     // reset result grid_solved and solved
     for (i_ss=0;i_ss<9;i_ss++){
        for (j_ss=0;j_ss<9;j_ss++){
          grid_solved[i_ss*SUDOKUSIZE+j_ss] = grid_init[i_ss*SUDOKUSIZE+j_ss];
        }
     }
     solved[0] = 0;

     // start solver
     sudokusolver(grid_solved, solved);
     printf("Iteration %d completed\n",k_ss);
   }

   // print solution
   printf("Solution:\n");

   for (i_ss=0;i_ss<9;i_ss++){
     printf("\n");
     for (j_ss=0;j_ss<9;j_ss++){
        printf("%d ",grid_solved[i_ss*SUDOKUSIZE+j_ss]);
     }
   }
   printf("\n");

   // check result!
   for (i_ss=0;i_ss<SUDOKUSIZE;i_ss++) {
     for (k_ss=0;k_ss<SUDOKUSIZE;k_ss++) {
        if (SUDOKUSOLVED[i_ss*SUDOKUSIZE+k_ss] != grid_solved[i_ss*SUDOKUSIZE+k_ss]) {
          error = error + 1;
#ifdef DEBUG_OUTPUT
          printf("Error occurred at i=%d k=%d; Computed result %d does not match expected result %d\n",i_ss,k_ss,grid_solved[i_ss*SUDOKUSIZE+k_ss],SUDOKUSOLVED[i_ss*SUDOKUSIZE+k_ss]);
#endif
        }
     }
   }

  } else if (coreid == 2) {

    printf("start MatrixMul\n");

    for (i_mm = 0; i_mm < WA * HA; i_mm++)
      h_A[i_mm] = i_mm;

    for (i_mm = 0; i_mm < WB * HB; i_mm++)
      h_B[i_mm] = i_mm;

    for (i_mm = 0; i_mm<2; i_mm++) {
      computeGoldMatrixMul(h_C, h_A, h_B, HA, WA, WB);
      printf("Iteration %d completed\n",i_mm);
    }

    for (i_mm=0; i_mm<WC*HC; i_mm++) {
      if (h_C[i_mm] != RESULT_MUL[i_mm]) {
#ifdef DEBUG_OUTPUT
        printf("expected result: %d, actual result: %d\n",RESULT_MUL[i_mm],h_C[i_mm]);
#endif
        error = error + 1;
      }
    }
  } else if (coreid == 3){

    printf("start stencil\n");

    for (i_st=0;i_st<N;i_st++) {
      for (k_st=0;k_st<M;k_st++)
        D[i_st*M+k_st] = i_st+k_st+1;
      /* D[i_st*n+k_st] = 1549578963*i_st-k_st; */
      /* W[i_st] = 3534442427*i_st; */
      W[i_st] = i_st+2;
    }

    for (j_st = 0; j_st<2; j_st++) {
      stencil(D, R, W);
      printf("Iteration %d completed\n",j_st);
    }

   for (i_st=0;i_st<N;i_st++) { 
     for (k_st=0;k_st<M;k_st++) {
       //       printf("%d %d\n",RESULT[i*M+k],R[i*M+k],0,0); 
       if (RESULT_STENCIL[i_st*M+k_st] != R[i_st*M+k_st]) {
         error = error + 1;
#ifdef DEBUG_OUTPUT
         printf("Error occurred at i=%d k=%d; Computed result R=%d does not match expected Result=%d\n",i_st,k_st,R[i_st*M+k_st],RESULT_STENCIL[i_st*M+k_st]);
#endif
       }
     }
   }
  }

  synch_barrier();
  if (coreid == 0) globalErrors += error;
  synch_barrier();
  if (coreid == 1) globalErrors += error;
  synch_barrier();
  if (coreid == 2) globalErrors += error;
  synch_barrier();
  if (coreid == 3) globalErrors += error;
  synch_barrier();


  print_summary((unsigned int) error);

  return globalErrors;
}

// stencil code
void stencil(int* D, int* R, int* W)
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
      getEntries(neighbors, weights, D, W, c, d);
      //printf("neighbors %d %d %d %d\n",neighbors[0],neighbors[1],neighbors[2],neighbors[3]);
      //printf("weights   %d %d %d %d\n",weights[0],weights[1],weights[2],weights[3]);
      R[c*M+d] = D[c*M+d] + neighbors[3]*weights[3] + neighbors[0]*weights[0] + neighbors[1]*weights[1] + neighbors[2]*weights[2];

      //printf("D: %d\n",D[c*M+d],0,0,0);
      //printf("R: %d\n",R[c*M+d],0,0,0);
    }
  }
}
 
void getEntries(int* neighbors, int* weights, int* D, int* W, unsigned int c, unsigned int d)
{
  // top&buttom pixel
  if (c==0) {
    neighbors[0] = 0;
    neighbors[3] = D[(c+1)*M+d];
    weights[0] = 0;
    weights[3] = W[c+1];
  } else if (c==N-1) {
    neighbors[0] = D[(c-1)*M+d];
    neighbors[3] = 0;
    weights[0] = W[c-1];
    weights[3] = 0;
  } else {
    neighbors[0] = D[(c-1)*M+d];
    neighbors[3] = D[(c+1)*M+d];
    weights[0] = W[c-1];
    weights[3] = W[c+1];
  }

  // left&right pixel
  if (d==0) {
    neighbors[1] = 0;
    neighbors[2] = D[c*M+d+1];
    weights[1] = 0;
    weights[2] = W[c];
  } else if (d==M-1) {
    neighbors[1] = D[c*M+d-1];
    neighbors[2] = 0;
    weights[1] = W[c];
    weights[2] = 0;
  } else {
    neighbors[1] = D[c*M+d-1];
    neighbors[2] = D[c*M+d+1];
    weights[1] = W[c];
    weights[2] = W[c];
  }
}


// matrixMul code
void computeGoldMatrixMul(volatile int* h_C, volatile int* h_A,volatile int* h_B, unsigned int hA, unsigned int wA, unsigned int wB)
{
  unsigned int i,j,k;
  unsigned int a,b,sum;

  for (i = 0; i < hA; ++i){
    for (j = 0; j < wB; ++j) {
      sum = 0;
      for (k = 0; k < wA; ++k) {
        a = h_A[i * wA + k];
        b = h_B[k * wB + j];
        sum += a * b;
      }
      h_C[i * wB + j] = (unsigned int)sum;
    }
  }
}


// sudokusolver code

// start solver. (this function is used for profiling)
void sudokusolver(int* grid_solved, int* solved)
{
  solve(grid_solved, 0, 0, solved);
}

// check if current index doesnt violate any sudoku constraints
int safe(int* grid_solved, int row, int col, int n)
{
  int r, c, br, bc;

  if (grid_solved[row*SUDOKUSIZE+col] == n) return 1;

  if (grid_solved[row*SUDOKUSIZE+col] != 0) return 0;

  for (c = 0; c < 9; c++)
    if (grid_solved[row*SUDOKUSIZE+c] == n) return 0;

  for (r = 0; r < 9; r++)
    if (grid_solved[r*SUDOKUSIZE+col] == n) return 0;

  /* br = row / 3; */
  /* bc = col / 3; */

  if (row>5)
    br = 2;
  else if (row>2)
    br = 1;
  else
    br = 0;

  if (col>5)
    bc = 2;
  else if (col>2)
    bc = 1;
  else
    bc = 0;

  for (r = br * 3; r < (br + 1) * 3; r++)
    for (c = bc * 3; c < (bc + 1) * 3; c++)
      if (grid_solved[r*SUDOKUSIZE+c] == n) return 0;

  return 1;
}

// solve sudoku! brute force
void solve(int* grid_solved, int row, int col, int* solved)
{
  int n, t;

  if (row == 9) {
    solved[0] = 1;
  } else {
    for (n = 1; n <= 9; n++) {
      if (safe(grid_solved, row, col, n)) {
        t = grid_solved[row*SUDOKUSIZE+col];
        grid_solved[row*SUDOKUSIZE+col] = n;

        if (col == 8)
          solve(grid_solved, row + 1, 0, solved);
        else
          solve(grid_solved, row, col + 1, solved);

        if (solved[0] == 0)
          grid_solved[row*SUDOKUSIZE+col] = t;
        else
          return;
      }
    }
  }
}

// towerofhanoi code!

void computeGoldToH(int n, char* A, char* B, char* C)
{
  char tmp;
  A[1] = 1;
  ToH(n-1,A,B,C);
  // small hack to add two more lines of code(easier for profiling, doesnt change anything)
  tmp = C[n-2];
  C[n-1] = tmp+1;
}

void ToH(int n,char* A,char* B,char* C)
{
 if(n==0)
 {
   B[n] = A[n];
   A[n] = 0;
 }
 else {
   ToH(n-1,A,C,B);
   B[n] = A[n];
   A[n] = 0;
   ToH(n-1,C,B,A);
 }
}
