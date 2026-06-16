#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#ifdef OMP
#include <omp.h>
#endif

// // our own utilities
// // defines: fopenCheck, freadCheck, fcloseCheck, fseekCheck, mallocCheck
// #include "../llm.c/llmc/utils.h"
// // defines: tokenizer_init, tokenizer_decode, tokenizer_free
// #include "../llm.c/llmc/tokenizer.h"
// // defines: dataloader_init, dataloader_reset, dataloader_next_batch, dataloader_free
// #include "../llm.c/llmc/dataloader.h"

//=============================================
#include "half.hpp"
using half_float::half;
#include "data.h"
#include "gold.h"
#include "inc.h"


//=============================================

void write_float_array_to_file(const char *filename, const char *arrname, const char *writemode, float *array, int size) {
    FILE *fp = fopen(filename, writemode);
    if (fp == NULL) {
        perror("Failed to open float file");
        return;
    }
    fprintf(fp, "float %s[] = {",arrname);
    for (int i = 0; i < size-1; i++) {
        fprintf(fp, "%f, ", array[i]);
    }
    fprintf(fp, "%f ", array[size-1]);
    fprintf(fp, "};\n");
    fclose(fp);
}

void write_half_array_to_file(const char *filename, const char *arrname, const char *writemode, half *array, int size) {
    FILE *fp = fopen(filename, writemode);
    if (fp == NULL) {
        perror("Failed to open half file");
        return;
    }
    fprintf(fp, "__fp16 %s[] = {",arrname);
    for (int i = 0; i < size-1; i++) {
        fprintf(fp, "%f, ", static_cast<float>(array[i]));
        // fprintf(fp, "%x, ", array[i]);
    }
    fprintf(fp, "%f ", static_cast<float>(array[size-1]));
    // fprintf(fp, "%x ", array[size-1]);
    fprintf(fp, "};\n");
    fclose(fp);
}

void write_half_array_to_file_hex(const char *filename, const char *arrname, const char *writemode, half *array, int size) {
    FILE *fp = fopen(filename, writemode);
    if (fp == NULL) {
        perror("Failed to open half file");
        return;
    }
    fprintf(fp, "__fp16 %s[] = {",arrname);
    for (int i = 0; i < size-1; i++) {
        fprintf(fp, "0x%x, ", (((uint16_t *)array)[i]));
        // fprintf(fp, "%x, ", array[i]);
    }
    fprintf(fp, "0x%x ", (((uint16_t *)array)[size-1]));
    // fprintf(fp, "%x ", array[size-1]);
    fprintf(fp, "};\n");
    fclose(fp);
}



half from_bits(uint16_t bits) {
    half h;
    std::memcpy(&h, &bits, sizeof(bits));
    return h;
}

half fast_exp(half x) {
    float xf = static_cast<float>(x);

    int val = static_cast<int>(1486.0f * xf + 15360.0f);
    if (val < 0) val = 0;
    if (val > 0x7BFF) val = 0x7BFF;

    return from_bits(static_cast<uint16_t>(val));
}

half fast_cosh(half x) {
    half ex  = fast_exp( x);
    half e_x = fast_exp(-x);
    return (half((ex+e_x)/2));
}

half fast_tanh(half x) {
    half e2x  = fast_exp(half(2*x));
    return half(half(e2x-1)/half(e2x+1));
}

half fast_tanh_v2(half x) {
    half ex  = fast_exp(half(x));
    half ex_1  = fast_exp(half(-x));
    // return half(half(ex-ex_1)/half(ex+ex_1));
    return half(ex-ex_1);
}


// ----------------------------------------------------------------------------
// all the individual layers' forward and backward passes
// B = batch_size, T = sequence_length, C = channels, V = vocab_size

void encoder_forward(half* out,
                   int* inp, half* wte, half* wpe,
                   int B, int T, int C) {
    // out is (B,T,C). At each position (b,t), a C-dimensional vector summarizing token & position
    // inp is (B,T) of integers, holding the token ids at each (b,t) position
    // wte is (V,C) of token embeddings, short for "weight token embeddings"
    // wpe is (maxT,C) of position embeddings, short for "weight positional embedding"
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            // seek to the output position in out[b,t,:]
            half* out_bt = out + b * T * C + t * C;
            // get the index of the token at inp[b, t]
            int ix = inp[b * T + t];
            // seek to the position in wte corresponding to the token
            half* wte_ix = wte + ix * C;
            // seek to the position in wpe corresponding to the position
            half* wpe_t = wpe + t * C;
            // add the two vectors and store the result in out[b,t,:]
            for (int i = 0; i < C; i++) {
                out_bt[i] = wte_ix[i] + wpe_t[i];
            }
        }
    }
}

void encoder_backward(half* dwte, half* dwpe,
                      half* dout, int* inp,
                      int B, int T, int C) {
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            half* dout_bt = dout + b * T * C + t * C;
            int ix = inp[b * T + t];
            half* dwte_ix = dwte + ix * C;
            half* dwpe_t = dwpe + t * C;
            for (int i = 0; i < C; i++) {
                half d = dout_bt[i];
                dwte_ix[i] += d;
                dwpe_t[i] += d;
            }
        }
    }
}

void layernorm_forward(half* out, half* mean, half* rstd,
                       half* inp, half* weight, half* bias,
                       int B, int T, int C) {
    // reference: https://pytorch.org/docs/stable/generated/torch.nn.LayerNorm.html
    // both inp and out are (B,T,C) of the activations
    // mean and rstd are (B,T) buffers, to be used later in backward pass
    // at each position (b,t) of the input, the C-dimensional vector
    // of activations gets normalized, then scaled and shifted
    half eps = half(1e-5f);
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            // seek to the input position inp[b,t,:]
            half* x = inp + b * T * C + t * C;
            // calculate the mean
            half m = half(0.0f);
            for (int i = 0; i < C; i++) {
                m += x[i];
            }
            m = m/C;
            // calculate the variance (without any bias correction)
            half v = half(0.0f);
            for (int i = 0; i < C; i++) {
                half xshift = x[i] - m;
                v += xshift * xshift;
            }
            v = v/C;
            // calculate the rstd (reciprocal standard deviation)
            half s = half (1.0f / sqrtf(v + eps));
            // seek to the output position in out[b,t,:]
            half* out_bt = out + b * T * C + t * C;
            for (int i = 0; i < C; i++) {
                half n = (s * (x[i] - m)); // normalize
                half o = n * weight[i] + bias[i]; // scale and shift
                out_bt[i] = o; // write
            }
            // cache the mean and rstd for the backward pass later
            mean[b * T + t] = m;
            rstd[b * T + t] = s;
        }
    }
}

void layernorm_backward(half* dinp, half* dweight, half* dbias,
                        half* dout, half* inp, half* weight, half* mean, half* rstd,
                        int B, int T, int C) {
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            half* dout_bt = dout + b * T * C + t * C;
            half* inp_bt  = inp + b * T * C + t * C;
            half* dinp_bt = dinp + b * T * C + t * C;
            half mean_bt  = mean[b * T + t];
            half rstd_bt  = rstd[b * T + t];

            // first: two reduce operations
            half dnorm_mean = half(0.0f);
            half dnorm_norm_mean = half(0.0f);
            for (int i = 0; i < C; i++) {
                half norm_bti = (inp_bt[i] - mean_bt) * rstd_bt;
                half dnorm_i = weight[i] * dout_bt[i];
                dnorm_mean += dnorm_i;
                dnorm_norm_mean += dnorm_i * norm_bti;
            }
            dnorm_mean = dnorm_mean / C;
            dnorm_norm_mean = dnorm_norm_mean / C;

            // now iterate again and accumulate all the gradients
            for (int i = 0; i < C; i++) {
                half norm_bti = (inp_bt[i] - mean_bt) * rstd_bt;
                half dnorm_i = weight[i] * dout_bt[i];
                // gradient contribution to bias
                dbias[i] += dout_bt[i];
                // gradient contribution to weight
                dweight[i] += norm_bti * dout_bt[i];
                // gradient contribution to input

                half dval = half(0.0f);
                // printf("1 dnorm_i = %f \t dnorm_mean = %f norm_bti = %f \t dnorm_norm_mean = %f \t rstd_bt = %f\n"
                    // ,dnorm_i,dnorm_mean,norm_bti,dnorm_norm_mean,rstd_bt);
                dval += dnorm_i; // term 1
                dval -= dnorm_mean; // term 2
                dval -= norm_bti * dnorm_norm_mean; // term 3
                dval *= rstd_bt; // final scale
                dinp_bt[i] += dval;
            }
        }
    }
}

void matmul_forward_naive(half* out,
                         const half* inp, const half* weight, const half* bias,
                         int B, int T, int C, int OC) {
    // the most naive implementation of matrix multiplication
    // this serves as an algorithmic reference, and as a fallback for
    // unfriendly input shapes inside matmul_forward(), below.
    #pragma omp parallel for collapse(2)
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            int bt = b * T + t;
            for (int o = 0; o < OC; o++) {
                half val = (bias != NULL) ? bias[o] : half(0.0f);
                for (int i = 0; i < C; i++) {
                    val += inp[bt * C + i] * weight[o*C + i];
                }
                if(bt == 0){
                    printf("out[%d] = %f\n",o,(float)(val-bias[o]));
                }
                out[bt * OC + o] = val;
            }
        }
    }
}

void matmul_backward(half* dinp, half* dweight, half* dbias,
                    const half* dout, const half* inp, const half* weight,
                    int B, int T, int C, int OC) {
    // most of the running time is spent here and in matmul_forward
    // this backward could be done in a single "round" of loops
    // but that doesn't afford an efficient parallelization strategy

    // backward into inp first, parallelize over B,T
    #pragma omp parallel for collapse(2)
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            const half* dout_bt = dout + b * T * OC + t * OC;
            half* dinp_bt = dinp + b * T * C + t * C;
            for (int o = 0; o < OC; o++) {
                const half* wrow = weight + o*C;
                half d = dout_bt[o];
                for (int i = 0; i < C; i++) {
                    dinp_bt[i] += wrow[i] * d;
                }
            }
        }
    }
    // backward into weight/bias, parallelize over output channels OC
    #pragma omp parallel for
    for (int o = 0; o < OC; o++) {
        for (int b = 0; b < B; b++) {
            for (int t = 0; t < T; t++) {
                const half* dout_bt = dout + b * T * OC + t * OC;
                const half* inp_bt = inp + b * T * C + t * C;
                half* dwrow = dweight + o*C;
                half d = dout_bt[o];
                if (dbias != NULL) { dbias[o] += d; }
                for (int i = 0; i < C; i++) {
                    dwrow[i] += inp_bt[i] * d;
                }
            }
        }
    }
}

void attention_forward(half* out, half* preatt, half* att,
                       half* inp,
                       int B, int T, int C, int NH) {
    // input is (B, T, 3C) holding the query, key, value (Q, K, V) vectors
    // preatt, att are (B, NH, T, T). NH = number of heads, T = sequence length
    // that holds the pre-attention and post-attention scores (used in backward)
    // output is (B, T, C)
    // attention is the only layer that mixes information across time
    // every other operation is applied at every (b,t) position independently
    // (and of course, no layer mixes information across batch)
    int C3 = C*3;
    int hs = C / NH; // head size
    half scale = half(1.0 / sqrtf(hs));
    // half scale = 1.0 / hs;

    #pragma omp parallel for collapse(3)
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            for (int h = 0; h < NH; h++) {
                half* query_t = inp + b * T * C3 + t * C3 + h * hs;
                half* preatt_bth = preatt + b*NH*T*T + h*T*T + t*T;
                half* att_bth = att + b*NH*T*T + h*T*T + t*T;
                // printf("index = %d\n",b*NH*T*T + h*T*T + t*T);
                // pass 1: calculate query dot key and maxval
                half maxval = half(-10000.0f); // TODO something better
                for (int t2 = 0; t2 <= t; t2++) {
                    half* key_t2 = inp + b * T * C3 + t2 * C3 + h * hs + C; // +C because it's key

                    // (query_t) dot (key_t2)
                    half val = half(0.0f);
                    for (int i = 0; i < hs; i++) {
                        val += query_t[i] * key_t2[i];
                    }
                    // printf("t2 = %d \t val = %f\n",t2,val);

                    val *= scale;
                    if (val > maxval) {
                        maxval = val;
                    }

                    preatt_bth[t2] = val;
                    // printf("preatt_bth[%d] = %f\n",t2,(float)preatt_bth[t2]);

                }
                // printf("maxval = %f\n",(float)maxval);
                // pass 2: calculate the exp and keep track of sum
                // maxval is being calculated and subtracted only for numerical stability
                half expsum = half(0.0f);
                for (int t2 = 0; t2 <= t; t2++) {
                    // half expv = expf(preatt_bth[t2] - maxval);//I CHANGED THIS PART
                    half expv = half(fast_exp(preatt_bth[t2] - maxval));//I CHANGED THIS PART
                    // half expv = half((preatt_bth[t2] - maxval));//I CHANGED THIS PART
                    // half expv = preatt_bth[t2] - maxval;
                    expsum += expv;
                    att_bth[t2] = expv;
                    // printf("\t[%d]\n",b*NH*T*T + h*T*T + t*T+t2);

                }
                half expsum_inv = expsum == 0.0f ? half(0.0f) : half(1.0f / expsum);

                // pass 3: normalize to get the softmax
                for (int t2 = 0; t2 < T; t2++) {
                    if (t2 <= t) {
                        att_bth[t2] *= expsum_inv;
                    } else {
                        // causal attention mask. not strictly necessary to set to zero here
                        // only doing this explicitly for debugging and checking to PyTorch
                        att_bth[t2] = 0.0f;
                    }
                }

                // pass 4: accumulate weighted values into the output of attention
                half* out_bth = out + b * T * C + t * C + h * hs;
                for (int i = 0; i < hs; i++) { out_bth[i] = 0.0f; }
                for (int t2 = 0; t2 <= t; t2++) {
                    half* value_t2 = inp + b * T * C3 + t2 * C3 + h * hs + C*2; // +C*2 because it's value
                    half att_btht2 = att_bth[t2];
                    for (int i = 0; i < hs; i++) {
                        out_bth[i] += att_btht2 * value_t2[i];
                    }
                }
            }
        }
    }
}

void attention_backward(half* dinp, half* dpreatt, half* datt,
                        half* dout, half* inp, half* att,
                        int B, int T, int C, int NH) {
    // inp/dinp are (B, T, 3C) Q,K,V
    // att/datt/dpreatt are (B, NH, T, T)
    // dout is (B, T, C)
    int C3 = C*3;
    int hs = C / NH; // head size
    half scale = half(1.f / sqrtf(hs));//I CHANGED THIS PART
    // float scale = 1.f / hs;

    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            for (int h = 0; h < NH; h++) {
                half* att_bth = att + b*NH*T*T + h*T*T + t*T;
                half* datt_bth = datt + b*NH*T*T + h*T*T + t*T;
                half* dpreatt_bth = dpreatt + b*NH*T*T + h*T*T + t*T;
                half* dquery_t = dinp + b * T * C3 + t * C3 + h * hs;
                half* query_t = inp + b * T * C3 + t * C3 + h * hs;

                // backward pass 4, through the value accumulation
                half* dout_bth = dout + b * T * C + t * C + h * hs;
                for (int t2 = 0; t2 <= t; t2++) {
                    half* value_t2 = inp + b * T * C3 + t2 * C3 + h * hs + C*2; // +C*2 because it's value
                    half* dvalue_t2 = dinp + b * T * C3 + t2 * C3 + h * hs + C*2;
                    for (int i = 0; i < hs; i++) {
                        // in the forward pass this was:
                        // out_bth[i] += att_bth[t2] * value_t2[i];
                        // so now we have:
                        datt_bth[t2] += value_t2[i] * dout_bth[i];
                        dvalue_t2[i] += att_bth[t2] * dout_bth[i];
                    }
                }

                // backward pass 2 & 3, the softmax
                // note that softmax (like e.g. tanh) doesn't need the input (preatt) to backward
                for (int t2 = 0; t2 <= t; t2++) {
                    for (int t3 = 0; t3 <= t; t3++) {
                        half indicator = t2 == t3 ? half(1.0f) : half(0.0f);
                        half local_derivative = att_bth[t2] * (indicator - att_bth[t3]);
                        dpreatt_bth[t3] += local_derivative * datt_bth[t2];
                    }
                }

                // backward pass 1, the query @ key matmul
                for (int t2 = 0; t2 <= t; t2++) {
                    half* key_t2 = inp + b * T * C3 + t2 * C3 + h * hs + C; // +C because it's key
                    half* dkey_t2 = dinp + b * T * C3 + t2 * C3 + h * hs + C; // +C because it's key
                    for (int i = 0; i < hs; i++) {
                        // in the forward pass this was:
                        // preatt_bth[t2] += (query_t[i] * key_t2[i]) * scale;
                        // so now we have:
                        dquery_t[i] += key_t2[i] * dpreatt_bth[t2] * scale;
                        dkey_t2[i] += query_t[i] * dpreatt_bth[t2] * scale;
                    }
                }
            }
        }
    }
}

// #define GELU_SCALING_FACTOR sqrtf(2.0f / M_PI)//I CHANGED THIS LINE
#define GELU_SCALING_FACTOR 0.797884561
void gelu_forward(half* out, half* inp, int N) {
    // (approximate) GeLU elementwise non-linearity in the MLP block of Transformer
    for (int i = 0; i < N; i++) {
        half x = inp[i];
        half cube = half(0.044715f * x * x * x);
        // printf("x + cube[%d] = %f\n",i,x + cube);
        // printf("bigger[%d] = %f\n",i,1.0f + GELU_SCALING_FACTOR * (x + cube));
        // out[i] = 0.5f * x * (1.0f + tanhf(GELU_SCALING_FACTOR * (x + cube)));        
        out[i] = 0.5f * x * (1.0f + fast_tanh(half(GELU_SCALING_FACTOR) * (x + cube)));
        // out[i] = half(0.5f * x * (1.0f + (GELU_SCALING_FACTOR * (x + cube))));//I CHANGED THIS LINE
    }
}

void gelu_backward(half* dinp, half* inp, half* dout, int N) {
    for (int i = 0; i < N; i++) {
        half x = inp[i];
        half cube = half(0.044715f * x * x * x);
        // if(i == 311){
        //     printf("cube[311] = %f\n",(float)cube);
        // }else if(i == 313){
        //     printf("cube[313] = %f\n",(float)cube);
        // }
        half tanh_arg = half(GELU_SCALING_FACTOR * (x + cube));
        // float tanh_out = tanhf(tanh_arg);//I CHANGED THIS LINE
        // float coshf_out = coshf(tanh_arg);//I CHANGED THIS LINE
        float tanh_out = fast_tanh(tanh_arg);//I CHANGED THIS LINE
        float coshf_out = fast_cosh(tanh_arg);//I CHANGED THIS LINE        
        // half tanh_out = tanh_arg;//I CHANGED THIS LINE
        // half coshf_out = tanh_arg;//I CHANGED THIS LINE        
        half sech_out = half(1.0f / (coshf_out * coshf_out));
        half local_grad = half(0.5f * (1.0f + tanh_out) + x * 0.5f * sech_out * GELU_SCALING_FACTOR * (1.0f + 3.0f * 0.044715f * x * x));
        dinp[i] += local_grad * dout[i];
    }
}

void residual_forward(half* out, half* inp1, half* inp2, int N) {
    for (int i = 0; i < N; i++) {
        out[i] = inp1[i] + inp2[i];
    }
}

void residual_backward(half* dinp1, half* dinp2, half* dout, int N) {
    for (int i = 0; i < N; i++) {
        dinp1[i] += dout[i];
        dinp2[i] += dout[i];
    }
}

void softmax_forward(half* probs, half* logits, int B, int T, int V, int Vp) {
    // output: probs are (B,T,Vp) of the probabilities (sums to 1.0 in each b,t position)
    // input: logits is (B,T,Vp) of the unnormalized log probabilities
    // Vp is the padded vocab size (for efficiency), V is the "real" vocab size
    // example: Vp is 50304 and V is 50257
    #pragma omp parallel for collapse(2)
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            // probs <- softmax(logits)
            half* logits_bt = logits + b * T * Vp + t * Vp;
            half* probs_bt = probs + b * T * Vp + t * Vp;

            // maxval is only calculated and subtracted for numerical stability
            half maxval = half(-10000.0f); // TODO something better
            for (int i = 0; i < V; i++) {
                if (logits_bt[i] > maxval) {
                    maxval = logits_bt[i];
                }
            }

            half sum = half(0.0f);
            for (int i = 0; i < V; i++) {
                // probs_bt[i] = expf(logits_bt[i] - maxval);//I CHANGED THIS LINE 
                probs_bt[i] = fast_exp(logits_bt[i] - maxval);//I CHANGED THIS LINE 
                // probs_bt[i] = logits_bt[i] - maxval; 
                sum += probs_bt[i];
            }
            // note we only loop to V, leaving the padded dimensions
            for (int i = 0; i < V; i++) {
                probs_bt[i] /= sum;
            }

            // for extra super safety we may wish to include this too,
            // forcing the probabilities here to be zero, but it shouldn't matter
            for (int i = V; i < Vp; i++) {
                probs_bt[i] = half(0.0f);
            }
        }
    }
}

void crossentropy_forward(half* losses,
                          half* probs, int* targets,
                          int B, int T, int Vp) {
    // output: losses is (B,T) of the individual losses at each position
    // input: probs are (B,T,Vp) of the probabilities
    // input: targets is (B,T) of integers giving the correct index in logits
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            // loss = -log(probs[target])
            half* probs_bt = probs + b * T * Vp + t * Vp;
            int ix = targets[b * T + t];
            losses[b * T + t] = -logf(probs_bt[ix]);
            // losses[b * T + t] = probs_bt[ix];
        }
    }
}

void crossentropy_softmax_backward(half* dlogits,
                           half* dlosses, half* probs, int* targets,
                           int B, int T, int V, int Vp) {
    // backwards through both softmax and crossentropy
    for (int b = 0; b < B; b++) {
        for (int t = 0; t < T; t++) {
            half* dlogits_bt = dlogits + b * T * Vp + t * Vp;
            half* probs_bt = probs + b * T * Vp + t * Vp;
            half dloss = dlosses[b * T + t];
            int ix = targets[b * T + t];
            // note we only loop to V, leaving the padded dimensions
            // of dlogits untouched, so gradient there stays at zero
            for (int i = 0; i < V; i++) {
                half p = probs_bt[i];
                half indicator = i == ix ? half(1.0f) : half(0.0f);
                dlogits_bt[i] += (p - indicator) * dloss;
            }
        }
    }
}



int main(){
    int B = B_Size;
    int C = C_Size;
    int T = T_Size;
    half *data1h = (half*)malloc(B * T * C * sizeof(half));
    for (int i = 0; i < B * T * C; i++){
        data1h[i] = half(data1[i]);
    }
    //--------------------------------------------------------- encoder_forward
    // half *out  = (half*)malloc(B * T * C * sizeof(half));
    // half *wte  = (half*)malloc(B * T * C * sizeof(half));
    // half *wpe  = (half*)malloc(B * T * C * sizeof(half));
    // memcpy(wte, data1h, B * T * C * sizeof(half));    
    // memcpy(wpe, data1h, B * T * C * sizeof(half));
    // encoder_forward(out, inp, wte, wpe, B, T, C);
    // write_half_array_to_file("gold_temp.h", "outG", "w", out, B*T*C);
    //---------------------------------------------------------

    //--------------------------------------------------------- encoder_backward
    // half* dwte = (half*)malloc(B * T * C * sizeof(half));
    // half* dwpe = (half*)malloc(B * T * C * sizeof(half));
    // half* dout = (half*)malloc(B * T * C * sizeof(half));
    // memcpy(dwte, data1h, B * T * C * sizeof(half));
    // memcpy(dwpe, data1h, B * T * C * sizeof(half));
    // memcpy(dout, data1h, B * T * C * sizeof(half));
    // encoder_backward(dwte, dwpe, dout, inp, B, T, C);
    // write_half_array_to_file("gold_temp.h", "dwteG", "w", dwte, B*T*C);
    // write_half_array_to_file("gold_temp.h", "dwpeG", "a", dwpe, B*T*C);
    //---------------------------------------------------------

    //--------------------------------------------------------- layernorm_forward
    // half* inp    = (half*)malloc(B * T * C * sizeof(half));
    // half* mean   = (half*)malloc(B * T * 1 * sizeof(half));
    // half* rstd   = (half*)malloc(B * T * 1 * sizeof(half));
    // half* weight = (half*)malloc(1 * 1 * C * sizeof(half));
    // half* bias   = (half*)malloc(1 * 1 * C * sizeof(half));
    // half* out    = (half*)malloc(B * T * C * sizeof(half));
    // memcpy(inp   , data1h, B * T * C * sizeof(half));
    // memcpy(weight, data1h, 1 * 1 * C * sizeof(half));
    // memcpy(bias  , data1h, 1 * 1 * C * sizeof(half));
    // memcpy(mean  , data1h, B * T * 1 * sizeof(half));
    // memcpy(rstd  , data1h, B * T * 1 * sizeof(half));
    // layernorm_forward(out, mean, rstd, inp, weight, bias, B, T, C);
    // write_half_array_to_file("gold_temp.h", "meanG", "w", mean, B*T*1);
    // write_half_array_to_file("gold_temp.h", "rstdG", "a", rstd, B*T*1);
    // write_half_array_to_file("gold_temp.h", "outG" , "a", out , B*T*C);

    //--------------------------------------------------------- layernorm_backward
    // half* inp    = (half*)malloc(B * T * C * sizeof(half));
    // half* dinp   = (half*)malloc(B * T * C * sizeof(half));
    // half* mean   = (half*)malloc(B * T * 1 * sizeof(half));
    // half* rstd   = (half*)malloc(B * T * 1 * sizeof(half));
    // half* dweight= (half*)malloc(1 * 1 * C * sizeof(half));
    // half* weight = (half*)malloc(1 * 1 * C * sizeof(half));
    // half* dbias  = (half*)malloc(1 * 1 * C * sizeof(half));
    // half* dout   = (half*)malloc(B * T * C * sizeof(half));
    // memcpy(inp    , data1h, B * T * C * sizeof(half));
    // memcpy(dinp   , data1h, B * T * C * sizeof(half));
    // memcpy(dweight, data1h, 1 * 1 * C * sizeof(half));
    // memcpy(weight , data1h, 1 * 1 * C * sizeof(half));
    // memcpy(dbias  , data1h, 1 * 1 * C * sizeof(half));
    // memcpy(mean   , data1h, B * T * 1 * sizeof(half));
    // memcpy(rstd   , data1h, B * T * 1 * sizeof(half));
    // memcpy(dout   , data1h, B * T * C * sizeof(half));
    // layernorm_backward(dinp, dweight, dbias, dout, inp, weight, mean, rstd, B, T, C);
    // write_half_array_to_file("gold_temp.h", "dbiasG"  , "w", dbias  , 1*1*C);
    // write_half_array_to_file("gold_temp.h", "dweightG", "a", dweight, 1*1*C);
    // write_half_array_to_file("gold_temp.h", "dinpG"   , "a", dinp   , B*T*C);

    //--------------------------------------------------------- matmul_forward_naive
    // int OC = C;
    // half* inp    = (half*)malloc(B * T * C * sizeof(half));
    // half* weight = (half*)malloc(1 * OC* C * sizeof(half));
    // half* bias   = (half*)malloc(1 * 1 * OC* sizeof(half));
    // half* out    = (half*)malloc(B * T * C * sizeof(half));
    // memcpy(inp    , data1h, B * T * C * sizeof(half));
    // memcpy(weight , data1h, 1 * OC* C * sizeof(half));
    // memcpy(bias   , data1h, 1 * 1 * OC* sizeof(half));
    // memcpy(out    , data1h, B * T * C * sizeof(half));    
    // matmul_forward_naive(out, inp, weight, bias, B, T, C, OC);
    // write_half_array_to_file("gold_temp.h", "outG"  , "w", out  , B*T*C);

    //--------------------------------------------------------- matmul_backward
    // int OC = C;
    // half* inp     = (half*)malloc(B * T * C * sizeof(half));
    // half* dinp    = (half*)malloc(B * T * C * sizeof(half));
    // half* dweight = (half*)malloc(1 * OC* C * sizeof(half));
    // half* weight  = (half*)malloc(1 * OC* C * sizeof(half));
    // half* dbias   = (half*)malloc(1 * 1 * OC* sizeof(half));
    // half* dout    = (half*)malloc(B * T * OC* sizeof(half));
    // memcpy(inp    , data1h, B * T * C * sizeof(half));
    // memcpy(dinp   , data1h, B * T * C * sizeof(half));
    // memcpy(dweight, data1h, 1 * OC* C * sizeof(half));
    // memcpy(weight , data1h, 1 * OC* C * sizeof(half));
    // memcpy(dbias  , data1h, 1 * 1 * OC* sizeof(half));
    // memcpy(dout   , data1h, B * T * C * sizeof(half));
    // matmul_backward(dinp, dweight, dbias, dout, inp, weight, B, T, C, OC);
    // write_half_array_to_file("gold_temp.h", "dinpG"     , "w", dinp      , B*T*C);
    // write_half_array_to_file("gold_temp.h", "dweightG"  , "a", dweight   , OC*C);
    // write_half_array_to_file("gold_temp.h", "dbiasG"    , "a", dbias     , OC);

    //--------------------------------------------------------- attention_forward
    // int NH = 2;
    // T = T/2;
    // half* inp     = (half*)malloc(B * T  * 3*C   * sizeof(half));
    // half* preatt  = (half*)malloc(B * NH * T * T * sizeof(half));
    // half* att     = (half*)malloc(B * NH * T * T * sizeof(half));
    // half* out     = (half*)malloc(B * T  * C     * sizeof(half));
    // for (int i = 0; i < 3; i++){
    //     memcpy(inp    + i*(B * T * C)    , data1h, B * T  * C    * sizeof(half));
    // }
    // for (int i = 0; i < 1; i++){
    //     memcpy(preatt + i*(B * NH * T * T)    , data1h, B * NH * T * T    * sizeof(half));
    // }
    // for (int i = 0; i < 1; i++){
    //     memcpy(att    + i*(B * NH * T * T)    , data1h, B * NH * T * T    * sizeof(half));
    // }
    // attention_forward(out, preatt, att, inp, B, T, C, NH);
    // write_half_array_to_file("gold_temp.h", "outG"     , "w", out      , B*T*C);
    // write_half_array_to_file("gold_temp.h", "preattG"  , "a", preatt   , B*NH*T*T);
    // write_half_array_to_file("gold_temp.h", "attG"     , "a", att      , B*NH*T*T);

    //--------------------------------------------------------- attention_backward
    // int NH = 2;
    // T = T/2;
    // half* inp     = (half*)malloc(B * T  * 3*C   * sizeof(half));
    // half* dinp    = (half*)malloc(B * T  * 3*C   * sizeof(half));
    // half* dpreatt = (half*)malloc(B * NH * T * T * sizeof(half));
    // half* att     = (half*)malloc(B * NH * T * T * sizeof(half));
    // half* datt    = (half*)malloc(B * NH * T * T * sizeof(half));
    // half* dout    = (half*)malloc(B * T  * C     * sizeof(half));
    // for (int i = 0; i < 3; i++){
    //     memcpy(inp    + i*(B * T * C)    , data1h, B * T  * C        * sizeof(half));
    //     memcpy(dinp   + i*(B * T * C)    , data1h, B * T  * C        * sizeof(half));
    // }
    // memcpy(dpreatt                       , data1h, B * NH * T * T    * sizeof(half));
    // memcpy(att                           , data1h, B * NH * T * T    * sizeof(half));
    // memcpy(datt                          , data1h, B * NH * T * T    * sizeof(half));
    // memcpy(dout                          , data1h, B * T * C         * sizeof(half));
    // attention_backward(dinp, dpreatt, datt, dout, inp, att, B, T, C, NH);
    // write_half_array_to_file("gold_temp.h", "dattG"     , "w", datt      , B*NH*T*T);
    // write_half_array_to_file("gold_temp.h", "dpreattG"  , "a", dpreatt   , B*NH*T*T);
    // write_half_array_to_file("gold_temp.h", "dinpG"     , "a", dinp      , B*T*3*C );

    //--------------------------------------------------------- gelu_forward
    int N = B*T*C;
    half* inp     = (half*)malloc(B * T  * C   * sizeof(half));
    half* out     = (half*)malloc(B * T  * C   * sizeof(half));
    memcpy(inp , data1h, B * T * C * sizeof(half));
    gelu_forward(out, inp, N);
    write_half_array_to_file("gold_temp.h", "outG"     , "w", out      , B*T*C);

    //--------------------------------------------------------- gelu_backward
    // int N = B*T*C;
    // half* inp     = (half*)malloc(B * T  * C   * sizeof(half));
    // half* dinp    = (half*)malloc(B * T  * C   * sizeof(half));
    // half* dout    = (half*)malloc(B * T  * C   * sizeof(half));
    // memcpy(inp  , data1h, B * T * C * sizeof(half));
    // memcpy(dinp , data1h, B * T * C * sizeof(half));
    // memcpy(dout , data1h, B * T * C * sizeof(half));
    // gelu_backward(dinp, inp, dout, N);
    // write_half_array_to_file("gold_temp.h", "dinpG"     , "w", dinp      , B*T*C);

    //--------------------------------------------------------- residual_forward
    // int N = B*T*C;
    // half* inp1     = (half*)malloc(B * T  * C   * sizeof(half));
    // half* inp2     = (half*)malloc(B * T  * C   * sizeof(half));
    // half* out      = (half*)malloc(B * T  * C   * sizeof(half));
    // memcpy(inp1  , data1h, B * T * C * sizeof(half));
    // memcpy(inp2  , data1h, B * T * C * sizeof(half));
    // residual_forward(out, inp1, inp2, N);
    // write_half_array_to_file("gold_temp.h", "outG"     , "w", out      , B*T*C);

    //--------------------------------------------------------- residual_backward
    // int N = B*T*C;
    // half* inp       = (half*)malloc(B * T  * C   * sizeof(half));
    // half* dinp      = (half*)malloc(B * T  * C   * sizeof(half));
    // half* dout      = (half*)malloc(B * T  * C   * sizeof(half));
    // memcpy(inp    , data1h, B * T * C * sizeof(half));
    // memcpy(dinp   , data1h, B * T * C * sizeof(half));
    // memcpy(dout   , data1h, B * T * C * sizeof(half));
    // residual_backward(inp, dinp, dout, N);
    // write_half_array_to_file("gold_temp.h", "inpG"      , "w", inp      , B*T*C);
    // write_half_array_to_file("gold_temp.h", "dinpG"     , "a", dinp     , B*T*C);

    //--------------------------------------------------------- softmax_forward
    // int V  = C;
    // int Vp = C;
    // half* probs      = (half*)malloc(B * T  * Vp   * sizeof(half));
    // half* logits     = (half*)malloc(B * T  * Vp   * sizeof(half));
    // memcpy(logits  , data1h, B * T * C * sizeof(half));
    // softmax_forward(probs, logits, B, T, V, Vp);
    // write_half_array_to_file("gold_temp.h", "probsG"     , "w", probs      , B*T*C);

    //--------------------------------------------------------- crossentropy_forward
    // int V  = C;
    // int Vp = C;
    // half* losses      = (half*)malloc(B * T  * sizeof(half));
    // half* probs       = (half*)malloc(B * T  * Vp   * sizeof(half));
    // int  * targets     = (int  *)malloc(B * T  * sizeof(int));
    // memcpy(probs  , data1h, B * T * Vp * sizeof(half));
    // memcpy(targets, inp  , B * T * sizeof(int));
    // crossentropy_forward(losses, probs, targets, B, T, Vp);
    // write_half_array_to_file("gold_temp.h", "lossesG"     , "w", losses      , B*T);

    //--------------------------------------------------------- crossentropy_softmax_backward
    // int V  = C;
    // int Vp = C;
    // half* dlosses     = (half*)malloc(B * T  * sizeof(half));
    // half* dlogits     = (half*)malloc(B * T  * Vp   * sizeof(half));
    // half* probs       = (half*)malloc(B * T  * Vp   * sizeof(half));
    // int  * targets     = (int  *)malloc(B * T  * sizeof(int));
    // memcpy(dlosses, data1h, B * T * sizeof(half));
    // memcpy(dlogits, data1h, B * T * Vp * sizeof(half));
    // memcpy(probs  , data1h, B * T * Vp * sizeof(half));
    // memcpy(targets, inp  , B * T * sizeof(int));
    // crossentropy_softmax_backward(dlogits, dlosses, probs, targets, B, T, V, Vp);
    // write_half_array_to_file("gold_temp.h", "dlogitsG"     , "w", dlogits      , B * T * Vp);

    //--------------------------------------------------------- exp
    // half* inp     = (half*)malloc(B * T * C * sizeof(half));
    // half* out     = (half*)malloc(B * T * C * sizeof(half));
    // memcpy(inp, data1h, B * T * C * sizeof(half));
    // float err;
    // float maxerr = 0;
    // int maxerr_idx = 0;
    // int count = 0;
    // for (int i = 0; i < B*T*C; i++){
    //     out[i] = fast_exp(inp[i]);
    //     err = fabsf((float)out[i]-expf((float)inp[i]));
    //     // if(err > (10*((float)out[i])/100)){
    //     //     count++;
    //     //     printf("err[%d] = %f\n",i,err);
    //     // }
    //     // printf("cout = %d\n",count);
    //     if(err > maxerr){
    //         maxerr = err;
    //         maxerr_idx = i;
    //     }
    // }
    // printf("maxerr[%d] = %f\t precise = %f \t approximate = %f\n",maxerr_idx,maxerr,expf(inp[maxerr_idx]),(float)out[maxerr_idx]);
    // write_half_array_to_file("gold_temp.h", "outG"     , "w", out      , B * T * C);

    //--------------------------------------------------------- cosh
    // half* inp     = (half*)malloc(B * T * C * sizeof(half));
    // half* out     = (half*)malloc(B * T * C * sizeof(half));
    // memcpy(inp, data1h, B * T * C * sizeof(half));
    // half err;
    // half maxerr = half(0);
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
    // write_half_array_to_file("gold_temp.h", "outG"     , "w", out      , B * T * C);

    //--------------------------------------------------------- tanh
    // half* inp     = (half*)malloc(B * T * C * sizeof(half));
    // half* out     = (half*)malloc(B * T * C * sizeof(half));
    // memcpy(inp, data1h, B * T * C * sizeof(half));
    // float err;
    // float maxerr = 0;
    // int maxerr_idx = 0;
    // for (int i = 0; i < B*T*C; i++){
    //     out[i] = fast_tanh(inp[i]);
    //     err = fabsf((float)out[i]-tanhf(inp[i]));
    //     if(err > maxerr){
    //         maxerr = err;
    //         maxerr_idx = i;
    //     }
    // }
    // printf("maxerr[%d] = %f\t precise = %f \t approximate = %f\n",maxerr_idx,maxerr,tanhf(inp[maxerr_idx]),(float)out[maxerr_idx]);
    // write_half_array_to_file("gold_temp.h", "outG"     , "w", out      , B * T * C);

    return 0;
}

