#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "pmsis.h"
// #include "pulp.h"

// #define PI_L1 __attribute__((section(".data_l1")))
#include "util.h"
#include "matmul.h"

// // our own utilities
// // defines: fopenCheck, freadCheck, fcloseCheck, fseekCheck, mallocCheck
// #include "../llm.c/llmc/utils.h"
// // defines: tokenizer_init, tokenizer_decode, tokenizer_free
// #include "../llm.c/llmc/tokenizer.h"
// // defines: dataloader_init, dataloader_reset, dataloader_next_batch, dataloader_free
// #include "../llm.c/llmc/dataloader.h"

//=============================================
#include "data.h"
// #include "gold.h"
// #include "/home/amir/UNI/karpathy/myllm.c/gold_temp.h"
#include "inc.h"
//=============================================
#define THRESHOLD       0.00010f

// definePrefArr


    PI_L1 float m[NUM_CORES];
    PI_L1 float v[NUM_CORES];
    PI_L1 float s;
    
    PI_L1 float dnorm_mean[NUM_CORES];
    PI_L1 float dnorm_norm_mean[NUM_CORES];
    
    PI_L1 float val[NUM_CORES];
    PI_L1 float expsum[NUM_CORES];

    PI_L1 float temp[NUM_CORES];
    
    PI_L1 float one = 1.0f;
    PI_L1 float zero = 0.0f;
    PI_L1 float maxval;
    PI_L1 float maxval_init = -10000.0f;
    PI_L1 float expsum_inv;

    PI_L1 int fast_exp_coef = 12102203;
    PI_L1 int fast_exp_bias = 1064866805;

    PI_L1 float gelu_const = 0.044715f;
    PI_L1 float half = 0.5f;
    PI_L1 float two = 2.0f;
    PI_L1 float three = 3.0f;
    PI_L1 float GELU_SCALING_FACTOR = 0.797884561;

    PI_L1 float sum[NUM_CORES];



    
    float* weightT ;
    float* doutT   ;


static inline float fSqrt(float a)
{
  float c;
  asm ("fsqrt.s %[c], %[a]\n"
		: [c] "=f" (c)
		: [a] "f"  (a));
  return c;
}

// void cluster_main();

// void pe_entry(void *arg){
// 	cluster_main();
// }

// void cluster_entry(void *arg){
// 	pi_cl_team_fork((NUM_CORES), pe_entry, 0);
// }

// static int test_entry(){

// 	// pi_perf_conf(1 << PI_PERF_CYCLES);

// 	struct pi_device cluster_dev;
// 	struct pi_cluster_conf cl_conf;
// 	struct pi_cluster_task cl_task;

// 	pi_cluster_conf_init(&cl_conf);

// 	cl_conf.id = 0;
// 	// cl_conf.icache_conf = PI_CLUSTER_MASTER_CORE_ICACHE_ENABLE |
// 	// 					// Enable the prefetch for all the cores, it's a 9bits mask (from bit 2 to bit 10), each bit correspond to 1 core
// 	// 					PI_CLUSTER_ICACHE_PREFETCH_ENABLE |
// 	// 					// Enable the icache for all the cores
// 	// 					PI_CLUSTER_ICACHE_ENABLE;
// 	pi_open_from_conf(&cluster_dev, &cl_conf);
// 	if (pi_cluster_open(&cluster_dev)){
// 		return -1;
// 	}

// 	// pi_cluster_task(&cluster_task, exec_cluster_stub, desc);
// 	pi_cluster_task(&cl_task, cluster_entry, NULL);

// 	pi_cluster_send_task_to_cl(&cluster_dev, &cl_task);

// 	// pi_cluster_send_task_to_cl(&cluster_dev, pi_cluster_task(&cl_task, cluster_entry, NULL));

// 	pi_cluster_close(&cluster_dev);

// 	return 0;
// }

// int main()
// {
// // Set voltage to 0.8 and frequency to 370 MHz
// 	// pi_pmu_voltage_set(PI_PMU_DOMAIN_CL, 800);
// 	// pi_freq_set(PI_FREQ_DOMAIN_FC, 370*1000*1000);
// 	// pi_freq_set(PI_FREQ_DOMAIN_CL, 370*1000*1000);
// 	// pi_freq_set(PI_FREQ_DOMAIN_PERIPH, 370*1000*1000);

//     int ret = test_entry();
//     pmsis_exit(ret);
// 	return 0;

// }


// void cluster_main()
// {

// 	pi_perf_conf(
// 	(1<<PI_PERF_CYCLES) | 
// 	(1<<PI_PERF_ACTIVE_CYCLES) | 
// 	(1<<PI_PERF_INSTR)  | 
// 	(1<<PI_PERF_LD_EXT) | 
// 	(1<<PI_PERF_TCDM_CONT) | 
// 	(1<<PI_PERF_LD_STALL) | 
// 	(1<<PI_PERF_IMISS) | 
// 	(1<<PI_PERF_LD_EXT_CYC) | 
// 	(1<<PI_PERF_ST_EXT_CYC) | 
// 	(1<<0x11) | 
// 	(1<<0x12) |
// 	(1<<0x13) | 
// 	(1<<0x14));
	
// 	// pi_perf_conf((1<<PI_PERF_CYCLES) | (1<<PI_PERF_ACTIVE_CYCLES));



// //////////////////////////////////////////////////////////////////////////////////////////////////////////
// //									 ASSIGN THE INITIAL VALUES HERE
// //////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	// pi_perf_reset();
// 	// pi_perf_start();
// 		llm_main();
// 	// pi_perf_stop();

//     printPerfCounters

// 	synch_barrier();
// }

void main_fn(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "Matrix Multiplication", .test = main_fn },
  {0, 0}
};

void main_fn(testresult_t *result, void (*start)(), void (*stop)()){

  llm_main(start, stop);

//   #ifdef CHECK
//   result->errors = check_result(matC);
//   #endif
};

int retval = 0;

int main()
{
  #ifdef FABRIC
      main_fn();
  #else
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);

  int nbErrors = run_suite(testcases);

  synch_barrier();
  #endif
  retval = nbErrors;

  return retval;
}

// void write_float_array_to_file(const char *filename, const char *arrname, const char *writemode, float *array, int size) {
//     FILE *fp = fopen(filename, writemode);
//     if (fp == NULL) {
//         perror("Failed to open float file");
//         return;
//     }
//     fprintf(fp, "float %s[] = {",arrname);
//     for (int i = 0; i < size-1; i++) {
//         fprintf(fp, "%f, ", array[i]);
//     }
//     fprintf(fp, "%f ", array[size-1]);
//     fprintf(fp, "};\n");
//     fclose(fp);
// }

// int check_result(const float* expected, const float* actual, int size, float tolerance) {
//     int error = 0;
//     for (int i = 0; i < size; i++) {
//         float diff = fabsf(expected[i] - actual[i]);
//         if (diff > tolerance) {
//             printf("Mismatch at index %d: expected = %f, actual = %f (diff = %f)\n",
//                    i, expected[i], actual[i], diff);
//             error++;
//         }
//     }
//     printf("TEST PASSED\n");

//     return error;
// }

float fast_exp(float x) {
    union {
        float f;
        uint32_t i;
    } result;

    // Constants derived by Schraudolph
    result.i = (uint32_t)(fast_exp_coef * x + fast_exp_bias);
    // result.i = (uint32_t)(12102203 * x + 1064866805);
    return result.f;
}

float fast_cosh(float x) {
    float ex  = fast_exp( x);
    float e_x = fast_exp(-x);
    return ((ex+e_x)/two);
}

float fast_tanh(float x) {
    float e2x  = fast_exp(two*x);
    return ((e2x-one)/(e2x+one));
}



// ----------------------------------------------------------------------------
// all the individual layers' forward and backward passes
// B = batch_size, T = sequence_length, C = channels, V = vocab_size

void encoder_forward(float* out,
                   int* inp, float* wte, float* wpe,
                   int B, int T, int C, int num_cores,int core_id) {


    int Chunk = C/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;

    // out is (B,T,C). At each position (b,t), a C-dimensional vector summarizing token & position
    // inp is (B,T) of integers, holding the token ids at each (b,t) position
    // wte is (V,C) of token embeddings, short for "weight token embeddings"
    // wpe is (maxT,C) of position embeddings, short for "weight positional embedding"
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            // seek to the output position in out[b,t,:]
            float* out_bt = out + b * T * C + t * C;
            // get the index of the token at inp[b, t]
            int ix = inp[b * T + t];
            // seek to the position in wte corresponding to the token
            float* wte_ix = wte + ix * C;
            // seek to the position in wpe corresponding to the position
            float* wpe_t = wpe + t * C;
            // add the two vectors and store the result in out[b,t,:]
            
            // for (int i = 0; i < C; i++) {
            //     out_bt[i] = wte_ix[i] + wpe_t[i];
            // }
            for (int i = start; i < end; i++) {
                out_bt[i] = wte_ix[i] + wpe_t[i];
                // out_bt[i] = wte_ix[i] * wpe_t[i];
            }            
        }
    }
}

void encoder_backward(float* dwte, float* dwpe,
                      float* dout, int* inp,
                      int B, int T, int C, int num_cores,int core_id) {


    int Chunk = C/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            float* dout_bt = dout + b * T * C + t * C;
            // int ix = inp[b * T + t];
            int ix = 0;
            float* dwte_ix = dwte + ix * C;
            float* dwpe_t = dwpe + t * C;
            // for (int i = 0; i < C; i++) {
            for (int i = start; i < end; i++) {
                float d = dout_bt[i];
                dwte_ix[i] += d;
                dwpe_t[i] += d;
            }
        }
    }
}

void layernorm_forward(float* out, float* mean, float* rstd,
                       float* inp, float* weight, float* bias,
                       int B, int T, int C, int num_cores,int core_id) {


    int Chunk = C/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    // reference: https://pytorch.org/docs/stable/generated/torch.nn.LayerNorm.html
    // both inp and out are (B,T,C) of the activations
    // mean and rstd are (B,T) buffers, to be used later in backward pass
    // at each position (b,t) of the input, the C-dimensional vector
    // of activations gets normalized, then scaled and shifted
    float eps = 1e-5f;
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            // seek to the input position inp[b,t,:]
            float* x = inp + b * T * C + t * C;
            
            // calculate the mean
            // float m = 0.0f;
            if(core_id == 0){
                for (int i = 0; i < num_cores; i++){
                    m[i]=zero;
                }
            }
            synch_barrier();

            // for (int i = 0; i < C; i++) {
            for (int i = start; i < end; i++) {
                // m += x[i];
                m[core_id] += x[i];
            }

            if(core_id == 0){
                for (int i = 1; i < num_cores; i++){
                    m[0]+=m[i];
                }
                m[0] = m[0]/C;
            }
            synch_barrier();
            // printf("m done\n");
            // m = m/C;

            // calculate the variance (without any bias correction)
            // float v = 0.0f;
            if(core_id == 0){
                for (int i = 0; i < num_cores; i++){
                    v[i]=zero;
                }
            }
            synch_barrier();
            // for (int i = 0; i < C; i++) {
            for (int i = start; i < end; i++) {
                // float xshift = x[i] - m;
                // v += xshift * xshift;
                float xshift = x[i] - m[0];
                v[core_id] += xshift * xshift;
            }
            if(core_id == 0){
                for (int i = 1; i < num_cores; i++){
                    v[0]+=v[i];
                }
                v[0] = v[0]/C;
            }
            synch_barrier();
            // printf("v done\n");                        
            // v = v/C;

            // calculate the rstd (reciprocal standard deviation)
            if(core_id==0){
                s = one / fSqrt(v[0] + eps);
                // s = one / sqrtf(v[0] + eps);
            }
            synch_barrier();            
            // printf("sqrt done\n");

            // float s = 1.0f / sqrtf(v[0] + eps);
            // printf("index = %d\t S = %f\n",b * T + t,s);
            // seek to the output position in out[b,t,:]
            float* out_bt = out + b * T * C + t * C;
            // for (int i = 0; i < C; i++) {
            // printf("start = %d\t end = %d\n",start,end);
            for (int i = start; i < end; i++) {
                // printf("i = %d\n",i);
                // float n = (s * (x[i] - m)); // normalize
                float n = (s * (x[i] - m[0])); // normalize
                float o = n * weight[i] + bias[i]; // scale and shift
                out_bt[i] = o; // write
            }
            // printf("first loop done\n");

            // cache the mean and rstd for the backward pass later
            if(core_id==0){
                // printf("mean[0] = %f\n",mean[0]);
                // printf("rstd[0] = %f\n",rstd[0]);
                mean[b * T + t] = m[0];
                rstd[b * T + t] = s;
            }
        }
    }
}

void layernorm_backward(float* dinp, float* dweight, float* dbias,
                        float* dout, float* inp, float* weight, float* mean, float* rstd,
                        int B, int T, int C, int num_cores,int core_id) {


    int Chunk = C/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {

            float* dout_bt = dout + b * T * C + t * C;
            float* inp_bt = inp + b * T * C + t * C;
            float* dinp_bt = dinp + b * T * C + t * C;
            float mean_bt = mean[b * T + t];
            float rstd_bt = rstd[b * T + t];

            // first: two reduce operations
            // float dnorm_mean = 0.0f;
            // float dnorm_norm_mean = 0.0f;


            if(core_id == 0){
                for (int i = 0; i < num_cores; i++){
                    dnorm_mean[i]=zero;
                    dnorm_norm_mean[i]=zero;
                }
            }
            synch_barrier();

            // for (int i = 0; i < C; i++) {
            for (int i = start; i < end; i++) {
                float norm_bti = (inp_bt[i] - mean_bt) * rstd_bt;
                float dnorm_i = weight[i] * dout_bt[i];
                // dnorm_mean += dnorm_i;
                // dnorm_norm_mean += dnorm_i * norm_bti;
                dnorm_mean[core_id] += dnorm_i;
                dnorm_norm_mean[core_id] += dnorm_i * norm_bti;
            }

            if(core_id == 0){
                for (int i = 1; i < num_cores; i++){
                    dnorm_mean[0]+=dnorm_mean[i];
                    dnorm_norm_mean[0]+=dnorm_norm_mean[i];
                }
                dnorm_mean[0] = dnorm_mean[0]/C;
                dnorm_norm_mean[0] = dnorm_norm_mean[0]/C;
            }
            synch_barrier();
            // dnorm_mean = dnorm_mean / C;
            // dnorm_norm_mean = dnorm_norm_mean / C;

            // now iterate again and accumulate all the gradients
            // for (int i = 0; i < C; i++) {
            for (int i = start; i < end; i++) {
                float norm_bti = (inp_bt[i] - mean_bt) * rstd_bt;
                float dnorm_i = weight[i] * dout_bt[i];
                // gradient contribution to bias
                dbias[i] += dout_bt[i];
                // gradient contribution to weight
                dweight[i] += norm_bti * dout_bt[i];
                // gradient contribution to input

                float dval = zero;
                // printf("1 dnorm_i = %f \t dnorm_mean = %f norm_bti = %f \t dnorm_norm_mean = %f \t rstd_bt = %f\n"
                    // ,dnorm_i,dnorm_mean,norm_bti,dnorm_norm_mean,rstd_bt);
                dval += dnorm_i; // term 1
                // dval -= dnorm_mean; // term 2
                // dval -= norm_bti * dnorm_norm_mean; // term 3
                dval -= dnorm_mean[0]; // term 2
                dval -= norm_bti * dnorm_norm_mean[0]; // term 3                
                dval *= rstd_bt; // final scale
                dinp_bt[i] += dval;
            }
        }
    }
}

void matmul_forward_naive(float* out,
                         const float* inp, const float* weight, const float* bias,
                         int B, int T, int C, int OC, int num_cores,int core_id) {


    int Chunk = C/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    // the most naive implementation of matrix multiplication
    // this serves as an algorithmic reference, and as a fallback for
    // unfriendly input shapes inside matmul_forward(), below.


    // for (int i = 0; i < OC; i++){
    //     for (int j = start; j < end; j++){
    //         weightT[j*OC+i] = weight[i*C+j];
    //     }
    // }    

    // matMul(inp, weightT, out, B*T, C, OC);

    matMul(inp, weight, out, B*T, C, OC);


    Chunk = OC/num_cores; 
    start = core_id*Chunk;
    end = start+Chunk;
    
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            int bt = b * T + t;
            for (int o = start; o < end; o++) {
                out[bt * OC + o] = out[bt * OC + o] + bias[o];
            }
        }
    }
    // synch_barrier(0);

}

void matmul_backward(float* dinp, float* dweight, float* dbias,
                    const float* dout, const float* inp, const float* weight,
                    int B, int T, int C, int OC, int num_cores,int core_id) {


    int Chunk = OC/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    // most of the running time is spent here and in matmul_forward
    // this backward could be done in a single "round" of loops
    // but that doesn't afford an efficient parallelization strategy

    matMul(dout, weight, dinp, B*T, OC, C);
    
    for (int i = 0; i < B*T; i++){
        for (int j = start; j < end; j++){
            // printf("index = %d \t T index = %d\n",i*OC+j,j*(B*T)+i);
            doutT[j*(B*T)+i] = dout[i*OC+j];
            // dout[j*(B*T)+i] = dout[i*OC+j];
        }
    }

    matMul(doutT, inp, dweight, OC, B*T, C);
    // matMul(dout, inp, dweight, OC, B*T, C);

    for (int o = start; o < end; o++) {
        for (int b = 0; b < B; b++) {
            for (int t = 0; t < T; t++) {
                const float* dout_bt = dout + b * T * OC + t * OC;
                dbias[o] += dout_bt[o];
            }
        }
    }
}

void attention_forward(float* out, float* preatt, float* att,
                       float* inp,
                       int B, int T, int C, int NH, int num_cores,int core_id) {
    // input is (B, T, 3C) holding the query, key, value (Q, K, V) vectors
    // preatt, att are (B, NH, T, T). NH = number of heads, T = sequence length
    // that holds the pre-attention and post-attention scores (used in backward)
    // output is (B, T, C)
    // attention is the only layer that mixes information across time
    // every other operation is applied at every (b,t) position independently
    // (and of course, no layer mixes information across batch)
    int C3 = C*3;
    int hs = C / NH; // head size
    float scale = one / sqrtf(hs);
    // float scale = 1.0 / hs;


    int Chunk_hs = hs/num_cores; 
    int start_hs = core_id*Chunk_hs;
    int end_hs   = start_hs+Chunk_hs;

    int Chunk_T = T/num_cores; 
    int start_T = core_id*Chunk_T;
    int end_T   = start_T+Chunk_T;


    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            int Chunk_t;
            int start_t;
            int end_t;
            if(t < 8){
                Chunk_t = ((t+1)+num_cores-1) / num_cores;
                start_t = core_id*Chunk_t;
                end_t   = start_t + Chunk_t < (t+1)? start_t + Chunk_t : (t+1);
            }else{
                Chunk_t = (t+1)/num_cores; 
                start_t = core_id*Chunk_t;
                if(core_id == 7){
                    end_t = t+1;
                }else{
                    end_t   = start_t+Chunk_t;
                }
            }
            for (int h = 0; h < NH; h++) {
                float* query_t = inp + b * T * C3 + t * C3 + h * hs;
                float* preatt_bth = preatt + b*NH*T*T + h*T*T + t*T;
                float* att_bth = att + b*NH*T*T + h*T*T + t*T;

                // pass 1: calculate query dot key and maxval
                maxval = maxval_init; // TODO something better
                for (int t2 = 0; t2 <= t; t2++) {
                    float* key_t2 = inp + b * T * C3 + t2 * C3 + h * hs + C; // +C because it's key

                    // (query_t) dot (key_t2)

                    // float val = 0.0f;
                    if(core_id == 0){
                        for (int i = 0; i < num_cores; i++){
                            val[i]=zero;
                        }
                    }
                    synch_barrier();

                    // for (int i = 0; i < hs; i++) {
                    // for (int k = 0; k < 4; k++){
                        for (int i = start_hs; i < end_hs; i++) {
                            val[core_id] += query_t[i] * key_t2[i];
                        }
                    // }
                    

                    // printf("t2 = %d \t val = %f\n",t2,val);

                    if(core_id == 0){
                        for (int i = 1; i < num_cores; i++){
                            val[0]+=val[i];
                        }
                        val[0] *= scale;
                        if (val[0] > maxval) {
                            maxval = val[0];
                        }

                        preatt_bth[t2] = val[0];
                    }
                    synch_barrier();
                    // printf("maxval = %f\n",maxval);
                    // val *= scale;
                    // if (val > maxval) {
                    //     maxval = val;
                    // }
                    // preatt_bth[t2] = val;
                    // printf("preatt_bth[%d] = %f\n",b*NH*T*T + h*T*T + t*T + t2,preatt_bth[t2]);

                }
                // pass 2: calculate the exp and keep track of sum
                // maxval is being calculated and subtracted only for numerical stability
                // float expsum = 0.0f;

                if(core_id == 0){
                    for (int i = 0; i < num_cores; i++){
                        expsum[i]=zero;
                    }
                }
                synch_barrier();                

                // for (int t2 = 0; t2 <= t; t2++) {
                for (int t2 = start_t; t2 < end_t; t2++) {
                    // float expv = expf(preatt_bth[t2] - maxval);//I CHANGED THIS PART
                    float expv = fast_exp(preatt_bth[t2] - maxval);//I CHANGED THIS PART
                    // printf("preatt_bth[t2] - maxval = %f\n",preatt_bth[t2] - maxval);
                    // printf("expv = %f\n",expv);
                    // float expv = preatt_bth[t2] - maxval;
                    expsum[core_id] += expv;
                    att_bth[t2] = expv;
                }
                synch_barrier();                

                if(core_id == 0){
                    for (int i = 1; i < num_cores; i++){
                        expsum[0]+=expsum[i];
                    }
                    expsum_inv = expsum[0] == zero ? zero : one / expsum[0];
                    // printf("expsum_inv = %f\n",expsum_inv);
                }
                synch_barrier();
                

                // float expsum_inv = expsum == 0.0f ? 0.0f : 1.0f / expsum;

                // pass 3: normalize to get the softmax

                // for (int t2 = 0; t2 < T; t2++) {
                for (int t2 = start_T; t2 < end_T; t2++) {
                    if (t2 <= t) {
                        att_bth[t2] *= expsum_inv;
                    } else {
                        // causal attention mask. not strictly necessary to set to zero here
                        // only doing this explicitly for debugging and checking to PyTorch
                        att_bth[t2] = zero;
                    }
                }

                // pass 4: accumulate weighted values into the output of attention
                float* out_bth = out + b * T * C + t * C + h * hs;
                // for (int i = 0; i < hs; i++) { out_bth[i] = 0.0f; }
                // for (int k = 0; k < 4; k++){
                    for (int i = start_hs; i < end_hs; i++) { out_bth[i] = zero; }
                // }
                for (int t2 = 0; t2 <= t; t2++) {
                    float* value_t2 = inp + b * T * C3 + t2 * C3 + h * hs + C*2; // +C*2 because it's value
                    float att_btht2 = att_bth[t2];
                    // for (int i = 0; i < hs; i++) {
                    // for (int k = 0; k < 4; k++){                    
                        for (int i = start_hs; i < end_hs; i++) {
                            out_bth[i] += att_btht2 * value_t2[i];
                        }
                    // }
                }
            }
        }
    }
}

void attention_backward(float* dinp, float* dpreatt, float* datt,
                        float* dout, float* inp, float* att,
                        int B, int T, int C, int NH, int num_cores,int core_id) {
    // inp/dinp are (B, T, 3C) Q,K,V
    // att/datt/dpreatt are (B, NH, T, T)
    // dout is (B, T, C)
    int C3 = C*3;
    int hs = C / NH; // head size
    float scale = one / sqrtf(hs);//I CHANGED THIS PART

    int Chunk_hs = hs/num_cores; 
    int start_hs = core_id*Chunk_hs;
    int end_hs   = start_hs+Chunk_hs;



    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            int Chunk_t;
            int start_t;
            int end_t;
            if(t < 8){
                Chunk_t = ((t+1)+num_cores-1) / num_cores;
                start_t = core_id*Chunk_t;
                end_t   = start_t + Chunk_t < (t+1)? start_t + Chunk_t : (t+1);
            }else{
                Chunk_t = (t+1)/num_cores; 
                start_t = core_id*Chunk_t;
                if(core_id == 7){
                    end_t = t+1;
                }else{
                    end_t   = start_t+Chunk_t;
                }
            }
            for (int h = 0; h < NH; h++) {
                float* att_bth = att + b*NH*T*T + h*T*T + t*T;
                float* datt_bth = datt + b*NH*T*T + h*T*T + t*T;
                float* dpreatt_bth = dpreatt + b*NH*T*T + h*T*T + t*T;
                float* dquery_t = dinp + b * T * C3 + t * C3 + h * hs;
                float* query_t = inp + b * T * C3 + t * C3 + h * hs;

                // backward pass 4, through the value accumulation
                float* dout_bth = dout + b * T * C + t * C + h * hs;
                for (int t2 = 0; t2 <= t; t2++) {
                    float* value_t2 = inp + b * T * C3 + t2 * C3 + h * hs + C*2; // +C*2 because it's value
                    float* dvalue_t2 = dinp + b * T * C3 + t2 * C3 + h * hs + C*2;
                    
                    if(core_id == 0){
                        temp[0] = datt_bth[t2];
                        for (int i = 1; i < num_cores; i++){
                            temp[i]=zero;
                        }
                    }
                    synch_barrier();                

                    for (int k = 0; k < 4; k++){                    
                        for (int i = start_hs; i < end_hs; i++) {
                            // in the forward pass this was:
                            // out_bth[i] += att_bth[t2] * value_t2[i];
                            // so now we have:
                            // datt_bth[t2] += value_t2[i] * dout_bth[i];
                            temp[core_id] += value_t2[i] * dout_bth[i];
                            dvalue_t2[i] += att_bth[t2] * dout_bth[i];
                        }
                    }


                    if(core_id == 0){
                        for (int i = 1; i < num_cores; i++){
                            temp[0]+=temp[i];
                        }
                        datt_bth[t2] = temp[0];
                    }
                    synch_barrier();
                }
                
                // backward pass 2 & 3, the softmax
                // note that softmax (like e.g. tanh) doesn't need the input (preatt) to backward
                for (int t2 = 0; t2 <= t; t2++) {
                    for (int t3 = start_t; t3 < end_t; t3++) {
                        float indicator = t2 == t3 ? one : zero;
                        float local_derivative = att_bth[t2] * (indicator - att_bth[t3]);
                        dpreatt_bth[t3] += local_derivative * datt_bth[t2];
                    }
                    synch_barrier();

                }

                // backward pass 1, the query @ key matmul
                for (int t2 = 0; t2 <= t; t2++) {
                    float* key_t2 = inp + b * T * C3 + t2 * C3 + h * hs + C; // +C because it's key
                    float* dkey_t2 = dinp + b * T * C3 + t2 * C3 + h * hs + C; // +C because it's key
                    for (int k = 0; k < 4; k++){                    
                        for (int i = start_hs; i < end_hs; i++) {
                            // in the forward pass this was:
                            // preatt_bth[t2] += (query_t[i] * key_t2[i]) * scale;
                            // so now we have:
                            dquery_t[i] += key_t2[i]  * dpreatt_bth[t2] * scale;
                            dkey_t2[i]  += query_t[i] * dpreatt_bth[t2] * scale;
                        }
                    }
                }
            }
        }
    }
}

// #define GELU_SCALING_FACTOR sqrtf(2.0f / M_PI)//I CHANGED THIS LINE
// #define GELU_SCALING_FACTOR 0.797884561
void gelu_forward(float* out, float* inp, int N, int num_cores,int core_id) {


    int Chunk = N/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;

    // (approximate) GeLU elementwise non-linearity in the MLP block of Transformer
    for (int i = start; i < end; i++) {
        float x = inp[i];
        float cube = gelu_const * x * x * x;
        // printf("x + cube[%d] = %f\n",i,x + cube);
        // printf("bigger[%d] = %f\n",i,1.0f + GELU_SCALING_FACTOR * (x + cube));
        // out[i] = 0.5f * x * (1.0f + tanhf(GELU_SCALING_FACTOR * (x + cube)));        
        out[i] = half * x * (one + fast_tanh(GELU_SCALING_FACTOR * (x + cube)));
        // out[i] = 0.5f * x * (1.0f + (GELU_SCALING_FACTOR * (x + cube)));//I CHANGED THIS LINE
    }
}

void gelu_backward(float* dinp, float* inp, float* dout, int N, int num_cores,int core_id) {


    int Chunk = N/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
 
    for (int i = start; i < end; i++) {
        float x = inp[i];
        float cube = gelu_const * x * x * x;
        float tanh_arg = GELU_SCALING_FACTOR * (x + cube);
        // float tanh_out = tanhf(tanh_arg);//I CHANGED THIS LINE
        // float coshf_out = coshf(tanh_arg);//I CHANGED THIS LINE
        float tanh_out = fast_tanh(tanh_arg);//I CHANGED THIS LINE
        float coshf_out = fast_cosh(tanh_arg);//I CHANGED THIS LINE        
        float sech_out = one / (coshf_out * coshf_out);
        float local_grad = half * (one + tanh_out) + x * half * sech_out * GELU_SCALING_FACTOR * (one + three * gelu_const * x * x);
        dinp[i] += local_grad * dout[i];
    }
}

void residual_forward(float* out, float* inp1, float* inp2, int N, int num_cores,int core_id) {


    int Chunk = N/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    for (int i = start; i < end; i++) {
        out[i] = inp1[i] + inp2[i];
    }
}

void residual_backward(float* dinp1, float* dinp2, float* dout, int N, int num_cores,int core_id) {


    int Chunk = N/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    for (int i = start; i < end; i++) {
        dinp1[i] += dout[i];
        dinp2[i] += dout[i];
    }
}

void softmax_forward(float* probs, float* logits, int B, int T, int V, int Vp, int num_cores,int core_id) {


    int Chunk = V/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    // output: probs are (B,T,Vp) of the probabilities (sums to 1.0 in each b,t position)
    // input: logits is (B,T,Vp) of the unnormalized log probabilities
    // Vp is the padded vocab size (for efficiency), V is the "real" vocab size
    // example: Vp is 50304 and V is 50257
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            // probs <- softmax(logits)
            float* logits_bt = logits + b * T * Vp + t * Vp;
            float* probs_bt = probs + b * T * Vp + t * Vp;

            // maxval is only calculated and subtracted for numerical stability
            // float maxval = -10000.0f; // TODO something better
            if(core_id == 0){
                for (int i = 0; i < num_cores; i++){
                    temp[i]=maxval_init;
                }
            }
            synch_barrier();

            for (int i = start; i < end; i++) {
                if (logits_bt[i] > temp[core_id]) {
                    temp[core_id] = logits_bt[i];
                }
            }

            if(core_id == 0){
                for (int i = 1; i < num_cores; i++){
                    if(temp[0] < temp[i])
                    temp[0] = temp[i];
                }
                temp[0];
            }
            synch_barrier();



            // float sum = 0.0f;
            if(core_id == 0){
                for (int i = 0; i < num_cores; i++){
                    sum[i]=zero;
                }
            }
            synch_barrier();
            for (int i = start; i < end; i++) {
                // probs_bt[i] = expf(logits_bt[i] - maxval);//I CHANGED THIS LINE 
                // probs_bt[i] = fast_exp(logits_bt[i] - maxval);//I CHANGED THIS LINE 
                probs_bt[i] = fast_exp(logits_bt[i] - temp[0]);//I CHANGED THIS LINE 
                // probs_bt[i] = logits_bt[i] - maxval; 
                sum[core_id] += probs_bt[i];
            }

            if(core_id == 0){
                for (int i = 1; i < num_cores; i++){
                    sum[0]+=sum[i];
                }
            }
            synch_barrier();
                        
            // note we only loop to V, leaving the padded dimensions
            for (int i = start; i < end; i++) {
                probs_bt[i] /= sum[0];
            }
            // for extra super safety we may wish to include this too,
            // forcing the probabilities here to be zero, but it shouldn't matter
            synch_barrier();

            if(core_id==0){
                for (int i = V; i < Vp; i++) {
                    probs_bt[i] = 0.0f;
                }
            }
            synch_barrier();

        }
    }
}

void crossentropy_forward(float* losses,
                          float* probs, int* targets,
                          int B, int T, int Vp, int num_cores,int core_id) {


    int Chunk = T/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    // output: losses is (B,T) of the individual losses at each position
    // input: probs are (B,T,Vp) of the probabilities
    // input: targets is (B,T) of integers giving the correct index in logits
    for (int b = 0; b < B; b++) {
        for (int t = start; t < end; t++) {
            // loss = -log(probs[target])
            float* probs_bt = probs + b * T * Vp + t * Vp;
            int ix = targets[b * T + t];
            losses[b * T + t] = -logf(probs_bt[ix]);
        }
    }
}

void crossentropy_softmax_backward(float* dlogits,
                           float* dlosses, float* probs, int* targets,
                           int B, int T, int V, int Vp, int num_cores,int core_id) {
    int Chunk = V/num_cores; 
    int start = core_id*Chunk;
    int end = start+Chunk;
    // backwards through both softmax and crossentropy
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            float* dlogits_bt = dlogits + b * T * Vp + t * Vp;
            float* probs_bt = probs + b * T * Vp + t * Vp;
            float dloss = dlosses[b * T + t];
            int ix = targets[b * T + t];
            // note we only loop to V, leaving the padded dimensions
            // of dlogits untouched, so gradient there stays at zero
            for (int i = start; i < end; i++) {
                float p = probs_bt[i];
                float indicator = i == ix ? 1.0f : 0.0f;
                dlogits_bt[i] += (p - indicator) * dloss;
            }
        }
    }
}
    
    float* inp     ;
    float* dinp    ;
    float* dweight ;
    float* weight  ;
    float* dbias   ;
    float* dout    ;
    float* doutT   ;


void llm_main(void (*start)(), void (*stop)()){
    int core_id = get_core_id();
	
    #if NUM_CORES > 1
	synch_barrier();
	BarrierCounter
	#endif

    int B = B_Size;
    int C = C_Size;
    int T = T_Size;

    //--------------------------------------------------------- encoder_forward
    // float *out;
    // float *wte;
    // float *wpe;
    // 1-1-768
    // if(core_id == 0){
    //     out  = (float*)pi_l1_malloc(0 , B * T * C * sizeof(float));
    //     wte  = (float*)pi_l1_malloc(0 , B * T * C * sizeof(float));
    //     wpe  = (float*)pi_l1_malloc(0 , B * T * C * sizeof(float));
    //     memcpy(wte, data1, B * T * C * sizeof(float));
    //     memcpy(wpe, data1, B * T * C * sizeof(float));
    // }
	// synch_barrier();
    // // printf("CORE START\n");
    // start();
    // // for (int i = 0; i < 4*64; i++){
    // for (int i = 0; i < 1; i++){
    //     encoder_forward(out, inp, wte, wpe, B, T, C,NUM_CORES,core_id);
    // }
    // stop();
	// synch_barrier();
    // // encoder_forward(out, inp, wte, wpe, B, T, C,NUM_CORES,core_id);
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     // check_result(out,outG,B * T * C,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "outG", "w", out, B*T*C);
    // ---------------------------------------------------------

    //--------------------------------------------------------- encoder_backward
    // float* dwte;
    // float* dwpe;
    // float* dout;
    // 1-1-768
    // if(core_id == 0){
    //     dwte = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    //     dwpe = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    //     dout = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    //     memcpy(dwte, data1, B * T * C * sizeof(float));
    //     memcpy(dwpe, data1, B * T * C * sizeof(float));
    //     memcpy(dout, data1, B * T * C * sizeof(float));
    // }
	// synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 4*64; i++)
    // for (int i = 0; i < 1; i++)
    // {
    //     encoder_backward(dwte, dwpe, dout, inp, B, T, C,NUM_CORES,core_id);
    // }
    // stop();
	// synch_barrier();
    // pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(dwte,dwteG,B * T * C,THRESHOLD);
    //     check_result(dwpe,dwpeG,B * T * C,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "dwteG", "w", dwte, B*T*C);
    // write_float_array_to_file("gold_temp.h", "dwpeG", "a", dwpe, B*T*C);
    //---------------------------------------------------------

    //--------------------------------------------------------- layernorm_forward
    // float* inp ;
    // float* mean;
    // float* rstd;
    // float* weight;
    // float* bias;
    // float* out ;
    // 1-1-768
    // if(core_id == 0){
    // inp    = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    // mean   = (float*)pi_l1_malloc(0, B * T * 1 * sizeof(float));
    // rstd   = (float*)pi_l1_malloc(0, B * T * 1 * sizeof(float));
    // weight = (float*)pi_l1_malloc(0, 1 * 1 * C * sizeof(float));
    // bias   = (float*)pi_l1_malloc(0, 1 * 1 * C * sizeof(float));
    // out    = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    // memcpy(inp   , data1, B * T * C * sizeof(float));
    // memcpy(weight, data1, 1 * 1 * C * sizeof(float));
    // memcpy(bias  , data1, 1 * 1 * C * sizeof(float));
    // memcpy(mean  , data1, B * T * 1 * sizeof(float));
    // memcpy(rstd  , data1, B * T * 1 * sizeof(float));
    // }
	// synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 64*4; i++){
    // for (int i = 0; i < 1; i++){
    //     layernorm_forward(out, mean, rstd, inp, weight, bias, B, T, C,NUM_CORES,core_id);
    // }
    // stop();    
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(mean,meanG,B*T*1,THRESHOLD);
    //     check_result(rstd,rstdG,B*T*1,THRESHOLD);
    //     check_result(out ,outG ,B*T*C,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "meanG", "w", mean, B*T*1);
    // write_float_array_to_file("gold_temp.h", "rstdG", "a", rstd, B*T*1);
    // write_float_array_to_file("gold_temp.h", "outG" , "a", out , B*T*C);

    //--------------------------------------------------------- layernorm_backward
    // float* inp    ;
    // float* dinp   ;
    // float* mean   ;
    // float* rstd   ;
    // float* dweight;
    // float* weight ;
    // float* dbias  ;
    // float* dout   ;
    // 1-1-768
    // if(core_id == 0){
    // inp    = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    // dinp   = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    // rstd   = (float*)pi_l1_malloc(0, B * T * 1 * sizeof(float));
    // mean   = (float*)pi_l1_malloc(0, B * T * 1 * sizeof(float));
    // dweight= (float*)pi_l1_malloc(0, 1 * 1 * C * sizeof(float));
    // weight = (float*)pi_l1_malloc(0, 1 * 1 * C * sizeof(float));
    // dbias  = (float*)pi_l1_malloc(0, 1 * 1 * C * sizeof(float));
    // dout   = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    // memcpy(rstd   , data1, B * T * 1 * sizeof(float));
    // memcpy(inp    , data1, B * T * C * sizeof(float));
    // memcpy(dinp   , data1, B * T * C * sizeof(float));
    // memcpy(dweight, data1, 1 * 1 * C * sizeof(float));
    // memcpy(weight , data1, 1 * 1 * C * sizeof(float));
    // memcpy(dbias  , data1, 1 * 1 * C * sizeof(float));
    // memcpy(mean   , data1, B * T * 1 * sizeof(float));
    // memcpy(dout   , data1, B * T * C * sizeof(float));
    // }
    // synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 64*4; i++){
    // for (int i = 0; i < 1; i++){
    //     layernorm_backward(dinp, dweight, dbias, dout, inp, weight, mean, rstd, B, T, C, NUM_CORES, core_id);
    // }    
    // stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(dbias  ,dbiasG  ,1*1*C,THRESHOLD);
    //     check_result(dweight,dweightG,1*1*C,THRESHOLD);
    //     check_result(dinp   ,dinpG   ,B*T*C,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif
    // write_float_array_to_file("gold_temp.h", "dbiasG"  , "w", dbias  , 1*1*C);
    // write_float_array_to_file("gold_temp.h", "dweightG", "a", dweight, 1*1*C);
    // write_float_array_to_file("gold_temp.h", "dinpG"   , "a", dinp   , B*T*C);

    //--------------------------------------------------------- matmul_forward_naive
    // int OC = C;
    // float* inp    ;
    // float* weight ;
    // float* bias   ;
    // float* out    ;
    // // // 1-64-64 OC=64
    // if(core_id == 0){
    // inp    = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    // weight = (float*)pi_l1_malloc(0, 1 * OC* C * sizeof(float));
    // // weightT= (float*)pi_l1_malloc(0, 1 * OC* C * sizeof(float));
    // bias   = (float*)pi_l1_malloc(0, 1 * 1 * OC* sizeof(float));
    // out    = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    // memcpy(inp    , data1, B * T * C * sizeof(float));
    // memcpy(weight , data1, 1 * OC* C * sizeof(float));
    // memcpy(bias   , data1, 1 * 1 * OC* sizeof(float));
    // memcpy(out    , data1, B * T * C * sizeof(float));
    // }
	// synch_barrier();
    // start();
    // for (int i = 0; i < 1; i++){
    //     matmul_forward_naive(out, inp, weight, bias, B, T, C, OC,NUM_CORES, core_id);
    //     synch_barrier();
    // }
    // stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(out  ,outG  ,B*T*C,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "outG"  , "w", out  , B*T*C);

    //--------------------------------------------------------- matmul_backward
    int OC = C;
    // float* inp     ;
    // float* dinp    ;
    // float* dweight ;
    // float* weight  ;
    // float* dbias   ;
    // float* dout    ;
    // float* doutT   ;
    if(core_id == 0){
    inp     = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    dinp    = (float*)pi_l1_malloc(0, B * T * C * sizeof(float));
    dweight = (float*)pi_l1_malloc(0, 1 * OC* C * sizeof(float));
    weight  = (float*)pi_l1_malloc(0, 1 * OC* C * sizeof(float));
    dbias   = (float*)pi_l1_malloc(0, 1 * 1 * OC* sizeof(float));
    dout    = (float*)pi_l1_malloc(0, B * T * OC* sizeof(float));
    doutT   = (float*)pi_l1_malloc(0, B * T * OC* sizeof(float));
    memcpy(inp    , data1, B * T * C * sizeof(float));
    memcpy(dinp   , dataz, B * T * C * sizeof(float));
    memcpy(dweight, dataz, 1 * OC* C * sizeof(float));
    memcpy(weight , data1, 1 * OC* C * sizeof(float));
    memcpy(dbias  , data1, 1 * 1 * OC* sizeof(float));
    memcpy(dout   , data1, B * T * C * sizeof(float));
    }
	synch_barrier();
    start();
    for (int i = 0; i < 1; i++){
        matmul_backward(dinp, dweight, dbias, dout, inp, weight, B, T, C, OC, NUM_CORES, core_id);
    }
    stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(dinp    ,dinpG    ,B*T*C,THRESHOLD);
    //     check_result(dweight ,dweightG ,OC*C ,THRESHOLD);
    //     check_result(dbias   ,dbiasG   ,OC   ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "dinpG"     , "w", dinp      , B*T*C);
    // write_float_array_to_file("gold_temp.h", "dweightG"  , "a", dweight   , OC*C);
    // write_float_array_to_file("gold_temp.h", "dbiasG"    , "a", dbias     , OC);

    //--------------------------------------------------------- attention_forward
    // int NH = 2;
    // T = T/2;
    // int NH=1;
    // float* inp     ;
    // float* preatt  ;
    // float* att     ;
    // float* out     ;
    //1-64-16 NH=1
    // if(core_id == 0){
    // inp     = (float*)pi_l1_malloc(0, B * T  * 3*C   * sizeof(float));
    // preatt  = (float*)pi_l1_malloc(0, B * NH * T * T * sizeof(float));
    // att     = (float*)pi_l1_malloc(0, B * NH * T * T * sizeof(float));
    // out     = (float*)pi_l1_malloc(0, B * T  * C     * sizeof(float));
    // for (int i = 0; i < 3; i++){
    //     memcpy(inp    + i*(B * T * C)    , data1, B * T  * C    * sizeof(float));
    // }
    // for (int i = 0; i < 1; i++){
    //     memcpy(preatt + i*(B * NH * T * T)    , data1, B * NH * T * T    * sizeof(float));
    // }
    // for (int i = 0; i < 1; i++){
    //     memcpy(att    + i*(B * NH * T * T)    , data1, B * NH * T * T    * sizeof(float));
    // }
    // }
	// synch_barrier();
	// BarrierCounter
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 4*12; i++){//B-NH C is 16 but it is upscaled to 64 ini the function by some loops
    // for (int i = 0; i < 1; i++){//B-NH C is 16 but it is upscaled to 64 ini the function by some loops
    //     attention_forward(out, preatt, att, inp, B, T, C, NH, NUM_CORES, core_id);
    // }
    // stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(out    ,outG    ,B*T*C    ,THRESHOLD);
    //     check_result(preatt ,preattG ,B*NH*T*T ,THRESHOLD);
    //     check_result(att    ,attG    ,B*NH*T*T ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "outG"     , "w", out      , B*T*C);
    // write_float_array_to_file("gold_temp.h", "preattG"  , "a", preatt   , B*NH*T*T);
    // write_float_array_to_file("gold_temp.h", "attG"     , "a", att      , B*NH*T*T);

    //--------------------------------------------------------- attention_forward v2
    // #include "gold_temp.h"
    // int NH = 2;
    // T = T/2;
    // float* inp     = (float*)malloc(B * T  * 3*C   * sizeof(float));
    // float* key     = (float*)malloc(B * T  *   C   * sizeof(float));//CHANGE THE SIZE
    // float* query   = (float*)malloc(B * T  *   C   * sizeof(float));//CHANGE THE SIZE
    // float* value   = (float*)malloc(B * T  *   C   * sizeof(float));//CHANGE THE SIZE
    // float* preatt  = (float*)malloc(B * NH * T * T * sizeof(float));
    // float* att     = (float*)malloc(B * NH * T * T * sizeof(float));
    // float* temp    = (float*)malloc(B * NH * T * T * sizeof(float));
    // float* out     = (float*)malloc(B * T  * C     * sizeof(float));
    // for (int i = 0; i < 3; i++){
    //     memcpy(inp    + i*(B * T * C)    , data1, B * T  * C    * sizeof(float));
    // }
    // for (int i = 0; i < 1; i++){
    //     memcpy(preatt + i*(B * NH * T * T)    , data1, B * NH * T * T    * sizeof(float));
    // }
    // for (int i = 0; i < 1; i++){
    //     memcpy(att    + i*(B * NH * T * T)    , data1, B * NH * T * T    * sizeof(float));
    // }
    // attention_forward_v2(out, preatt, att, inp, temp, key, query, value, B, T, C, NH);
    // // write_float_array_to_file("gold_temp.h", "outG"     , "w", out      , B*T*C);
    // // write_float_array_to_file("gold_temp.h", "preattG"  , "a", preatt   , B*NH*T*T);
    // // write_float_array_to_file("gold_temp.h", "attG"     , "a", att      , B*NH*T*T);
    // // printf("CHECK PREATT\n");
    // // check_result(preattG, preatt, B * NH * T * T, 0.00001f);
    // printf("CHECK ATT\n");
    // check_result(attG   , att   , B * NH * T * T, 0.00001f);
    // printf("CHECK OUT\n");
    // check_result(outG   , out   , B * T * C, 0.00001f);

    //--------------------------------------------------------- attention_backward
    // int NH = 1;
    // // T = T/2;
    // // float* inp     ;
    // // float* dinp    ;
    // // float* dpreatt ;
    // // float* att     ;
    // // float* datt    ;
    // // float* dout    ;
    // //1-64-16 NH=1
    // if(core_id == 0){
    //     inp     = (float*)pi_l1_malloc(0, B * T  * 3*C   * sizeof(float));
    //     dinp    = (float*)pi_l1_malloc(0, B * T  * 3*C   * sizeof(float));
    //     dpreatt = (float*)pi_l1_malloc(0, B * NH * T * T * sizeof(float));
    //     att     = (float*)pi_l1_malloc(0, B * NH * T * T * sizeof(float));
    //     datt    = (float*)pi_l1_malloc(0, B * NH * T * T * sizeof(float));
    //     dout    = (float*)pi_l1_malloc(0, B * T  * C     * sizeof(float));
    //     for (int i = 0; i < 3; i++){
    //         memcpy(inp    + i*(B * T * C)    , data1, B * T  * C        * sizeof(float));
    //         memcpy(dinp   + i*(B * T * C)    , data1, B * T  * C        * sizeof(float));
    //     }
    //     memcpy(dpreatt                       , data1, B * NH * T * T    * sizeof(float));
    //     memcpy(att                           , data1, B * NH * T * T    * sizeof(float));
    //     memcpy(datt                          , data1, B * NH * T * T    * sizeof(float));
    //     memcpy(dout                          , data1, B * T * C         * sizeof(float));
    // }
    // synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 4*12; i++){//B-NH C is 16 but it is upscaled to 64 ini the function by some loops
    // for (int i = 0; i < 1; i++){//B-NH C is 16 but it is upscaled to 64 ini the function by some loops
    //     attention_backward(dinp, dpreatt, datt, dout, inp, att, B, T, C, NH, NUM_CORES, core_id);
    // }
    // stop();
    // pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(datt    ,dattG    ,B*NH*T*T ,THRESHOLD);
    //     check_result(dpreatt ,dpreattG ,B*NH*T*T ,THRESHOLD);
    //     check_result(dinp    ,dinpG    ,B*T*3*C  ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "dattG"     , "w", datt      , B*NH*T*T);
    // write_float_array_to_file("gold_temp.h", "dpreattG"  , "a", dpreatt   , B*NH*T*T);
    // write_float_array_to_file("gold_temp.h", "dinpG"     , "a", dinp      , B*T*3*C );

    //--------------------------------------------------------- gelu_forward
    // int N = B*T*C;
    // // float* inp;
    // // float* out;
    // // //4096
    // if(core_id == 0){
    //     inp     = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     out     = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     memcpy(inp , data1, B * T * C * sizeof(float));
    // }
	// synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 192; i++){
    // for (int i = 0; i < 1; i++){
    //     gelu_forward(out, inp, N, NUM_CORES, core_id);
    // }
    // stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(out    ,outG    ,B*T*C  ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "outG"     , "w", out      , B*T*C);

    //--------------------------------------------------------- gelu_backward
    // int N = B*T*C;
    // // float* inp     ;
    // // float* dinp    ;
    // // float* dout    ;
    // // //4096
    // if(core_id == 0){
    //     inp     = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     dinp    = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     dout    = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     memcpy(inp  , data1, B * T * C * sizeof(float));
    //     memcpy(dinp , data1, B * T * C * sizeof(float));
    //     memcpy(dout , data1, B * T * C * sizeof(float));
    // }
    // synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 192; i++){
    // for (int i = 0; i < 1; i++){
    //     gelu_backward(dinp, inp, dout, N, NUM_CORES, core_id);
    // }
    // stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(dinp    ,dinpG    ,B*T*C  ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "dinpG"     , "w", dinp      , B*T*C);

    //--------------------------------------------------------- residual_forward
    // int N = B*T*C;
    // float* inp1     ;
    // float* inp2     ;
    // float* out      ;
    // 4096
    // if(core_id == 0){
    //     inp1     = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     inp2     = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     out      = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     memcpy(inp1  , data1, B * T * C * sizeof(float));
    //     memcpy(inp2  , data1, B * T * C * sizeof(float));
    // }
    // synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 48; i++){
    // for (int i = 0; i < 1; i++){
    //     residual_forward(out, inp1, inp2, N, NUM_CORES, core_id);
    // }
    // stop();    
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(out    ,outG    ,B*T*C  ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif    
    // write_float_array_to_file("gold_temp.h", "outG"     , "w", out      , B*T*C);

    //--------------------------------------------------------- residual_backward
    // int N = B*T*C;
    // // float* inp;
    // // float* dinp;
    // // float* dout;
    // // 4096
    // if(core_id == 0){
    //     inp     = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     dinp    = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     dout    = (float*)pi_l1_malloc(0, B * T  * C   * sizeof(float));
    //     memcpy(inp    , data1, B * T * C * sizeof(float));
    //     memcpy(dinp   , data1, B * T * C * sizeof(float));
    //     memcpy(dout   , data1, B * T * C * sizeof(float));
    // }
	// synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 48; i++){
    // for (int i = 0; i < 1; i++){
    //     residual_backward(inp, dinp, dout, N, NUM_CORES, core_id);
    // }    
    // stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(inp     ,inpG     ,B*T*C  ,THRESHOLD);
    //     check_result(dinp    ,dinpG    ,B*T*C  ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif        
    // write_float_array_to_file("gold_temp.h", "inpG"      , "w", inp      , B*T*C);
    // write_float_array_to_file("gold_temp.h", "dinpG"     , "a", dinp     , B*T*C);

    //--------------------------------------------------------- softmax_forward
    // int V  = C;
    // // int Vp = C;
    // int Vp = C+3;//50 element over 16 iter 
    // //3141*16
    // // float* probs;
    // // float* logits;
    // if(core_id == 0){
    //     probs     = (float*)pi_l1_malloc(0, B * T  * Vp   * sizeof(float));
    //     logits    = (float*)pi_l1_malloc(0, B * T  * Vp   * sizeof(float));
    //     memcpy(logits    , data1, B * T * C * sizeof(float));
    // }
    // synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 16; i++){
    // for (int i = 0; i < 1; i++){
    //     softmax_forward(probs, logits, B, T, V, Vp, NUM_CORES, core_id);
    // }
    // stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(probs     ,probsG     ,B*T*C  ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif            
    // write_float_array_to_file("gold_temp.h", "probsG"     , "w", probs      , B*T*C);

    //--------------------------------------------------------- crossentropy_forward
    // int V  = C;
    // int Vp = C;
    // // float* losses ;
    // // float* probs  ;
    // // int  * targets;
    // //64*4
    // if(core_id == 0){
    //     losses      = (float*)pi_l1_malloc(0, B * T  * sizeof(float));
    //     probs       = (float*)pi_l1_malloc(0, B * T  * Vp   * sizeof(float));
    //     targets     = (int  *)pi_l1_malloc(0, B * T  * sizeof(int));
    //     memcpy(probs  , data1, B * T * Vp * sizeof(float));
    //     memcpy(targets, inp  , B * T * sizeof(int));
    // }
    // synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // crossentropy_forward(losses, probs, targets, B, T, Vp, NUM_CORES, core_id);
    // stop();
	// pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(losses     ,lossesG     ,B*T  ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif         
    // write_float_array_to_file("gold_temp.h", "lossesG"     , "w", losses      , B*T);

    //--------------------------------------------------------- crossentropy_softmax_backward
    // int V  = C;
    // int Vp = C;
    // float* dlosses     ;
    // float* dlogits     ;
    // float* probs       ;
    // int  * targets     ;
    // //3141 * 16
    // if(core_id == 0){
    //     dlosses     = (float*)pi_l1_malloc(0, B * T  * sizeof(float));
    //     dlogits     = (float*)pi_l1_malloc(0, B * T  * Vp   * sizeof(float));
    //     probs       = (float*)pi_l1_malloc(0, B * T  * Vp   * sizeof(float));
    //     targets     = (int  *)pi_l1_malloc(0, B * T  * sizeof(int));
    //     memcpy(dlosses, data1, B * T * sizeof(float));
    //     memcpy(dlogits, data1, B * T * Vp * sizeof(float));
    //     memcpy(probs  , data1, B * T * Vp * sizeof(float));
    //     memcpy(targets, inp  , B * T * sizeof(float));
    // }
    // synch_barrier();
    // // printf("CORE START\n");
    // // pi_perf_reset();
	// // pi_perf_start();
    // start();
    // // for (int i = 0; i < 16; i++){
    // for (int i = 0; i < 1; i++){
    //     crossentropy_softmax_backward(dlogits, dlosses, probs, targets, B, T, V, Vp, NUM_CORES, core_id);
    // }
    // stop();
    // pi_perf_stop();
    // printf("CORE DONE\n");
    // if(core_id == 0){
    //     check_result(dlogits     ,dlogitsG     ,B*T  ,THRESHOLD);
    // }
    // #if NUM_CORES > 1
	// synch_barrier();
	// BarrierCounter
	// #endif         
    // write_float_array_to_file("gold_temp.h", "dlogitsG"     , "w", dlogits      , B * T * Vp);

    //--------------------------------------------------------- exp
    // float* inp     = (float*)malloc(B * T * C * sizeof(float));
    // float* out     = (float*)malloc(B * T * C * sizeof(float));
    // memcpy(inp, data1, B * T * C * sizeof(float));
    // float err;
    // float maxerr = 0;
    // int maxerr_idx = 0;
    // for (int i = 0; i < B*T*C; i++){
    //     out[i] = fast_exp(inp[i]);
    //     err = fabsf(out[i]-expf(inp[i]));
    //     if(err > maxerr){
    //         maxerr = err;
    //         maxerr_idx = i;
    //     }
    // }
    // printf("maxerr[%d] = %f\t precise = %f \t approximate = %f\n",maxerr_idx,maxerr,expf(inp[maxerr_idx]),out[maxerr_idx]);
    // write_float_array_to_file("gold_temp.h", "outG"     , "w", out      , B * T * C);

    //--------------------------------------------------------- cosh
    // float* inp     = (float*)malloc(B * T * C * sizeof(float));
    // float* out     = (float*)malloc(B * T * C * sizeof(float));
    // memcpy(inp, data1, B * T * C * sizeof(float));
    // float err;
    // float maxerr = 0;
    // int maxerr_idx = 0;
    // for (int i = 0; i < B*T*C; i++){
    //     out[i] = fast_cosh(inp[i]);
    //     err = fabsf(out[i]-coshf(inp[i]));
    //     if(err > maxerr){
    //         maxerr = err;
    //         maxerr_idx = i;
    //     }
    // }
    // printf("maxerr[%d] = %f\t precise = %f \t approximate = %f\n",maxerr_idx,maxerr,coshf(inp[maxerr_idx]),out[maxerr_idx]);
    // write_float_array_to_file("gold_temp.h", "outG"     , "w", out      , B * T * C);

    //--------------------------------------------------------- tanh
    // float* inp     = (float*)malloc(B * T * C * sizeof(float));
    // float* out     = (float*)malloc(B * T * C * sizeof(float));
    // memcpy(inp, data1, B * T * C * sizeof(float));
    // float err;
    // float maxerr = 0;
    // int maxerr_idx = 0;
    // for (int i = 0; i < B*T*C; i++){
    //     out[i] = fast_tanh(inp[i]);
    //     err = fabsf(out[i]-tanhf(inp[i]));
    //     if(err > maxerr){
    //         maxerr = err;
    //         maxerr_idx = i;
    //     }
    // }
    // printf("maxerr[%d] = %f\t precise = %f \t approximate = %f\n",maxerr_idx,maxerr,tanhf(inp[maxerr_idx]),out[maxerr_idx]);
    // write_float_array_to_file("gold_temp.h", "outG"     , "w", out      , B * T * C);
}




// #include "config.h"
// #include "pulp.h"

// #include <stdio.h>
// #include <stdint.h>
// #include <limits.h> /* for CHAR_BIT */
// #include <math.h>

// #include "data.h"

// #define STACK_SIZE 2048

// #define M 8
// #define N 8
// #define P 8

// void main_fn(testresult_t *result, void (*start)(), void (*stop)());

// testcase_t testcases[] = {
//   { .name = "Matrix Multiplication", .test = main_fn },
//   {0, 0}
// };

// DATA_LOCATION MA_TYPE matA[M*N] __attribute__ ((aligned (4)));
// DATA_LOCATION MB_TYPE matB[N*P] __attribute__ ((aligned (4)));
// DATA_LOCATION OUT_TYPE matC[M*P] __attribute__ ((aligned (4)));

// // End of computation
// int done = 0;

// int retval = 0;

// void __attribute__ ((noinline)) matrix_init(MA_TYPE * __restrict__ A, MB_TYPE * __restrict__ B, OUT_TYPE * __restrict__ C) {
//   for (int i = 0; i < M; i++) 
//     for (int j = 0; j < N; j++){
//       A[i*N+j] = data1[i*N+j];


//     } 
      
//   for (int i = 0; i < N; i++) 
//     for (int j = 0; j < P; j++){
//       B[i*P+j] = data1[i*P+j];
//     }
//   for (int i = 0; i < M; i++) 
//     for (int j = 0; j < P; j++)  
//       C[i*P+j] = 0;
  
// }

// int __attribute ((noinline)) check_result(OUT_TYPE * __restrict__ result) {
//   #ifndef FABRIC
//     synch_barrier();
//   #endif

//   if(get_core_id() == 0) {
//     float diff;
//     int err = 0;

//     // for (int i = 0; i < (M*P); i++) {
//     //   diff = fabs(result[i] - ref[i]);
//     //   if(diff > THR) {
//     //     err++;
//     //   #ifdef VERBOSE

//     //     printf("Error at index %d:\t refrence %f\t output %f\t error %.4f\n", i, ref[i], result[i], diff);
//     //   #endif
      
//     //   }

//     //   #ifdef PRINT_RESULTS

//     //     printf("index %d:\t refrence %f\t output %f\t error %f\n", i, ref[i], result[i], diff);
//     //   #endif
//     // }

//     return err;

//   }
// }

// void main_fn(testresult_t *result, void (*start)(), void (*stop)()){
  
//   if (get_core_id() == 0)
//     matrix_init(matA, matB, matC);
 
//   #ifndef FABRIC
//   synch_barrier();
//   #endif
  
//   #ifdef STATS
//   start();
//   #endif
//   matMul(matA, matB, matC, M, N, P);

//   #ifdef STATS
//   stop();
//   #endif

//   #ifdef CHECK
//   result->errors = check_result(matC);
//   #endif
// };

// int main()
// {
//   #ifdef FABRIC
//       main_fn();
//   #else
//   if (rt_cluster_id() != 0)
//     return bench_cluster_forward(0);

//   int nbErrors = run_suite(testcases);

//   synch_barrier();
//   #endif
//   retval = nbErrors;

//   return retval;
// }
