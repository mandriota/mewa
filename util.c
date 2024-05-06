/******************************************************************************\
*                                                                              *
*    Mewa. Math EWAluator.                                                     *
*    Copyright (C) 2024 Mark Mandriota                                         *
*                                                                              *
*    This program is free software: you can redistribute it and/or modify      *
*    it under the terms of the GNU General Public License as published by      *
*    the Free Software Foundation, either version 3 of the License, or         *
*    (at your option) any later version.                                       *
*                                                                              *
*    This program is distributed in the hope that it will be useful,           *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
*    GNU General Public License for more details.                              *
*                                                                              *
*    You should have received a copy of the GNU General Public License         *
*    along with this program.  If not, see <https://www.gnu.org/licenses/>.    *
*                                                                              *
\******************************************************************************/

#include "util.h"

#include <assert.h>
#include <stdint.h>
#include <tgmath.h>

//=:util
//           _   _ _
//          | | (_) |
//     _   _| |_ _| |
//    | | | | __| | |
//    | |_| | |_| | |
//     \__,_|\__|_|_|

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
  if (*lineptr == NULL || *n == 0)
    *lineptr = (char *)malloc((*n = 16) * sizeof(char));

  char cc = 0;
  size_t cp = 0;
  do {
    (*lineptr)[cp] = cc = getc(stream);
    ++cp;
    if (cp >= *n)
      *lineptr = (char *)realloc(*lineptr, *n *= 2);
  } while (cc != '\n' && !ferror(stream));

	return cp;
}

//=:util:memory
size_t align(size_t sz, size_t alignment) {
  return sz + (alignment - ((sz - 1) & (alignment - 1))) - 1;
}

//=:util:encoding
unt_t encode_symbol_c(char c) {
  if (is_upper(c))
    return (c - 'A') + 1;
  if (is_lower(c))
    return (c - 'a') + ENC_OFF + 1;
  if (c == '_')
    return ENC_OFF * 2 + 1;
  if (is_digit(c))
    return (c - '0') + ENC_OFF * 2 + 2;

  DBG_FATAL("symbol's character (%d) is out of range", c);
  return 0;
}

char decode_symbol_c(char c) {
  if (c >= 1 && c <= ENC_OFF)
    return (c + 'A') - 1;
  if (c >= ENC_OFF + 1 && c <= ENC_OFF * 2)
    return (c + 'a') - ENC_OFF - 1;
  if (c == ENC_OFF * 2 + 1)
    return '_';
  if (c >= ENC_OFF * 2 + 2 && c <= ENC_OFF * 2 + 12)
    return (c + '0') - ENC_OFF * 2 - 2;

  DBG_FATAL("symbol's character (%d) is out of range", c);
  return 0;
}

char *decode_symbol(char *dst, char *dst_end, unt_t src) {
  char *p, c;

  for (p = dst; src && p < dst_end; ++p) {
    c = src & ((1 << 6) - 1);
    *p = decode_symbol_c(c);
    src >>= 6;
  }

  if (src != 0)
    FATAL("buffer capacity is not enough\n");

  return p;
}

//=:runtime
//                      _   _
//                     | | (_)
//     _ __ _   _ _ __ | |_ _ _ __ ___   ___
//    | '__| | | | '_ \| __| | '_ ` _ \ / _	;
//    | |  | |_| | | | | |_| | | | | | |  __/
//    |_|   \__,_|_| |_|\__|_|_| |_| |_|\___|

char *int_stringify(char *dst, char *dst_end, int_t num) {
  assert(dst_end >= dst);

  char *p = dst_end + 1;
  int_t n = num;

  if (n == 0) {
    *--p = '0';
    return p;
  }

  while (n) {
    if (p == dst)
      FATAL("buffer capacity is not enough\n");

    *--p = (num < 0 ? -1 : 1) * (n % 10) + '0';
    n /= 10;
  }

  if (num < 0)
    *--p = '-';

  return p;
}

//=:runtime:operators
int_t pow_int(int_t base, int_t expo) {
  if (expo == 0)
    return 1;
  if (expo == 1)
    return base;

  int_t rt = 1;
  while (expo > 1) {
    if (expo % 2 == 1)
      rt *= base;
    expo /= 2;
    base *= base;
  }
  return rt * base;
}

int_t fac_int(int_t base, int_t step) {
  if (base == 0)
    return 1;

  int_t rt = 1;
  for (int_t i = base; i >= 2; i -= step)
    rt *= i;

  return rt;
}

flt_t fac_flt_helper(flt_t i, flt_t step) {
  flt_t rt = 0;

  for (int_t j = 1; j <= step; ++j)
    rt += cos(acos(cos(2 * j * M_PI / step)) * i);

  return rt / step;
}

flt_t fac_flt(flt_t base, flt_t step) {
  flt_t rt = pow(step, base / step) * tgamma(1 + base / step);

  for (int_t i = 1; i < step; ++i)
    rt *= pow(pow(step, (step - i) / step) / tgamma(i / step),
              fac_flt_helper(base - i, step));

  return rt;
}

bol_t is_almost_equal_flt(flt_t x, flt_t y) {
  if (x == y)
    return true;
  if (isnan(x) || isinf(x) || isnan(y) || isinf(y))
    return false;

  IEEE754_flt_t x_ieee754 = {.lit = x};
  IEEE754_flt_t y_ieee754 = {.lit = y};

  if (x < MAX_DIFF_ULPS_FROM || y < MAX_DIFF_ULPS_FROM)
    return fabsl(x - y) < MAX_DIFF_ABS;
  if (x_ieee754.sign != y_ieee754.sign ||
      llabs((int64_t)x_ieee754.expo - (int64_t)y_ieee754.expo) > 1)
    return false;

  if (x_ieee754.expo > y_ieee754.expo) {
    y_ieee754.mant += MAX_DIFF_ULPS * 2;
    return y_ieee754.mant - x_ieee754.mant <= MAX_DIFF_ULPS;
  } else if (x_ieee754.expo < y_ieee754.expo) {
    x_ieee754.mant += MAX_DIFF_ULPS * 2;
    return x_ieee754.mant - y_ieee754.mant <= MAX_DIFF_ULPS;
  }

  return llabs((int64_t)x_ieee754.mant - (int64_t)y_ieee754.mant) <=
         MAX_DIFF_ULPS;
}

bol_t is_almost_equal_cmx(cmx_t x, cmx_t y) {
  return is_almost_equal_flt(creal(x), creal(y)) &&
         is_almost_equal_flt(cimag(x), cimag(y));
}

