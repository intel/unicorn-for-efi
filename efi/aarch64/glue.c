/** @file

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#include "glue.h"
#include <Library/CacheMaintenanceLib.h>

void __clear_cache(void *start, void *end)
{
  InvalidateInstructionCacheRange(start, (UINTN) end - (UINTN) start);
}

void abort(void)
{
  asm ("hlt #0x86");
  while (1);
}
