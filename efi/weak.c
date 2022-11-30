/** @file

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#include "glue.h"

#define WEAK __attribute__ ((__weak__))

#define ARCHES \
  ARCH(m68k) \
  ARCH(x86) \
  ARCH(arm) \
  ARCH(arm64) \
  ARCH(mips) \
  ARCH(mipsel) \
  ARCH(mips64) \
  ARCH(mips64el) \
  ARCH(sparc) \
  ARCH(sparc64) \
  ARCH(ppc) \
  ARCH(ppc64) \
  ARCH(riscv32) \
  ARCH(riscv64)	\
  ARCH(s390) \
  ARCH(tricore)

struct uc_struct;

#define ARCH(x) WEAK void x##_uc_init(struct uc_struct *uc) \
  { printf("Unimplemented %s!\n", __FUNCTION__); abort();  }
ARCHES
#undef ARCH

#define ARCH(x) WEAK int x##_context_reg_read(struct uc_struct *uc, \
  unsigned int *regs, void **vals, int count) \
  { printf("Unimplemented %s!\n", __FUNCTION__); abort();  return 0; }
ARCHES
#undef ARCH

#define ARCH(x) WEAK int x##_context_reg_write(struct uc_struct *uc, \
  unsigned int *regs, void *const *vals, int count) \
  { printf("Unimplemented %s!\n", __FUNCTION__); abort();  return 0; }
ARCHES
#undef ARCH
