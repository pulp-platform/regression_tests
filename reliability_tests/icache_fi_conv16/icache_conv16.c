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
/******************************************************************************
 *                                                                            *
 *             Multitherman Lab @ DEI - University of Bologna                 *
 *                     Viale Risorgimento 2 40136                             *
 *                     Bologna - phone 0512092759                             *
 *                                                                            *
 * Engineer:       Francesco Conti - f.conti@unibo.it                         *
 *                                                                            *
 * Project:        CConvNet                                                   *
 * File:           conv16.c                                                   *
 * Description:    16-bit fixed point convolution test                        *
 *                                                                            *
 ******************************************************************************/

#include <pulp.h>
#include <stdint.h>
#include "conv16.h"

__attribute__((section(".heapsram"))) int16_t g_W[FH*FW];
__attribute__((section(".heapsram"))) int16_t g_x[IH*IW];
__attribute__((section(".heapsram"))) int16_t g_y[OH*OW];
__attribute__((section(".heapsram"))) int16_t g_y_in[OH*OW];

int main() {

   if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
 
   int errors = 0;
   int sum = 0;

   // single-threaded "golden" by-the-book convolution
   errors += test_singlethread(&conv16_gold, "sequential convolution");

   // single-threaded loop-unrolled convolution
   errors += test_singlethread(&conv16_unrolled_5x5, "sequential loop-unrolled convolution");

   // single-threaded loop-unrolled pointer-optimized convolution
   errors += test_singlethread(&conv16_unrolled_ptr_5x5, "sequential loop-unrolled pointer-optimized convolution");

   // multi-threaded by-the-book convolution (1 thread per output pixel)
   errors += test_multithread(&conv16_gold_four_coarse, "4-threaded convolution (1 thread per output pixel)");

   // multi-threaded loop-unrolled convolution (1 thread per output pixel)
   errors += test_multithread(&conv16_unrolled_5x5_four_coarse, "4-threaded loop-unrolled convolution (1 thread per output pixel)");

   // multi-threaded loop-unrolled pointer-optimized convolution (1 thread per output pixel)
   errors += test_multithread(&conv16_unrolled_ptr_5x5_four_coarse, "4-threaded loop-unrolled pointer-optimized convolution (1 thread per output pixel)");

   // multi-threaded by-the-book convolution (1 thread per output row)
   errors += test_multithread(&conv16_gold_four_coarsest, "4-threaded convolution (1 thread per output row)");

   // multi-threaded loop-unrolled convolution (1 thread per output row)
   errors += test_multithread(&conv16_unrolled_5x5_four_coarsest, "4-threaded loop-unrolled convolution (1 thread per output row)");

   // multi-threaded loop-unrolled pointer-optimized convolution (1 thread per output row)
   errors += test_multithread(&conv16_unrolled_ptr_5x5_four_coarsest, "4-threaded loop-unrolled pointer-optimized convolution (1 thread per output row)");

   synch_barrier();

   // TODO readout icache errors

   return errors;
}

int test_singlethread(void (*test)(int16_t *, int16_t *, int16_t *, int, int, int, int, int, int, int, int, int), char *str) {
   int errors = 0;
   int sum = 0;

   synch_barrier();

   if(rt_core_id() == 0) {
      load();

      reset_timer(rt_cluster_id());
      start_timer(rt_cluster_id());
      test(g_W, g_x, g_y, IH, IW, FH, FW, OH, OW, 1, 0, 0);
      stop_timer(rt_cluster_id());

      #ifdef CHECK_CHECKSUM
      errors = 0;
      sum = checksum(g_y);
      if(sum != RIGHT_CHECKSUM) {
         #ifndef PULP_SPI
 	 printf("wrong checksum, 0x%08x instead of 0x%08x\n", sum, RIGHT_CHECKSUM);
         #ifndef CHECK_ERROR
         errors += 1;
         #endif
         #endif
         #ifdef CHECK_ERROR
         errors = check(g_y);
         #endif
      }
      #else
      errors = -1;
      #endif

      #ifndef PULP_SPI
      printf("%s, errors=%d, time=%d\n", str, errors, get_time(rt_cluster_id()));
      #endif
      
   }

   return errors;
}

int test_multithread(void (*test)(int16_t *, int16_t *, int16_t *, int, int, int, int, int, int, int, int, int), char *str) {
   int errors = 0;
   int sum = 0;

   if(rt_core_id() == 0) {
      load();
   }
   
   synch_barrier();

   if(rt_core_id() == 0) {
      reset_timer(rt_cluster_id());
      start_timer(rt_cluster_id());
   }
   test(g_W, g_x, g_y, IH, IW, FH, FW, OH, OW, 1, 0, 0);
   if(rt_core_id() == 0) {
      stop_timer(rt_cluster_id());

      #ifdef CHECK_CHECKSUM
      errors = 0;
      sum = checksum(g_y);
      if(sum != RIGHT_CHECKSUM) {
         #ifndef PULP_SPI
         printf("wrong checksum, 0x%08x instead of 0x%08x\n", sum, RIGHT_CHECKSUM);
         #ifndef CHECK_ERROR
         errors += 1;
         #endif
         #endif
         #ifdef CHECK_ERROR
         errors = check(g_y);
         #endif
      }
      #else
      errors = -1;
      #endif

      #ifndef PULP_SPI
      printf("%s, errors=%d, time=%d\n", str, errors, get_time(rt_cluster_id()));
      #endif
      
   }

   return errors;
}

void conv16_gold(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   int i;
   for (i=0; i<oh; i++) {
      int j;
      for (j=0; j<ow; j++) {
         int32_t conv = 0;
         int ui;
         for (ui=0; ui<fh; ui++) {
            int uj;
            for (uj=0; uj<fw; uj++) {
               int m;
               int n;
               m = i-ui+fh-1;
               n = j-uj+fw-1;
               #ifndef IMPRECISE_ASM5
               conv += FIXED_MUL(W[((((a*nif)+b)*fh)+ui)*fw+uj] , x[(((b*h)+m)*w)+n]);
               #else
               conv += W[((((a*nif)+b)*fh)+ui)*fw+uj] * x[(((b*h)+m)*w)+n];
               #endif
            }
         }
         #ifndef IMPRECISE_ASM5
         y[(a*oh+i)*ow+j] = (y[(a*oh+i)*ow+j] + conv);
         #else
         y[(a*oh+i)*ow+j] = (y[(a*oh+i)*ow+j] + (conv >> QF));
         #endif
      }
   }
}

void conv16_unrolled_5x5(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   int i;
   for (i=0; i<oh; i++) {
      int j;
      for (j=0; j<ow; j++) {

         int32_t conv = 0;

         #ifndef IMPRECISE_ASM5

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+0], x[(((b*h)+(i+4-0))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+1], x[(((b*h)+(i+4-0))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+2], x[(((b*h)+(i+4-0))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+3], x[(((b*h)+(i+4-0))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+4], x[(((b*h)+(i+4-0))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+0], x[(((b*h)+(i+4-1))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+1], x[(((b*h)+(i+4-1))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+2], x[(((b*h)+(i+4-1))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+3], x[(((b*h)+(i+4-1))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+4], x[(((b*h)+(i+4-1))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+0], x[(((b*h)+(i+4-2))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+1], x[(((b*h)+(i+4-2))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+2], x[(((b*h)+(i+4-2))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+3], x[(((b*h)+(i+4-2))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+4], x[(((b*h)+(i+4-2))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+0], x[(((b*h)+(i+4-3))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+1], x[(((b*h)+(i+4-3))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+2], x[(((b*h)+(i+4-3))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+3], x[(((b*h)+(i+4-3))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+4], x[(((b*h)+(i+4-3))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+0], x[(((b*h)+(i+4-4))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+1], x[(((b*h)+(i+4-4))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+2], x[(((b*h)+(i+4-4))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+3], x[(((b*h)+(i+4-4))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+4], x[(((b*h)+(i+4-4))*w)+(j+4-4)]);

         y[(a*oh+i)*ow+j] += conv;

         #else

         conv += W[((((a*nif)+b)*5)+0)*5+0] * x[(((b*h)+(i+4-0))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+0)*5+1] * x[(((b*h)+(i+4-0))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+0)*5+2] * x[(((b*h)+(i+4-0))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+0)*5+3] * x[(((b*h)+(i+4-0))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+0)*5+4] * x[(((b*h)+(i+4-0))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+1)*5+0] * x[(((b*h)+(i+4-1))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+1)*5+1] * x[(((b*h)+(i+4-1))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+1)*5+2] * x[(((b*h)+(i+4-1))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+1)*5+3] * x[(((b*h)+(i+4-1))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+1)*5+4] * x[(((b*h)+(i+4-1))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+2)*5+0] * x[(((b*h)+(i+4-2))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+2)*5+1] * x[(((b*h)+(i+4-2))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+2)*5+2] * x[(((b*h)+(i+4-2))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+2)*5+3] * x[(((b*h)+(i+4-2))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+2)*5+4] * x[(((b*h)+(i+4-2))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+3)*5+0] * x[(((b*h)+(i+4-3))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+3)*5+1] * x[(((b*h)+(i+4-3))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+3)*5+2] * x[(((b*h)+(i+4-3))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+3)*5+3] * x[(((b*h)+(i+4-3))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+3)*5+4] * x[(((b*h)+(i+4-3))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+4)*5+0] * x[(((b*h)+(i+4-4))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+4)*5+1] * x[(((b*h)+(i+4-4))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+4)*5+2] * x[(((b*h)+(i+4-4))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+4)*5+3] * x[(((b*h)+(i+4-4))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+4)*5+4] * x[(((b*h)+(i+4-4))*w)+(j+4-4)];

         y[(a*oh+i)*ow+j] += (conv >> QF);

         #endif

      }
   }
}

void conv16_unrolled_ptr_5x5(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   register int i;
   register int j;

   int16_t *y_ptr = y + a*oh*ow;
   int16_t *x_base = x + b*h*w + (fh-1)*w + (fw-1);
   int16_t *W_base = &W[((a*nif)+b)*fh*fw];
   int16_t *W_ptr;
   int16_t *x_ptr;

   for (i=0; i<oh; i++) {
      for (j=0; j<ow; j++) {

         int conv = 0;

         W_ptr = W_base;
         x_ptr = x_base + i*w + j;

         #ifndef IMPRECISE_ASM5

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         *(y_ptr + i*ow+j) += conv;

         #else

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         *(y_ptr + i*ow+j) += conv >> QF;

         #endif

      }
   }

}

void conv16_gold_four_coarse(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   int i;
   register int myid      = rt_core_id();
   register int num_cores = get_core_num();
   // synch_barrier();
   for (i=0; i<oh; i++) {
      int j;
      for (j=myid; j<ow; j+=num_cores) {
         int ui;
         int32_t conv = 0;
         for (ui=0; ui<fh; ui++) {
            int uj;
            for (uj=0; uj<fw; uj++) {
               int m;
               int n;
               m = i-ui+fh-1;
               n = j-uj+fw-1;
               #ifndef IMPRECISE_ASM5
               conv += FIXED_MUL(W[((((a*nif)+b)*fh)+ui)*fw+uj] , x[(((b*h)+m)*w)+n]);
               #else
               conv += W[((((a*nif)+b)*fh)+ui)*fw+uj] * x[(((b*h)+m)*w)+n];
               #endif
            }
         }
         #ifndef IMPRECISE_ASM5
         y[(a*oh+i)*ow+j] = (y[(a*oh+i)*ow+j] + conv);
         #else
         y[(a*oh+i)*ow+j] = (y[(a*oh+i)*ow+j] + (conv >> QF));
         #endif
      }
   }
   synch_barrier();
}

void conv16_gold_four_coarsest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   int i;
   register int myid      = rt_core_id();
   register int num_cores = get_core_num();
   // synch_barrier();
   for (i=myid; i<oh; i+=num_cores) {
      int j;
      for (j=0; j<ow; j++) {
         int ui;
         int32_t conv = 0;
         for (ui=0; ui<fh; ui++) {
            int uj;
            for (uj=0; uj<fw; uj++) {
               int m;
               int n;
               m = i-ui+fh-1;
               n = j-uj+fw-1;
               #ifndef IMPRECISE_ASM5
               conv += FIXED_MUL(W[((((a*nif)+b)*fh)+ui)*fw+uj] , x[(((b*h)+m)*w)+n]);
               #else
               conv += W[((((a*nif)+b)*fh)+ui)*fw+uj] * x[(((b*h)+m)*w)+n];
               #endif
            }
         }
         #ifndef IMPRECISE_ASM5
         y[(a*oh+i)*ow+j] = (y[(a*oh+i)*ow+j] + conv);
         #else
         y[(a*oh+i)*ow+j] = (y[(a*oh+i)*ow+j] + (conv >> QF));
         #endif
      }
   }
   synch_barrier();
}

void conv16_unrolled_5x5_four_coarse(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   int i;
   register int myid      = rt_core_id();
   register int num_cores = get_core_num();
   // synch_barrier();
   for (i=0; i<oh; i++) {
      int j;
      for (j=myid; j<ow; j+=num_cores) {

         int32_t conv = 0;

         #ifndef IMPRECISE_ASM5

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+0], x[(((b*h)+(i+4-0))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+1], x[(((b*h)+(i+4-0))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+2], x[(((b*h)+(i+4-0))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+3], x[(((b*h)+(i+4-0))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+4], x[(((b*h)+(i+4-0))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+0], x[(((b*h)+(i+4-1))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+1], x[(((b*h)+(i+4-1))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+2], x[(((b*h)+(i+4-1))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+3], x[(((b*h)+(i+4-1))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+4], x[(((b*h)+(i+4-1))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+0], x[(((b*h)+(i+4-2))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+1], x[(((b*h)+(i+4-2))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+2], x[(((b*h)+(i+4-2))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+3], x[(((b*h)+(i+4-2))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+4], x[(((b*h)+(i+4-2))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+0], x[(((b*h)+(i+4-3))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+1], x[(((b*h)+(i+4-3))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+2], x[(((b*h)+(i+4-3))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+3], x[(((b*h)+(i+4-3))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+4], x[(((b*h)+(i+4-3))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+0], x[(((b*h)+(i+4-4))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+1], x[(((b*h)+(i+4-4))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+2], x[(((b*h)+(i+4-4))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+3], x[(((b*h)+(i+4-4))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+4], x[(((b*h)+(i+4-4))*w)+(j+4-4)]);

         y[(a*oh+i)*ow+j] += conv; // because i'm using 32-bit int

         #else

         conv += W[((((a*nif)+b)*5)+0)*5+0] * x[(((b*h)+(i+4-0))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+0)*5+1] * x[(((b*h)+(i+4-0))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+0)*5+2] * x[(((b*h)+(i+4-0))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+0)*5+3] * x[(((b*h)+(i+4-0))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+0)*5+4] * x[(((b*h)+(i+4-0))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+1)*5+0] * x[(((b*h)+(i+4-1))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+1)*5+1] * x[(((b*h)+(i+4-1))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+1)*5+2] * x[(((b*h)+(i+4-1))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+1)*5+3] * x[(((b*h)+(i+4-1))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+1)*5+4] * x[(((b*h)+(i+4-1))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+2)*5+0] * x[(((b*h)+(i+4-2))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+2)*5+1] * x[(((b*h)+(i+4-2))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+2)*5+2] * x[(((b*h)+(i+4-2))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+2)*5+3] * x[(((b*h)+(i+4-2))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+2)*5+4] * x[(((b*h)+(i+4-2))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+3)*5+0] * x[(((b*h)+(i+4-3))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+3)*5+1] * x[(((b*h)+(i+4-3))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+3)*5+2] * x[(((b*h)+(i+4-3))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+3)*5+3] * x[(((b*h)+(i+4-3))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+3)*5+4] * x[(((b*h)+(i+4-3))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+4)*5+0] * x[(((b*h)+(i+4-4))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+4)*5+1] * x[(((b*h)+(i+4-4))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+4)*5+2] * x[(((b*h)+(i+4-4))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+4)*5+3] * x[(((b*h)+(i+4-4))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+4)*5+4] * x[(((b*h)+(i+4-4))*w)+(j+4-4)];

         y[(a*oh+i)*ow+j] += (conv >> QF); // because i'm using 32-bit int

         #endif

      }
   }
   synch_barrier();
}

void conv16_unrolled_5x5_four_coarsest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   int i;
   register int myid      = rt_core_id();
   register int num_cores = get_core_num();
   // synch_barrier();
   for (i=myid; i<oh; i+=num_cores) {
      int j;
      for (j=0; j<ow; j++) {

         int32_t conv = 0;

         #ifndef IMPRECISE_ASM5

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+0], x[(((b*h)+(i+4-0))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+1], x[(((b*h)+(i+4-0))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+2], x[(((b*h)+(i+4-0))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+3], x[(((b*h)+(i+4-0))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+0)*5+4], x[(((b*h)+(i+4-0))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+0], x[(((b*h)+(i+4-1))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+1], x[(((b*h)+(i+4-1))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+2], x[(((b*h)+(i+4-1))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+3], x[(((b*h)+(i+4-1))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+1)*5+4], x[(((b*h)+(i+4-1))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+0], x[(((b*h)+(i+4-2))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+1], x[(((b*h)+(i+4-2))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+2], x[(((b*h)+(i+4-2))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+3], x[(((b*h)+(i+4-2))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+2)*5+4], x[(((b*h)+(i+4-2))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+0], x[(((b*h)+(i+4-3))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+1], x[(((b*h)+(i+4-3))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+2], x[(((b*h)+(i+4-3))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+3], x[(((b*h)+(i+4-3))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+3)*5+4], x[(((b*h)+(i+4-3))*w)+(j+4-4)]);

         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+0], x[(((b*h)+(i+4-4))*w)+(j+4-0)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+1], x[(((b*h)+(i+4-4))*w)+(j+4-1)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+2], x[(((b*h)+(i+4-4))*w)+(j+4-2)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+3], x[(((b*h)+(i+4-4))*w)+(j+4-3)]);
         conv += FIXED_MUL(W[((((a*nif)+b)*5)+4)*5+4], x[(((b*h)+(i+4-4))*w)+(j+4-4)]);

         y[(a*oh+i)*ow+j] += conv; // because i'm using 32-bit int

         #else

         conv += W[((((a*nif)+b)*5)+0)*5+0] * x[(((b*h)+(i+4-0))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+0)*5+1] * x[(((b*h)+(i+4-0))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+0)*5+2] * x[(((b*h)+(i+4-0))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+0)*5+3] * x[(((b*h)+(i+4-0))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+0)*5+4] * x[(((b*h)+(i+4-0))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+1)*5+0] * x[(((b*h)+(i+4-1))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+1)*5+1] * x[(((b*h)+(i+4-1))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+1)*5+2] * x[(((b*h)+(i+4-1))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+1)*5+3] * x[(((b*h)+(i+4-1))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+1)*5+4] * x[(((b*h)+(i+4-1))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+2)*5+0] * x[(((b*h)+(i+4-2))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+2)*5+1] * x[(((b*h)+(i+4-2))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+2)*5+2] * x[(((b*h)+(i+4-2))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+2)*5+3] * x[(((b*h)+(i+4-2))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+2)*5+4] * x[(((b*h)+(i+4-2))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+3)*5+0] * x[(((b*h)+(i+4-3))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+3)*5+1] * x[(((b*h)+(i+4-3))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+3)*5+2] * x[(((b*h)+(i+4-3))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+3)*5+3] * x[(((b*h)+(i+4-3))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+3)*5+4] * x[(((b*h)+(i+4-3))*w)+(j+4-4)];

         conv += W[((((a*nif)+b)*5)+4)*5+0] * x[(((b*h)+(i+4-4))*w)+(j+4-0)];
         conv += W[((((a*nif)+b)*5)+4)*5+1] * x[(((b*h)+(i+4-4))*w)+(j+4-1)];
         conv += W[((((a*nif)+b)*5)+4)*5+2] * x[(((b*h)+(i+4-4))*w)+(j+4-2)];
         conv += W[((((a*nif)+b)*5)+4)*5+3] * x[(((b*h)+(i+4-4))*w)+(j+4-3)];
         conv += W[((((a*nif)+b)*5)+4)*5+4] * x[(((b*h)+(i+4-4))*w)+(j+4-4)];

         y[(a*oh+i)*ow+j] += (conv >> QF); // because i'm using 32-bit int

         #endif

      }
   }
   synch_barrier();
}

void conv16_unrolled_ptr_5x5_four_coarse(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   register int i;
   register int j;
   register int myid      = rt_core_id();
   register int num_cores = get_core_num();
   int16_t *W_ptr;
   int16_t *x_ptr;
   int16_t *y_ptr = y + a*oh*ow;
   int16_t *x_base = x + b*h*w + (fh-1)*w + (fw-1);
   int16_t *W_base = &W[((a*nif)+b)*fh*fw];
   
   // synch_barrier();

   for (i=0; i<oh; i++) {
      for (j=myid; j<ow; j+=num_cores) {

         int conv = 0;

         W_ptr = W_base;
         x_ptr = x_base + i*w + j;

         #ifndef IMPRECISE_ASM5

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         *(y_ptr + i*ow+j) += conv;

         #else

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         *(y_ptr + i*ow+j) += conv >> QF;

         #endif

      }
   }

   synch_barrier();
}

void conv16_unrolled_ptr_5x5_four_coarsest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   // register int i;
   // register int j;
   // register int myid = rt_core_id();
   // int16_t *W_ptr;
   // int16_t *x_ptr;
   int16_t *y_ptr = y + a*oh*ow;
   int16_t *x_base = x + b*h*w + (fh-1)*w + (fw-1);
   int16_t *W_base = &W[((a*nif)+b)*fh*fw];

   register int myid      = rt_core_id();
   register int num_cores = get_core_num();

   register int i;
   register int j;
   int16_t *W_ptr;
   int16_t *x_ptr;

   for (i=myid; i<oh; i+=num_cores) {
      for (j=0; j<ow; j++) {

         int conv = 0;

         W_ptr = W_base;
         x_ptr = x_base + i*w + j;

         #ifndef IMPRECISE_ASM5

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         conv += FIXED_MUL(*W_ptr++, *x_ptr--);
         x_ptr -= w-5;

         *(y_ptr + i*ow+j) += conv;

         #else

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         conv += *W_ptr++ * *x_ptr--;
         x_ptr -= w-5;

         *(y_ptr + i*ow+j) += conv >> QF;

         #endif

      }
   }

   synch_barrier();

}

#ifndef __GCC__
#ifndef __riscv__
void conv16_asm_mul_unrolled_5x5_four_coarsest(int16_t *__restrict__ W, int16_t *__restrict__ x, int16_t *__restrict__ y, int h, int w, int fh, int fw, int oh, int ow, int nif, int a, int b) {
   register int i;
   register int j;
   register int myid      = rt_core_id();
   register int num_cores = get_core_num();
   register int16_t *W_ptr;
   register int16_t *x_ptr;
   int16_t *y_ptr = y + a*oh*ow;
   int16_t *x_base = x + b*h*w + (fh-1)*w + (fw-1);
   int16_t *W_base = &W[((a*nif)+b)*fh*fw];
   for (i=myid; i<oh; i+=num_cores) {
      int j;
      for (j=0; j<ow; j++) {
         W_ptr = W_base;
         x_ptr = x_base + i*w + j;
         int32_t conv = 0;
         int ui;
         for (ui=0; ui<fh; ui++) {

            #ifndef IMPRECISE_ASM5
            FIXED_MUL_ASM5_PRECISE(W_ptr,x_ptr,conv);
            #else
            register int32_t conv_int = conv;
            FIXED_MUL_ASM5_IMPRECISE(W_ptr,x_ptr,conv_int);
            conv = conv_int;
            #endif

            x_ptr -= w-fw+5;
            W_ptr += 5;

         }
         y[(a*oh+i)*ow+j] = (y[(a*oh+i)*ow+j] + conv) & 0x0000ffff; // because i'm using 32-bit int
      }
   }
   synch_barrier();
}
#endif
#endif

void load() {
   int i;
   for(i=0; i<FH*FW; i++) {
      g_W[i] = (int16_t) 0x2000;
   }
   for(i=0; i<IH*IW; i++) {
      g_x[i] = (int16_t) (i % 0x2000);
   }
   for(i=0; i<OH*OW; i++) {
      g_y[i] = (int16_t) (i % 0x2000);
      g_y_in[i] = g_y[i];
      // g_y_in[i] = (int16_t) (i % 0x2000);
      // g_y[i] = 0;
   }
}

void printW() {
   int i;
   for(i=0; i<FH*FW; i++)
      printf("%04x\n", g_W[i]);
}

void printX() {
   int i;
   for(i=0; i<IH*IW; i++)
      printf("%04x\n", g_x[i]);
}

int check(int16_t *y) {
   int i;
   int errors = 0;
   for(i=0; i<OH*OW; i++) {
      int err = ((y[i]!=correct_yout[i]) ? 1 : 0);
      errors += err;
      #ifndef PULP_SPI
      if(err)
         printf("error: y_out=%04x instead of %04x! y_in=%04x\n", y[i], correct_yout[i], g_y_in[i], 0);
      #endif
   }
   return errors;
}

int checksum(int16_t *y) {
   int sum = 0;
   int i;
   for(i=0; i<OH*OW; i++)
      sum += y[i];
   return sum;
}
