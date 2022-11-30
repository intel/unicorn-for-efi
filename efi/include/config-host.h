/** @file

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#if defined (MDE_CPU_X64)
#define CONFIG_CPUID_H 1
#endif

#define CONFIG_INT128 1
#define CONFIG_CMPXCHG128 1
#define CONFIG_ATOMIC64 1

#define CONFIG_PRAGMA_DIAGNOSTIC_AVAILABLE 1
#define CONFIG_STATIC_ASSERT 1
