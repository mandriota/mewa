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

#ifdef G_TYPE

#include "generic_init.h"

#include <stdlib.h>

typedef struct {
  size_t cap;
  size_t len;
  G_TYPE data[];
} G_TYPED(Stack_);

static inline G_RETURN_TYPE
G_TYPED(st_add_)(G_TYPED(Stack_) *restrict st, G_TYPE v) {
  if (st->len >= st->cap)
    return G_ERROR(_G_ST_FULL);

  st->data[st->len] = v;
  ++st->len;

  return G_ERROR(_NOERROR);
}

static inline G_RETURN_TYPE
G_TYPED(st_pop_)(G_TYPED(Stack_) *restrict st, G_TYPE *v) {
  if (st->len == 0)
    return G_ERROR(_G_ST_EMPTY);

  --st->len;
  *v = st->data[st->len];

  return G_ERROR(_NOERROR);
}

#undef G_TYPE
#endif
