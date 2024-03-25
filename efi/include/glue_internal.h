/** @file

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

**/

#pragma once

typedef VOID *FILE;
typedef INT32 sig_atomic_t;
typedef BASE_LIBRARY_JUMP_BUFFER sigjmp_buf;

enum {
  ENOSYS,
  ENOENT,
  EINTR,
  ERANGE,
  ENOTSUP,
  EINVAL,
};

typedef int pthread_t;

#define __PRI_64_LENGTH_MODIFIER__ "ll"
#define PRIu32 "u"
#define PRIx64 __PRI_64_LENGTH_MODIFIER__ "x"
#define PRIu64 __PRI_64_LENGTH_MODIFIER__ "u"

#define __thread
#define va_start VA_START
#define va_end VA_END
#define va_copy VA_COPY
#define va_arg VA_ARG
#define assert(x) ASSERT(x)
#define offsetof OFFSET_OF
#define false FALSE
#define true TRUE

#define INT8_MAX __INT8_MAX__
#define INT16_MAX __INT16_MAX__
#define INT32_MAX __INT32_MAX__
#define INT64_MAX __INT64_MAX__

#define UINT8_MAX  __UINT8_MAX__
#define UINT16_MAX __UINT16_MAX__
#define UINT32_MAX __UINT32_MAX__
#define UINT64_MAX __UINT64_MAX__

#define INTPTR_MAX __INTPTR_MAX__
#define UINTPTR_MAX __UINTPTR_MAX__
#define PTRDIFF_MAX __PTRDIFF_MAX__
#define SIZE_MAX __SIZE_MAX__

#define INT8_MIN  MIN_INT8
#define INT16_MIN MIN_INT16
#define INT32_MIN MIN_INT32
#define INT64_MIN MIN_INT64

#define __CONCAT(x, y) x ## y
#define INT64_C(value) __CONCAT(value, LL)
#define UINT64_C(value) __CONCAT(value, ULL)
#define bswap_16(x) SwapBytes16(x)
#define bswap_32(x) SwapBytes32(x)
#define bswap_64(x) SwapBytes64(x)
#define CHAR_BIT 8
#define ULONG_MAX UINT64_MAX
#define UINT_MAX  UINT32_MAX
#define FLT_MIN   __FLT_MIN__
#define DBL_MIN   __DBL_MIN__
#define INT_MAX   INT32_MAX
#define INT_MIN   INT32_MIN
#define LLONG_MIN INT64_MIN

typedef __int128 ti_int;
typedef unsigned __int128 tu_int;
typedef UINT64 du_int;
typedef UINT32 su_int;
typedef INT64  di_int;
typedef INT32  si_int;

typedef union {
  di_int all;
  struct {
    su_int low;
    si_int high;
  } s;
} dwords;

typedef union {
    ti_int all;
    struct {
        du_int low;
        di_int high;
    } s;
} twords;

typedef union {
    tu_int all;
    struct {
        du_int low;
        du_int high;
    } s;
} utwords;

STATIC_ASSERT(sizeof(unsigned long) == sizeof(UINT64), "sizeof(unsigned long) != sizeof(UINT64)");
STATIC_ASSERT(sizeof(unsigned int) == sizeof(UINT32), "sizeof(unsigned int) != sizeof(UINT32)");

static inline char *strerror(int errnum)
{
  return "<errno error>";
}

void perror(const char *s);

extern FILE *stdout;
extern FILE *stderr;
extern int errno;

static inline void NORETURN
MyLongJump (
  IN      BASE_LIBRARY_JUMP_BUFFER  *JumpBuffer,
  IN      UINTN                     Value
  )
{
  LongJump (JumpBuffer, Value);
  UNREACHABLE();
}
#define siglongjmp(x, y) MyLongJump(&x, y)
#define sigsetjmp(x, y) SetJump(&x)

void NORETURN abort(void);
#define EXIT_FAILURE 0
static inline void NORETURN exit(int status) { abort(); }
static inline char *getenv(const char *name) { return NULL; }

int vfprintf(FILE *stream, const char *format, va_list ap);
int fprintf(FILE *stream, const char *format, ...);
int printf(const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int vasprintf(char **strp, const char *fmt, va_list ap);

char *strdup(const char *s);
size_t strlen(const char *s);
char *strstr(const char *haystack, const char *needle);
int memcmp(const void *s1, const void *s2, size_t n);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
char *strchr(const char *s, int c);
char *strcat(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);

static inline int fclose(const FILE *f) { return 0; }
static inline int fflush(FILE *f) { return 0; }
static inline FILE *fopen(const char *n, const char *m) { return NULL; }

static inline int getpagesize(void) { return EFI_PAGE_SIZE; }

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *memalign(size_t alignment, size_t size);

typedef int cmp_t(const void *, const void *);
void qsort(void *a, size_t n, size_t es, cmp_t *cmp);
void *bsearch(const void *key, const void *base,
	      size_t nmemb, size_t size,
	      int (*compar)(const void *, const void *));

struct tm {
  int tm_sec;    /* Seconds (0-60) */
  int tm_min;    /* Minutes (0-59) */
  int tm_hour;   /* Hours (0-23) */
  int tm_mday;   /* Day of the month (1-31) */
  int tm_mon;    /* Month (0-11) */
  int tm_year;   /* Year - 1900 */
  int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
  int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
  int tm_isdst;  /* Daylight saving time */
};

/* All floating-point numbers can be put in one of these categories.  */
#define FP_NAN 0
#define FP_INFINITE 1
#define FP_ZERO 2
#define FP_SUBNORMAL 3
#define FP_NORMAL 4

#define fpclassify(x)							\
  __builtin_fpclassify (FP_NAN, FP_INFINITE,				\
			FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)

#define isgreater(x, y)       __builtin_isgreater(x, y)
#define isgreaterequal(x, y)  __builtin_isgreaterequal(x, y)
#define isless(x, y)          __builtin_isless(x, y)
#define islessequal(x, y)     __builtin_islessequal(x, y)
#define islessgreater(x, y)   __builtin_islessgreater(x, y)
#define isunordered(x, y)     __builtin_isunordered(x, y)
#define signbit(x)            __builtin_signbit (x)

static inline float sqrtf(float x)
{
  abort();
  UNREACHABLE();
}

static inline float fabsf(float x)
{
  abort();
  UNREACHABLE();
}

static inline float fmaf(float x, float y, float z)
{
  abort();
  UNREACHABLE();
}

static inline double sqrt(double x)
{
  abort();
  UNREACHABLE();
}

static inline double pow(double x, double y)
{
  abort();
  UNREACHABLE();
}

static inline double log(double x)
{
  abort();
  UNREACHABLE();
}

static inline double tan(double x)
{
  abort();
  UNREACHABLE();
}

static inline double atan2(double y, double x)
{
  abort();
  UNREACHABLE();
}

static inline int isinf(double x)
{
  abort();
  UNREACHABLE();
}

static inline int isnan(double x)
{
  abort();
  UNREACHABLE();
}

static inline double rint(double x)
{
  abort();
  UNREACHABLE();
}

static inline double floor(double x)
{
  abort();
  UNREACHABLE();
}

static inline double ceil(double x)
{
  abort();
  UNREACHABLE();
}

static inline double fabs(double x)
{
  abort();
  UNREACHABLE();
}

static inline double sin(double x)
{
  abort();
  UNREACHABLE();
}

static inline double cos(double x)
{
  abort();
  UNREACHABLE();
}

static inline double fma(double x, double y, double z)
{
  abort();
  UNREACHABLE();
}

static inline __int128 __sync_val_compare_and_swap_16(void *ptr, __int128 oldval, __int128 newval)
{
  abort();
  UNREACHABLE();
}

int64_t efi_get_timer_ticks(void);
void efi_get_g_rand_seed(UINT32 seed[4]);
void *efi_alloc_code_pages(size_t size);
void efi_free_code_pages(void *p, size_t size);
int64_t efi_get_timer_ns(void);


