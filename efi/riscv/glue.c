/** @file

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#include "glue.h"
#include "stdatomic_asm.h"
#include <Library/CacheMaintenanceLib.h>

void abort(void)
{
  printf("Abort from 0x%lx!\n", __builtin_return_address(0));
  asm("ebreak");
  while (1);
}

void __riscv_flush_icache(void *start, void *end, unsigned long int flags)
{
  //
  // As of 12/02/2022 this is not implemented yet.
  //
  // InvalidateInstructionCacheRange(start, end - start);
  //
  asm("fence.i");
}

bool __atomic_compare_exchange_1(volatile void *ptr, void *expected, UINT8 desired,
                                 bool weak, int success_memorder,
                                 int failure_memorder)
{
  atomic_compare_exchange_weak_explicit((volatile UINT8 *) ptr,
                                        (UINT8 *) expected, desired,
                                        success_memorder, failure_memorder);

  return true;
}

bool __atomic_compare_exchange_2(volatile void *ptr, void *expected, UINT16 desired,
                                 bool weak, int success_memorder,
                                 int failure_memorder)
{
  atomic_compare_exchange_weak_explicit((volatile UINT16 *) ptr,
                                        (UINT16 *) expected, desired,
                                        success_memorder, failure_memorder);

  return true;
}

UINT8 __atomic_fetch_add_1(volatile void *ptr, UINT8 val, int ordering)
{
  return atomic_fetch_add_explicit((volatile UINT8 *) ptr, val, ordering);
}

UINT16 __atomic_fetch_add_2(volatile void *ptr, UINT16 val, int ordering)
{
  return atomic_fetch_add_explicit((volatile UINT16 *) ptr, val, ordering);
}

UINT32 __atomic_fetch_add_4(volatile void *ptr, UINT32 val, int ordering)
{
  return atomic_fetch_add_explicit((volatile UINT32 *) ptr, val, ordering);
}

UINT64 __atomic_fetch_add_8(volatile void *ptr, UINT64 val, int ordering)
{
  return atomic_fetch_add_explicit((volatile UINT64 *) ptr, val, ordering);
}

UINT8 __atomic_fetch_sub_1(volatile void *ptr, UINT8 val, int ordering)
{
  return atomic_fetch_sub_explicit((volatile UINT8 *) ptr, val, ordering);
}

UINT16 __atomic_fetch_sub_2(volatile void *ptr, UINT16 val, int ordering)
{
  return atomic_fetch_sub_explicit((volatile UINT16 *) ptr, val, ordering);
}

UINT32 __atomic_fetch_sub_4(volatile void *ptr, UINT32 val, int ordering)
{
  return atomic_fetch_sub_explicit((volatile UINT32 *) ptr, val, ordering);
}

UINT64 __atomic_fetch_sub_8(volatile void *ptr, UINT64 val, int ordering)
{
  return atomic_fetch_sub_explicit((volatile UINT64 *) ptr, val, ordering);
}

UINT8 __atomic_fetch_and_1(volatile void *ptr, UINT8 val, int ordering)
{
  return atomic_fetch_and_explicit((volatile UINT8 *) ptr, val, ordering);
}

UINT16 __atomic_fetch_and_2(volatile void *ptr, UINT16 val, int ordering)
{
  return atomic_fetch_and_explicit((volatile UINT16 *) ptr, val, ordering);
}

UINT32 __atomic_fetch_and_4(volatile void *ptr, UINT32 val, int ordering)
{
  return atomic_fetch_and_explicit((volatile UINT32 *) ptr, val, ordering);
}

UINT64 __atomic_fetch_and_8(volatile void *ptr, UINT64 val, int ordering)
{
  return atomic_fetch_and_explicit((volatile UINT64 *) ptr, val, ordering);
}

UINT8 __atomic_fetch_or_1(volatile void *ptr, UINT8 val, int ordering)
{
  return atomic_fetch_or_explicit((volatile UINT8 *) ptr, val, ordering);
}

UINT16 __atomic_fetch_or_2(volatile void *ptr, UINT16 val, int ordering)
{
  return atomic_fetch_or_explicit((volatile UINT16 *) ptr, val, ordering);
}

UINT32 __atomic_fetch_or_4(volatile void *ptr, UINT32 val, int ordering)
{
  return atomic_fetch_or_explicit((volatile UINT32 *) ptr, val, ordering);
}

UINT64 __atomic_fetch_or_8(volatile void *ptr, UINT64 val, int ordering)
{
  return atomic_fetch_or_explicit((volatile UINT64 *) ptr, val, ordering);
}

UINT8 __atomic_fetch_xor_1(volatile void *ptr, UINT8 val, int ordering)
{
  return atomic_fetch_xor_explicit((volatile UINT8 *)ptr, val, ordering);
}

UINT16 __atomic_fetch_xor_2(volatile void *ptr, UINT16 val, int ordering)
{
  return atomic_fetch_xor_explicit((volatile UINT16 *) ptr, val, ordering);
}

UINT32 __atomic_fetch_xor_4(volatile void *ptr, UINT32 val, int ordering)
{
  return atomic_fetch_xor_explicit((volatile UINT32 *) ptr, val, ordering);
}

UINT64 __atomic_fetch_xor_8(volatile void *ptr, UINT64 val, int ordering)
{
  return atomic_fetch_xor_explicit((volatile UINT64 *) ptr, val, ordering);
}
