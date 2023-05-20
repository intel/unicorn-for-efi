/** @file

  Copyright (c) 2023, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#include "glue.h"

#define __cpuid(level, a, b, c, d)                                      \
  __asm__ __volatile__ ("cpuid\n\t"                                     \
                        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)        \
                        : "0" (level))

#define __cpuid_count(level, count, a, b, c, d)                         \
  __asm__ __volatile__ ("cpuid\n\t"                                     \
                        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)        \
                        : "0" (level), "2" (count))

static __inline UINTN
__get_cpuid_max(UINTN Ext, UINTN *Sig)
{
  UINTN Eax;
  UINTN Ebx;
  UINTN Ecx;
  UINTN Edx;

  __cpuid (Ext, Eax, Ebx, Ecx, Edx);
  if (Sig) {
    *Sig = Ebx;
  }

  return Eax;
}

static __inline INTN
__get_cpuid (UINTN Leaf, UINTN *Eax, UINTN *Ebx,
             UINTN *Ecx, UINTN *Edx)
{
  UINTN MaxLeaf = __get_cpuid_max(Leaf & 0x80000000, 0);
  if (MaxLeaf == 0 || MaxLeaf < Leaf) {
    return 0;
  }

  __cpuid(Leaf, *Eax, *Ebx, *Ecx, *Edx);
  return 1;
}
