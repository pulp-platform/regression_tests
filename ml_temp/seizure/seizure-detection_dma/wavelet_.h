#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "pulp.h"
#include "init.h"

#define ELEMENT(a,stride,i) ((a)[(stride)*(i)])



PULP_L1_DATA static const float ch_2[2] = { 0.70710678118654752440, 0.70710678118654752440 };
PULP_L1_DATA static const float cg_2[2] = { 0.70710678118654752440, -(0.70710678118654752440) };

// float *ptr_scratch[window];
typedef enum
{
  gsl_wavelet_forward = 1, gsl_wavelet_backward = -1
}
gsl_wavelet_direction;

//DEF WAVELET E WORKSPACE
typedef struct
{
  const char *name;
  int (*init) (const float **h1, const float **g1,
               const float **h2, const float **g2, size_t * nc,
               size_t * offset, size_t member);
}
gsl_wavelet_type;

typedef struct
{
  //const gsl_wavelet_type *type;
  const float *h1;
  const float *g1;
  const float *h2;
  const float *g2;
  size_t nc;
  size_t offset;
}
gsl_wavelet;


typedef struct
{
  float *scratch;
  int n;
}
gsl_wavelet_workspace;


static void
dwt_step (const gsl_wavelet * w, float *a, size_t stride, size_t n,
          gsl_wavelet_direction dir, gsl_wavelet_workspace * work);
/*
int
gsl_wavelet_transform (const gsl_wavelet * w,
        float *data, size_t stride, size_t n,
        gsl_wavelet_workspace * work
                       );
*/
int gsl_wavelet_transform (float *data, size_t stride, size_t n, gsl_wavelet_workspace *ptr_workspace);

int wavelet_alloc(gsl_wavelet *ptr_wavelet);
int workspace_alloc(gsl_wavelet_workspace *ptr_workspace);
//int wavelet_alloc();
//int workspace_alloc();
void calcolo_energia(float *datiInput, float *Output);
