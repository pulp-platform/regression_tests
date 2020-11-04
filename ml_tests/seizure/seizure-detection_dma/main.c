#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include "pca_.h"
#include "wavelet_.h"
#include "libSVM_predict.h"
#include "libSVM_load_model.h"
#include "pulp.h"
#include "init.h"
#include "mlShared.h"

//TO SELECT THE NUMBER OF CORES FOR THE MULTI-CORE EXECUTION JUST CHANGE THE DEFINED VARIABLE "CORE" IN init.h
//TO EXECUTE THE MULTI-CORE APPLICATION COMPILE AND RUN WITH: make clean all run pulpFpu=1 pulpDiv=1 
//FOR THE 8 CORES ONLY: make clean all run pulpFpu=1 pulpDiv=1 nbPe=8
//TO EXECUTE THE APPLICATION IN SEQUENTIAL COMPILE AND RUN WITH: make clean all run pulpFpu=1 pulpDiv=1 -f Makefile.seq  


float datiOutput[channels][window];



PULP_L1_DATA int components;
	
PULP_L1_DATA int i;
PULP_L1_DATA int j=0;

PULP_L1_DATA float energy_matrix[4][channels];
PULP_L1_DATA float energy_vector[4];
PULP_L1_DATA float dwt[window];

PULP_L1_DATA extern struct svm_node *x;
PULP_L1_DATA extern struct svm_model *model;

int main()
{
	if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

        init_fp_regs();
	printf("Start Seizure detection application\n");
        #ifdef SEQ
        if(rt_core_id())
                return 0;
        #endif
        
        #if HWPERF
	perf_begin();
        #endif

                svm_node x1[37]; 
                //PCA: call the funcion for Principal Component Analysis. components is the number of Principal Component we consider. 
                components=PCA(window, channels, datiOutput);
                
                //ptr_energy_vector=energy_vector;
                
                //DWT: call the function gsl_wavelet_transform for all the PC. The result is in the vector dwt. 
                //Energy: call the funcion calcolo_energia. We compute the energy of dwt. The result goes in energy_matrix.  
                
                #if HWPERF_FUNC
		perf_stop();
		printf("START DWT\n"); perf_print_all();
		perf_start();
                #endif

		//printf("start omp parallel\n");
#pragma omp parallel private(dwt, i, energy_vector) shared(energy_matrix) num_threads(CORE)//shared(energy_matrix)
                {
		  
		  gsl_wavelet_workspace *ptr_workspace;
#if HWPERFMALLOC
		  perf_start();
#endif
		  ptr_workspace          = plp_alloc_l1((int)sizeof(gsl_wavelet_workspace));
		  ptr_workspace->scratch = plp_alloc_l1((int)(window*sizeof(float)));
		  //printf("malloc %x %x \n",ptr_workspace,ptr_workspace->scratch);
		  ptr_workspace->n       = window;
#if HWPERFMALLOC
		  perf_stop();
		  printf("STOP alloc\n"); perf_print_all();
#endif


                        #pragma omp for
                        for (j=0; j<components; j++){
                                int indx=0;
                                
                                for(indx=0; indx<window; indx++){
                                        
                                        dwt[indx]=datiOutput[j][indx]; //printf("%d:iter %d, dwt[%d]=%d\n", omp_get_thread_num(), j, indx, (int)dwt[indx]);     
                                        
                                }
                                //printf("start wavelet transform\n");
                                gsl_wavelet_transform (dwt, 1, window, ptr_workspace);
                                //printf("finish wavelet transform\n");
                                //printf("start energy computation\n");
                                calcolo_energia(dwt, energy_vector);
                                //printf("finish energy computation\n");
                                
                                
                                
                                for(i=0;i<4;i++){
                                        
				  energy_matrix[i][j]=energy_vector[i]; //printf("%d\t\t", (int)energy_vector[i]);
				  x1[((j)*4)+i].index=((j)*4)+i+1;
				  x1[((j)*4)+i].value=fDiv(energy_vector[i],100000.0f); //printf("\nX:%d\n", (int)(x1[((j)*4)+i].value));
                                }
                                
                                
                        }
                        #pragma omp barrier
#if HWPERFFREE
			perf_start();
#endif
			l1free(ptr_workspace->scratch);
			l1free(ptr_workspace);
			ptr_workspace->scratch = NULL;
			ptr_workspace = NULL;
#if HWPERFFREE
			perf_stop();
			printf("FREE\n"); perf_print_all();
#endif
                
		}//omp
		
                x1[36].index=-1;
                x1[36].value=0.0f;
                
                #if HWPERF_FUNC
		perf_stop();
		printf("END DWT\n"); perf_print_all();
                #endif

		#if HWPERF
		perf_stop();
		#endif

#ifdef DEBUG
		float sum;
		sum = 0.0F;
		for(i=0;i<36;i++){
		  sum +=  1000.0F*fAbs(x1[i].value);
		}
		printf("sum of x1: %d\n", (int) sum);
#endif

                printf("\nENERGY MATRIX\n\n");

                for(j=0;j<4;j++){
		  for(i=0;i<components;i++){
                                
		    printf("%d\t", (int)energy_matrix[j][i]);
                                
		  }
		  printf("\n");
                }
                
                #if HWPERF
		perf_start();
                #endif
                
                //SVM: call the funcion svm_load_model , svm_init_data and svm_predict_values to perform the classification.
		//                printf("start svm load model\n");
                
                #if HWPERF_FUNC
		perf_stop();
		printf("START SVM\n"); perf_print_all();
		perf_start();
                #endif
		
		svm_load_model();
                
#if HWPERFMALLOC
		perf_start();
#endif
		float * dec_values = NULL;
		dec_values = (float*) plp_alloc_l1((int)(sizeof(float)*model->nr_class*fDiv((model->nr_class-1),2)));
		//printf("malloc %x \n",dec_values);
                
		svm_predict_values( x1, dec_values);
		//		printf("finish svm predict\n");
                

#if HWPERFFREE
		perf_start();
#endif
		l1free(dec_values);
		dec_values     = NULL;
		svm_free_and_destroy_model(model);

#if HWPERFFREE
		perf_stop();
		printf("FREE\n"); perf_print_all();
#endif

                #if HWPERF_FUNC
		printf("END SVM\n");
		#endif
		#if HWPERF
		perf_end();
                #endif  
        
        return 0;
}


