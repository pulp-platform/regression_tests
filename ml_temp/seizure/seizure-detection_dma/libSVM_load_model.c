#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <locale.h>
#include <math.h>
#include "init.h"
//#include "modelSVM.h"
#include "libSVM_predict.h"

#include "pulp.h"

PULP_L1_DATA extern struct svm_model *model;
PULP_L1_DATA struct svm_node **predict_data;

PULP_L1_DATA int sample_count = 0;
PULP_L1_DATA int N_smaple = 1;


// load model from handcoded values...
void svm_load_model()
{
        int i = 0;
        int j=0;
        #if HWPERFMALLOC
	perf_start();
        #endif
	model = (struct svm_model*) plp_alloc_l1((int)(sizeof(struct svm_model)));
	//printf("malloc %x \n",model);
        #if HWPERFMALLOC
	perf_stop();
	printf("STOP alloc\n"); perf_print_all();
        #endif
        model->param.svm_type = 0;
        model->param.kernel_type = 2;
        model->param.degree = 0;
        model->param.gamma = 0.0277778F;
        model->param.coef0 = 0;
        model->nr_class = 2;
        model->l = 315;
        
        int n = model->nr_class * (model->nr_class-1)/2;
        
	int m = model->nr_class - 1;
        int l = model->l;
        #if HWPERFMALLOC
	perf_start();
        #endif
	model->rho = (float *) plp_alloc_l1((int)(sizeof(float)*n));
	model->label = (int*)plp_alloc_l1((int)(sizeof(int)*model->nr_class));
	model->nSV = (int*)plp_alloc_l1((int)(sizeof(int)*model->nr_class));
        model->sv_coef = (float**) plp_alloc_l1((int)(sizeof(float)*m));
        model->SV = (svm_node**) plp_alloc_l1((int)(sizeof(svm_node)*l));
	//printf("malloc %x %x %x %x %x \n",model->rho,model->label,model->nSV,model->sv_coef,model->SV);
        #if HWPERFMALLOC
	perf_stop();
	printf("STOP alloc\n"); perf_print_all();
        #endif
	model->rho[0] = 0.138475F;
 	model->label[0] = 0;
        model->label[1] = 1;
        
	model->nSV[0] = 161;
        model->nSV[1] = 154;
#ifdef DEBUG	
	printf("load model %d \n", (int) (1000.0F *model->param.gamma));
#endif
        }
