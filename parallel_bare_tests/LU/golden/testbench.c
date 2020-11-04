#include <stdlib.h>
#include <stdio.h>

#define F 10000

#define MIN(a, b) (((a)<(b) ) ? (a): (b))
#define ABS(a)    (((a)>=0)? (a): (-(a)))

int factor(int *A[], int M, int N, int pivot[])
{
  int i, j, k, ii;
  int minMN = MIN(M,N);
  
  for (j=0; j<minMN; ++j)
  {
    // find pivot in column j and  test for singularity.
    
    int jp=j;
    
    int t = ABS(A[j][j]);
    for (i=j+1; i<M; ++i)
    {
      int ab = ABS(A[i][j]);
      if (ab > t)
      {
        jp = i;
        t = ab;
      }
    }
    
    pivot[j] = jp;
    
    // jp now has the index of maximum element
    // of column j, below the diagonal
    
    if (A[jp][j] == 0 )                 
      return 1;       // factorization failed because of zero pivot
    
    if (jp != j)
    {
      // swap rows j and jp
      int *tA = A[j];
      A[j] = A[jp];
      A[jp] = tA;
    }
    
    //for (i=0;i<N;i++)
    //  printf("%d, ",*(A[i]));
    
    //printf("\n");
    
    #pragma omp parallel
    {
      if (j<M-1)                // compute elements j+1:M of jth column
      {
        // note A(j,j), was A(jp,p) previously which was
        // guarranteed not to be zero (Label #1)
        //
        //printf("\nVALS = %d %d \n",  F, A[j][j]);
        int recp = (F * F) / A[j][j];
        
        #pragma omp for
        for (k=j+1; k<M; ++k)
        {
          //printf("---> %d %d (th: %d)\n", A[k][j], recp, omp_get_thread_num());
          A[k][j] *= recp;
          A[k][j] /= F;
          //printf("* (%d %d) --> %d \n", k, j, A[k][j]);
        }
      }
      
      if (j < minMN-1)
      {
        // rank-1 update to trailing submatrix:   E = E - x*y;
        //
        // E is the region A(j+1:M, j+1:N)
        // x is the column vector A(j+1:M,j)
        // y is row vector A(j,j+1:N)
        
        #pragma omp for
        for (ii=j+1; ii<M; ++ii)
        {
          int jj;
          int *Aii = A[ii];
          int *Aj  = A[j];
          int AiiJ = Aii[j];
          for (jj=j+1; jj<N; ++jj)
          {
            Aii[jj] -= (AiiJ * Aj[jj])/F;
            //printf("(%d %d) --> %d %d\n", ii, jj, (AiiJ * Aj[jj])/F, Aii[jj]);
          }
          
        }
      }
    }
  }
  
  return 0;
}


/* DATA */
/*
int G1[] = {12*F, 2*F, 1*F};
int G2[] = {2*F, 3*F, 2*F};
int G3[] = {1*F, 2*F, 1*F};
int *G[] = {G1, G2, G3};
int pivots[3];
*/

#define N 4

int elements[N*N];
int *G[N];
int pivots[N];
  
int main(int argc, char **argv)
{
  int i,j;
  
  /* random init */
  for(i=0; i<N*N; ++i)
    elements[i] = rand()%100;
  for(i=0; i<N; ++i)
    G[i] = elements+N*i;
  
  printf("int lu[N*N] = {\n");
  for(i=0; i<N; ++i){
    for(j=0; j<N; ++j){
      printf("%2d, ", elements[i*N + j]);
    }
    printf("\n");
  }
  printf("};\n\n");
  
  factor(G, N, N, pivots);
  
  printf("int lu_ref[N*N] = {\n");
  for(i=0; i<N; ++i){
    for(j=0; j<N; ++j){
      printf("%5d, ", elements[i*N + j]);
    }
    printf("\n");
  }
  printf("};\n");
  
  return 0;
}
