/*
 * This comes from https://github.com/TinyCC/tinycc/blob/mob/lib/builtin.c
 *
 * The TinyCC code is licensed under GNU Lesser General Public License v2.1.
 */

#include "glue.h"

#define POPCOUNTL(x, m)                                                   \
    x = x - ((x >> 1) & 0x5555555555555555ull);                           \
    x = (x & 0x3333333333333333ull) + ((x >> 2) & 0x3333333333333333ull); \
    x = (x + (x >> 4)) & 0xf0f0f0f0f0f0f0full;                            \
    return ((x * 0x0101010101010101ull) >> 56) & m;

int __popcountdi2(INT64 x)
{
  return POPCOUNTL(x, 0x7f);
}
