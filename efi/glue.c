/** @file

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#include "glue.h"
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CacheMaintenanceLib.h>

int errno = 0;
FILE *stdout = (FILE *) DEBUG_INFO;
FILE *stderr = (FILE *) DEBUG_ERROR;

void *memcpy(void *dest, const void *src, size_t n)
{
  return CopyMem (dest, src, n);
}

void *memmove(void *dest, const void *src, size_t n)
{
  //
  // UEFI CopyMem handles overlapping.
  //
  return CopyMem (dest, src, n);
}

void *memset(void *s, int c, size_t n)
{
  return SetMem (s, n, c);
}

int vfprintf(FILE *stream, const char *format, va_list ap)
{
  char *f;
  char *fmt;
  ASSERT (stream == stdout || stream == stderr);

  f = fmt = strdup(format);
  if (fmt == NULL) {
    return -1;
  }

  while ((f = AsciiStrStr(f, "%s")) != NULL) {
    f[1] = 'a';
    f += 2;
  }

  DebugVPrint((UINTN) stream, fmt, ap);
  free (fmt);
  /*
   * A non-zero value indicating success - close enough.
   */
  return 1;
}

int fprintf(FILE *stream, const char *format, ...)
{
  VA_LIST   Marker;
  INT32     Result;

  VA_START  (Marker, format);
  Result = vfprintf (stream, format, Marker);
  VA_END (Marker);

  return Result;
}

int printf(const char *format, ...)
{
  VA_LIST   Marker;
  INT32     Result;

  VA_START  (Marker, format);
  Result = vfprintf (stdout, format, Marker);
  VA_END (Marker);

  return Result;
}

int snprintf(char *str, size_t size, const char *format, ...)
{
  VA_LIST   Marker;
  int       NumberOfPrinted;

  VA_START (Marker, format);
  NumberOfPrinted = (int) AsciiVSPrint (str, size, format, Marker);
  VA_END (Marker);

  return NumberOfPrinted;
}

int vasprintf(char **strp, const char *fmt, va_list ap)
{
  char *String;
  UINTN Length = SPrintLengthAsciiFormat (fmt, ap);

  if (Length == 0) {
    return 0;
  }

  Length++;
  String = malloc (Length);
  if (String == NULL) {
    return -1;
  }

  *strp = String;
  return (int) AsciiVSPrint (String, Length, fmt, ap);
}

int strcmp(const char *s1, const char *s2)
{
  return AsciiStrCmp (s1, s2);
}

int memcmp(const void *s1, const void *s2, size_t n)
{
  return CompareMem (s1, s2, n);
}

char *strdup(const char *s)
{
  int len;
  char *result;

  len = strlen(s);

  result = malloc (len + 1);
  if (result == NULL) {
    return NULL;
  }
  memcpy (result, s, len);

  result[len] = 0;
  return result;
}

size_t strlen(const char *s)
{
  return AsciiStrLen(s);
}
