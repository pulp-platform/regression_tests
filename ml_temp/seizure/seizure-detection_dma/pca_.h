#ifndef PCA__H_
#define PCA__H_
#include <stdint.h>
#include "init.h"

int PCA(int lunghezza_finestra, int numero_canali, float output[][window]); 
void mean_covariance(float datiInput[][window], float a[channels*channels]);

float householder(float a[channels*channels], float rv1[channels], float w[channels]);

void accumulate(float v[channels*channels], float a[channels*channels], float rv1[channels]);

void diagonalize(float w[channels], float rv1[channels], float v[channels*channels], float anorm);
static float PYTHAG(float a, float b);

void PC(float datiInput[][window], float datioutput[][window], float v[channels*channels]);


#endif /* PCA__H_ */
