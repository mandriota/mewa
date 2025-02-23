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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//=:hmap:hmap

typedef struct {
  uint64_t key;
  G_TYPE val;
} G_TYPED(Map_Entry_);

//=:hmap:get

static inline G_RETURN_TYPE
G_TYPED(map_get_)(G_TYPED(Map_Entry_) m[restrict static 1], size_t cap, uint64_t key, G_TYPE *val) {
  size_t index = key % cap;
  size_t steps = 0;

  do {
    if (m[index].key == key) {
      *val = m[index].val;
      return G_ERROR(_NOERROR);
    }

    index = (index + 1) % cap;
    ++steps;
  } while (steps < cap);

  return G_ERROR(_G_HM_NOT_FOUND);
}

//=:hmap:set

static inline G_RETURN_TYPE
G_TYPED(map_set_)(G_TYPED(Map_Entry_) m[restrict static 1], size_t cap, uint64_t key, G_TYPE val) {
  size_t index = key % cap;
  size_t steps = 0;

  do {
    if (m[index].key == key || m[index].key == 0) {
      m[index].key = key;
      m[index].val = val;
      return G_ERROR(_NOERROR);
    }

    index = (index + 1) % cap;
    ++steps;
  } while (steps < cap);

  return G_ERROR(_G_HM_FULL);
}

//=:hmap:pop

static inline G_RETURN_TYPE
G_TYPED(map_pop_)(G_TYPED(Map_Entry_) m[restrict static 1], size_t cap, uint64_t key) {
  size_t index = key % cap;
  size_t steps = 0;

  do {
    if (m[index].key == key) {
      m[index].key = 0;
      return G_ERROR(_NOERROR);
    }

    index = (index + 1) % cap;
    ++steps;
  } while (steps < cap);

  return G_ERROR(_G_HM_NOT_FOUND);
}

#undef G_TYPE
#endif
