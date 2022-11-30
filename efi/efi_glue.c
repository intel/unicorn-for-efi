/** @file

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "glue.h"

int64_t efi_get_timer_ticks(void)
{
  int64_t r = GetPerformanceCounter();

  return r & MAX_INT64;
}

void efi_get_g_rand_seed(UINT32 seed[4])
{
  seed[0] = (UINT32) GetPerformanceCounter();
  seed[1] = (UINT32) (GetPerformanceCounter() >> 32);
  seed[2] = (UINT32) (UINTN) &seed;
  seed[3] = (UINT32) ((UINTN) (&seed) >> 32);
}

void *efi_alloc_code_pages(size_t size)
{
  EFI_STATUS Status;
  EFI_PHYSICAL_ADDRESS Alloc;

  Status = gBS->AllocatePages (AllocateAnyPages, EfiBootServicesCode, EFI_SIZE_TO_PAGES (size), &Alloc);
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  return (void *) Alloc;
}

void efi_free_code_pages(void *p, size_t size)
{
  FreePages (p, EFI_SIZE_TO_PAGES (size));
}

int64_t efi_get_timer_ns(void)
{
  UINT64 ticks = GetPerformanceCounter();

  return GetTimeInNanoSecond(ticks) & MAX_INT64;
}
