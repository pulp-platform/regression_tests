// Copyright 2018 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

// This testbench checks the basic functionality of:
//
//l.mac
//l.msu
//l.mul
//l.mmul
//
//l.macs
//l.macu
//l.macus
//l.muls
//l.muluu
//l.mulus
//l.msus
//l.msuu
//l.msuus
//l.mmuls
//l.mmulu
//l.mmulus
//l.machls
//l.machlu
//l.machlus
//l.machlsu
//l.mulhls
//l.mulhlu
//l.mulhlus
//l.mulhlsu
//l.msuhls
//l.msuhlu
//l.msuhlus
//l.msuhlsu
//l.mmulhls
//l.mmulhlu
//l.mmulhlus
//l.mmulhlsu
//l.machhs
//l.machhu
//l.machhus
//l.mulhhs
//l.mulhhu
//l.mulhhus
//l.msuhhs
//l.msuhhu
//l.msuhhus
//l.mmulhhs
//l.mmulhhu
//l.mmulhhus

#include "pulp.h"
#include <stdio.h>
#include "riscv_test.h"

#define MAC      "p.mac"
#define MSU      "p.msu"
#define MACS     "p.macs"
#define MACU     "p.macu"
#define MULS     "p.muls"
#define MULUU    "p.mulu"
#define MACHHS   "p.machhs"
#define MACHHU   "p.machhu"
#define MULHHS   "p.mulhhs"
#define MULHHU   "p.mulhhu"

void check_mac(void);
void check_mac_subword(void);
void check_mul_subword(void);

int main()
{
#ifdef USE_CLUSTER
  if (rt_cluster_id() != 0)
    return bench_cluster_forward(0);
#endif

  if(get_core_id() == 0) {
    test_init();

    check_mac();
    check_mac_subword();

    test_report();

    if (test_get_num_errors() == 0)
    {
    }
    else
    {
	return -1;
    }
  }

  return 0;
}

#include "testMAC3_stimuli.h"

#define util_check_mac(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    : [c] "+r" (prefix ## _act[i]) \
                    : [a] "r"  (prefix ## _a[i]), \
                      [b] "r" (prefix ## _b[i])); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
    }

#define util_check_mac_flags(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile (asm_str " %[c], %[a], %[b]\n" \
                    "l.mfspr %[spr], r0, 0x11\n" \
                    : [c] "+r"   (prefix ## _act[i]), \
                      [spr] "+r" (spr) \
                    : [a] "r"    (prefix ## _a[i]), \
                      [b] "r"    (prefix ## _b[i])); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
      test_check_overflow(asm_str, spr, prefix ## _flags[i]); \
      test_check_carry(asm_str, spr, prefix ## _flags[i]); \
    }


#define util_check_mac_c(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile ("l.addi %[tmp], %[cy], 0x1\n" \
                    asm_str " %[c], %[a], %[b]\n" \
                    : [c]   "+r" (prefix ## _act[i]), \
                      [tmp] "+&r" (tmp) \
                    : [a]   "r"  (prefix ## _a[i]), \
                      [b]   "r"  (prefix ## _b[i]), \
                      [cy]  "r"  (0xFFFFFFFF)); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
    }

#define util_check_mac_flags_c(asm_str, i, prefix) \
    for(i = 0; i < (sizeof(prefix ## _a)/4); i++) { \
      asm volatile ("l.addi %[tmp], %[cy], 0x1\n" \
                    asm_str " %[c], %[a], %[b]\n" \
                    "l.mfspr %[spr], r0, 0x11\n" \
                    : [c]   "+r" (prefix ## _act[i]), \
                      [tmp] "+&r" (tmp), \
                      [spr] "+r" (spr) \
                    : [a]   "r"  (prefix ## _a[i]), \
                      [b]   "r"  (prefix ## _b[i]), \
                      [cy]  "r"  (0xFFFFFFFF)); \
      test_check(asm_str, prefix ## _act[i], prefix ## _exp[i]); \
      test_check_overflow(asm_str, spr, prefix ## _flags[i]); \
      test_check_carry(asm_str, spr, prefix ## _flags[i]); \
    }



void check_mac(void) {
  unsigned int i;
  unsigned int tmp;
  unsigned int spr;

  //-----------------------------------------------------------------
  // Check l.mac l.msu l.mul l.mmul
  //-----------------------------------------------------------------

  util_check_mac      (MAC,  i, g_mac);
  util_check_mac      (MSU,  i, g_msu);
  #ifdef MUL
  util_check_mac      (MUL,  i, g_mul);
  #endif
  #ifdef MMUL
  util_check_mac      (MMUL, i, g_mmul);
  #endif


}

void check_mac_subword(void) {
  unsigned int i;
  unsigned int tmp;
  unsigned int spr;

  //-----------------------------------------------------------------
  // Check l.mac with subword selection, NO carry in
  //-----------------------------------------------------------------
    util_check_mac (MACS     , i, g_macs     );
    util_check_mac (MACU     , i, g_macu     );
    #ifdef MACUS
    util_check_mac (MACUS    , i, g_macus    );
    #endif

    util_check_mac (MULS    , i, g_muls     );
    util_check_mac (MULUU    , i, g_muluu    );
    #ifdef MULUS
    util_check_mac (MULUS    , i, g_mulus    );
    #endif

    #ifdef MSUS
    util_check_mac (MSUS     , i, g_msus     );
    #endif
    #ifdef MSUU
    util_check_mac (MSUU     , i, g_msuu     );
    #endif
    #ifdef MSUUS
    util_check_mac (MSUUS    , i, g_msuus    );
    #endif

    #ifdef MMULS
    util_check_mac (MMULS    , i, g_mmuls    );
    #endif
    #ifdef MMULU
    util_check_mac (MMULU    , i, g_mmulu    );
    #endif
    #ifdef MMULUS
    util_check_mac (MMULUS   , i, g_mmulus   );
    #endif

    #ifdef MACHLS
    util_check_mac (MACHLS   , i, g_machls   );
    #endif
    #ifdef MACHLU
    util_check_mac (MACHLU   , i, g_machlu   );
    #endif
    #ifdef MACHLUS
    util_check_mac (MACHLUS  , i, g_machlus  );
    #endif
    #ifdef MACHLSU
    util_check_mac (MACHLSU  , i, g_machlsu  );
    #endif

    #ifdef MULHLS
    util_check_mac (MULHLS   , i, g_mulhls   );
    #endif
    #ifdef MULHLU
    util_check_mac (MULHLU   , i, g_mulhlu   );
    #endif
    #ifdef MULHLUS
    util_check_mac (MULHLUS  , i, g_mulhlus  );
    #endif
    #ifdef MULHLSU
    util_check_mac (MULHLSU  , i, g_mulhlsu  );
    #endif

    #ifdef MSUHLS
    util_check_mac (MSUHLS   , i, g_msuhls   );
    #endif
    #ifdef MSUHLU
    util_check_mac (MSUHLU   , i, g_msuhlu   );
    #endif
    #ifdef MSUHLUS
    util_check_mac (MSUHLUS  , i, g_msuhlus  );
    #endif
    #ifdef MSUHLSU
    util_check_mac (MSUHLSU  , i, g_msuhlsu  );
    #endif

    #ifdef MMULHLS
    util_check_mac (MMULHLS   , i, g_mmulhls  );
    #endif
    #ifdef MMULHLU
    util_check_mac (MMULHLU   , i, g_mmulhlu  );
    #endif
    #ifdef MMULHLUS
    util_check_mac (MMULHLUS , i, g_mmulhlus );
    #endif
    #ifdef MMULHLSU
    util_check_mac (MMULHLSU , i, g_mmulhlsu );
    #endif

    util_check_mac (MACHHS   , i, g_machhs   );
    util_check_mac (MACHHU   , i, g_machhu   );
    #ifdef MACHHUS
    util_check_mac (MACHHUS  , i, g_machhus  );
    #endif

    util_check_mac (MULHHS   , i, g_mulhhs   );
    util_check_mac (MULHHU   , i, g_mulhhu   );
    #ifdef MULHHUS
    util_check_mac (MULHHUS  , i, g_mulhhus  );
    #endif

    #ifdef MSUHHS
    util_check_mac (MSUHHS   , i, g_msuhhs   );
    #endif
    #ifdef MSUHHU
    util_check_mac (MSUHHU   , i, g_msuhhu   );
    #endif
    #ifdef MSUHHUS
    util_check_mac (MSUHHUS  , i, g_msuhhus  );
    #endif

    #ifdef MMULHHS
    util_check_mac (MMULHHS  , i, g_mmulhhs  );
    #endif
    #ifdef MMULHHU
    util_check_mac (MMULHHU  , i, g_mmulhhu  );
    #endif
    #ifdef MMULHHUS
    util_check_mac (MMULHHUS , i, g_mmulhhus );
    #endif

}

