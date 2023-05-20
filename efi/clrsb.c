/*
 * This comes from https://github.com/TinyCC/tinycc/blob/mob/lib/builtin.c
 *
 * The TinyCC code is licensed under GNU Lesser General Public License v2.1.
 */

#include "glue.h"

/*
 * Returns the number of leading redundant sign bits
 * in x, i.e. the number of bits following the most
 * significant bit that are identical to it. There are
 * no special cases for 0 or other values.
*/
int __clrsbdi2(UINT64 x)
{
  if (x < 0) {
    x = ~x;
  }

  x <<= 1;

  return __builtin_clzll(x);
}
