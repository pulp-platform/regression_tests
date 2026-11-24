#include "config.h"
#include "pulp.h"

// libgcc soft-float helpers for printing half-precision values. Only the RI5CY
// toolchain has float16/float16alt and the fcvt.s.ah encoding; on CORE-V we can
// do FP16 via _Float16 + fcvt.s.h, but FP16ALT has no equivalent instruction.
#ifdef __cv32e40p__

#if defined(__riscv_zhinx) || defined(__riscv_zfh)
double __extendhfdf2(float16 value)
{
  float result;
  __asm__ __volatile__ ("fcvt.s.h %0, %1": "=f"(result): "f"(value) :);
  return (double) result;
}
#endif

#else

double __extendohfdf2(float16alt value)
{
  float result;
  __asm__ __volatile__ ("fcvt.s.ah %0, %1": "=f"(result): "f"(value) :);
  return (double) result;
}

double __extendhfdf2(float16 value)
{
  float result;
  __asm__ __volatile__ ("fcvt.s.h %0, %1": "=f"(result): "f"(value) :);
  return (double) result;
}

#endif
