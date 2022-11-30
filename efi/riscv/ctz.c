/* ===-- ctz.c - Implement __ctzsi2/__ctzdi2 -------------------------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 * ===----------------------------------------------------------------------===
 *
 * This file implements __ctzdi2 for the compiler_rt library.
 *
 * ===----------------------------------------------------------------------===
 */

#include "glue.h"

/* Returns: the number of trailing 0-bits  */

/* Precondition: a != 0 */

si_int
__ctzsi2(si_int a)
{
    su_int x = (su_int)a;
    si_int t = ((x & 0x0000FFFF) == 0) << 4;  /* if (x has no small bits) t = 16 else 0 */
    x >>= t;           /* x = [0 - 0xFFFF] + higher garbage bits */
    su_int r = t;       /* r = [0, 16]  */
    /* return r + ctz(x) */
    t = ((x & 0x00FF) == 0) << 3;
    x >>= t;           /* x = [0 - 0xFF] + higher garbage bits */
    r += t;            /* r = [0, 8, 16, 24] */
    /* return r + ctz(x) */
    t = ((x & 0x0F) == 0) << 2;
    x >>= t;           /* x = [0 - 0xF] + higher garbage bits */
    r += t;            /* r = [0, 4, 8, 12, 16, 20, 24, 28] */
    /* return r + ctz(x) */
    t = ((x & 0x3) == 0) << 1;
    x >>= t;
    x &= 3;            /* x = [0 - 3] */
    r += t;            /* r = [0 - 30] and is even */
    /* return r + ctz(x) */

/*  The branch-less return statement below is equivalent
 *  to the following switch statement:
 *     switch (x)
 *    {
 *     case 0:
 *         return r + 2;
 *     case 2:
 *         return r + 1;
 *     case 1:
 *     case 3:
 *         return r;
 *     }
 */
    return r + ((2 - (x >> 1)) & -((x & 1) == 0));
}

si_int
__ctzdi2(di_int a)
{
    dwords x;
    x.all = a;
    const si_int f = -(x.s.low == 0);
    return __ctzsi2((x.s.high & f) | (x.s.low & ~f)) +
              (f & ((si_int)(sizeof(si_int) * CHAR_BIT)));
}
