## @file
#
#  Copyright (c) 2022-2023, Intel Corporation. All rights reserved.<BR>
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2 of the License, or (at your option) any later version.
#
##

[LibraryClasses.common.UEFI_APPLICATION, LibraryClasses.common.DXE_DRIVER]
  #
  # Unicorn
  #
  UnicornEngineLib|unicorn/efi/UnicornEngineLib.inf
  UnicornStubLib|unicorn/efi/UnicornStubLib.inf
  UnicornRV64Lib|unicorn/efi/UnicornRV64Lib.inf
  UnicornRV32Lib|unicorn/efi/UnicornRV32Lib.inf
  UnicornX86Lib|unicorn/efi/UnicornX86Lib.inf
  UnicornArm64Lib|unicorn/efi/UnicornArm64Lib.inf

[PcdsFeatureFlag]

[PcdsDynamicExDefault]

[Components]

[BuildOptions]
GCC:*_*_AARCH64_CC_XIPFLAGS ==
GCC:*_*_*_CC_FLAGS = -Wno-array-parameter

[BuildOptions.AARCH64]
GCC:*_*_*_CC_FLAGS = -Wno-psabi
#
# LTO options.
#
# Note these apply on top of whatever is implied by Conf/tools_def.txt!
# If you want to disable LTO, you're going to have to edit tools_def.txt
# as well.
#
GCC:*_*_*_DLINK_FLAGS = -L$(WORKSPACE)/unicorn/efi/aarch64 -llto-unicorn -Wl,-plugin-opt=-pass-through=-llto-unicorn -flto=$(UC_LTO_JOBS)
GCC:*_*_*_CC_FLAGS = -flto=$(UC_LTO_JOBS)

[BuildOptions.X64]
#
# LTO options.
#
# Note these apply on top of whatever is implied by Conf/tools_def.txt!
# If you want to disable LTO, you're going to have to edit tools_def.txt
# as well.
#
GCC:*_*_*_DLINK_FLAGS = -L$(WORKSPACE)/unicorn/efi/x86_64 -llto-unicorn -Wl,-plugin-opt=-pass-through=-llto-unicorn -flto=$(UC_LTO_JOBS)
GCC:*_*_*_CC_FLAGS = -flto=$(UC_LTO_JOBS)
