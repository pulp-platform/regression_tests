// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.


// This testbench checks the basic functionality of complex instructions for GAP9 on

#include <stdio.h>
#include "pulp.h"
#include "number_of_stimuli.h"
#include "pv_complex_stimuli_div8.h"
#include "pv_complex_stimuli_div4.h"
#include "pv_complex_stimuli_div2.h"
#include "pv_complex_stimuli.h"
#include "cplxbitman_stimuli.h"
#include "cplxbitrev_stimuli.h"
#include "pv_cplxmul_real_stimuli.h"
#include "pv_cplxmul_real_stimuli_div2.h"
#include "pv_cplxmul_real_stimuli_div4.h"
#include "pv_cplxmul_real_stimuli_div8.h"
#include "pv_cplxmul_img_stimuli.h"
#include "pv_cplxmul_img_stimuli_div2.h"
#include "pv_cplxmul_img_stimuli_div4.h"
#include "pv_cplxmul_img_stimuli_div8.h"


void check_pv_cplxmul_real(testresult_t *result, void (*start)(), void (*stop)());
void check_pv_cplxmul_img(testresult_t *result, void (*start)(), void (*stop)());
void check_pv_complex (testresult_t *result, void (*start)(), void (*stop)());
void check_pv_bitman(testresult_t *result, void (*start)(), void (*stop)());

int tmp_result[N];

testcase_t testcases[] = {
  { .name = "check_pv_cplxmul_real"       , .test = check_pv_cplxmul_real     },
  { .name = "check_pv_cplxmul_img"        , .test = check_pv_cplxmul_img      },
  { .name = "check_pv_complex"          , .test = check_pv_complex          },
  { .name = "check_pv_bitman"           , .test = check_pv_bitman           },
  {0, 0}
};

int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if(get_core_id() == 0) {
    return run_suite(testcases);
  }

  return 0;
}

//################################################################################
//# T E S T    check_pv_cplxmul_real
//################################################################################

void check_pv_cplxmul_real(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check pv.cplxmul.h.r
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxmul.h.r %[c], %[a], %[b]\n"
                  : [c] "+r" (cplxmul_opCr_[i])
                  : [a] "r"  (cplxmul_opAr_[i]), [b] "r" (cplxmul_opBr_[i]));

    check_uint32(result, "pv.cplxmul.h.r", cplxmul_opCr_[i],  cplxmul_opCResr_[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.cplxmul.h.r.div2
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxmul.h.r.div2 %[c], %[a], %[b]\n"
                  : [c] "+r" (cplxmul_opCr_div2[i])
                  : [a] "r"  (cplxmul_opAr_div2[i]), [b] "r" (cplxmul_opBr_div2[i]));

    check_uint32(result, "pv.cplxmul.h.r.div2", cplxmul_opCr_div2[i],  cplxmul_opCResr_div2[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.cplxmul.h.r.div4
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxmul.h.r.div4 %[c], %[a], %[b]\n"
                  : [c] "+r" (cplxmul_opCr_div4[i])
                  : [a] "r"  (cplxmul_opAr_div4[i]), [b] "r" (cplxmul_opBr_div4[i]));

    check_uint32(result, "pv.cplxmul.h.r.div4", cplxmul_opCr_div4[i],  cplxmul_opCResr_div4[i]);
  }


  //-----------------------------------------------------------------
  // Check pv.cplxmul.h.r.div8
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxmul.h.r.div8 %[c], %[a], %[b]\n"
                  : [c] "+r" (cplxmul_opCr_div8[i])
                  : [a] "r"  (cplxmul_opAr_div8[i]), [b] "r" (cplxmul_opBr_div8[i]));

    check_uint32(result, "pv.cplxmul.h.r.div8", cplxmul_opCr_div8[i],  cplxmul_opCResr_div8[i]);
  }

}

//################################################################################
//# T E S T    check_pv_cplxmul_img
//################################################################################

void check_pv_cplxmul_img(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check pv.cplxmul.h.i
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxmul.h.i %[c], %[a], %[b]\n"
                  : [c] "+r" (cplxmul_opCi_[i])
                  : [a] "r"  (cplxmul_opAi_[i]), [b] "r" (cplxmul_opBi_[i]));

    check_uint32(result, "pv.cplxmul.h.i", cplxmul_opCi_[i],  cplxmul_opCResi_[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.cplxmul.h.i.div2
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxmul.h.i.div2 %[c], %[a], %[b]\n"
                  : [c] "+r" (cplxmul_opCi_div2[i])
                  : [a] "r"  (cplxmul_opAi_div2[i]), [b] "r" (cplxmul_opBi_div2[i]));

    check_uint32(result, "pv.cplxmul.h.i.div2", cplxmul_opCi_div2[i], cplxmul_opCResi_div2[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.cplxmul.h.i.div4
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxmul.h.i.div4 %[c], %[a], %[b]\n"
                  : [c] "+r" (cplxmul_opCi_div4[i])
                  : [a] "r"  (cplxmul_opAi_div4[i]), [b] "r" (cplxmul_opBi_div4[i]));

    check_uint32(result, "pv.cplxmul.h.i.div4", cplxmul_opCi_div4[i], cplxmul_opCResi_div4[i]);
  }


  //-----------------------------------------------------------------
  // Check pv.cplxmul.h.i.div8
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxmul.h.i.div8 %[c], %[a], %[b]\n"
                  : [c] "+r" (cplxmul_opCi_div8[i])
                  : [a] "r"  (cplxmul_opAi_div8[i]), [b] "r" (cplxmul_opBi_div8[i]));

    check_uint32(result, "pv.cplxmul.h.i.div8", cplxmul_opCi_div8[i], cplxmul_opCResi_div8[i]);
  }

}


//################################################################################
//# T E S T    check_pv_complex
//################################################################################

void check_pv_complex(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check pv.subrotmj.h
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.subrotmj.h %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opA[i]), [b] "r" (cplx_opB[i]));

    check_uint32(result, "pv.subrotmj.h", tmp_result[i],  subrotmj_opC[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.subrotmj.h.div2
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.subrotmj.h.div2 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv2[i]), [b] "r" (cplx_opBdiv2[i]));

    check_uint32(result, "pv.subrotmj.h.div2", tmp_result[i],  subrotmj_opCdiv2[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.subrotmj.h.div4
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.subrotmj.h.div4 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv4[i]), [b] "r" (cplx_opBdiv4[i]));

    check_uint32(result, "pv.subrotmj.h.div4", tmp_result[i],  subrotmj_opCdiv4[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.subrotmj.h.div8
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.subrotmj.h.div8 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv8[i]), [b] "r" (cplx_opBdiv8[i]));

    check_uint32(result, "pv.subrotmj.h.div8", tmp_result[i],  subrotmj_opCdiv8[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.cplxconj.h
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.cplxconj.h %[c], %[a]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opA[i]));

    check_uint32(result, "pv.cplxconj.h", tmp_result[i],  cplxconj_opC[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.add.h.div2 equivalent to pv.avg
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.add.h.div2 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv2[i]), [b] "r" (cplx_opBdiv2[i]));

    check_uint32(result, "pv.add.h.div2", tmp_result[i],  cplxadd_opCdiv2[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.add.h.div4
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.add.h.div4 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv4[i]), [b] "r" (cplx_opBdiv4[i]));

    check_uint32(result, "pv.add.h.div4", tmp_result[i],  cplxadd_opCdiv4[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.add.h.div8
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.add.h.div8 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv8[i]), [b] "r" (cplx_opBdiv8[i]));

    check_uint32(result, "pv.add.h.div8", tmp_result[i],  cplxadd_opCdiv8[i]);
  }


  //-----------------------------------------------------------------
  // Check pv.sub.h.div2
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.sub.h.div2 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv2[i]), [b] "r" (cplx_opBdiv2[i]));

    check_uint32(result, "pv.sub.h.div2", tmp_result[i],  cplxsub_opCdiv2[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.sub.h.div4
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.sub.h.div4 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv4[i]), [b] "r" (cplx_opBdiv4[i]));

    check_uint32(result, "pv.sub.h.div4", tmp_result[i],  cplxsub_opCdiv4[i]);
  }

  //-----------------------------------------------------------------
  // Check pv.sub.h.div8
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.sub.h.div8 %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplx_opAdiv8[i]), [b] "r" (cplx_opBdiv8[i]));

    check_uint32(result, "pv.sub.h.div8", tmp_result[i],  cplxsub_opCdiv8[i]);
  }

}

//################################################################################
//# T E S T    check_pv_bitman
//################################################################################

void check_pv_bitman(testresult_t *result, void (*start)(), void (*stop)()) {
  unsigned int i;
  unsigned int res;

  //-----------------------------------------------------------------
  // Check pv.subrotmj.h
  //-----------------------------------------------------------------

  for(i=0;i<N;i++)
  {
    asm volatile ("pv.pack.h.h %[c], %[a], %[b]\n"
                  : [c] "=r" (tmp_result[i])
                  : [a] "r"  (cplxbitman_opA[i]), [b] "r" (cplx_opB[i]));

    check_uint32(result, "pv.pack.h.h", tmp_result[i],  cplxpack_opC[i]);
  }


  #include "testBitReverse_radix2.c"

  for(i=0;i<NumberOfStimuli;i++)
    check_uint32(result, "p.bitrev_radix2", tmp_result[i],  cplxbitrev_opC_radix2[i]);

  #include "testBitReverse_radix4.c"

  for(i=0;i<NumberOfStimuli;i++)
    check_uint32(result, "p.bitrev_radix4", tmp_result[i],  cplxbitrev_opC_radix4[i]);

  #include "testBitReverse_radix8.c"

  for(i=0;i<NumberOfStimuli;i++)
    check_uint32(result, "p.bitrev_radix8", tmp_result[i],  cplxbitrev_opC_radix8[i]);

}