/** @file

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#include "glue.h"

int main(int argc, char **argv, char **envp);

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  char *argv[] = { "sample", NULL };
  int argc = ARRAY_SIZE(argv) - 1;

  main(argc, argv, NULL);

  return EFI_SUCCESS;
}
