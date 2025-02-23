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

#ifndef GENERIC_H

#define TRY(type, expr)        \
  {                            \
    type err = expr;           \
    if (err != type##_NOERROR) \
      return err;              \
  }

#ifndef G_TYPED
#define G_CONCAT_EXPAND(name, type) name##type
#define G_CONCAT(name, type) G_CONCAT_EXPAND(name, type)
#define G_TYPED(name) G_CONCAT(name, G_TYPE)
#define G_ERROR(name) G_CONCAT(G_RETURN_TYPE, name)
#endif

//=:stack:errors
#define STACK_ERRS()                   \
  G_CONCAT(G_RETURN_TYPE, _G_ST_FULL), \
  G_CONCAT(G_RETURN_TYPE, _G_ST_EMPTY)

#define STRINGIFY_CASE_STACK_ERRS()                   \
  STRINGIFY_CASE(G_CONCAT(G_RETURN_TYPE, _G_ST_FULL)) \
  STRINGIFY_CASE(G_CONCAT(G_RETURN_TYPE, _G_ST_EMPTY))

//=:table:errors
#define TABLE_ERRS()                   \
  G_CONCAT(G_RETURN_TYPE, _G_HM_FULL), \
  G_CONCAT(G_RETURN_TYPE, _G_HM_NOT_FOUND)

#define STRINGIFY_CASE_TABLE_ERRS()                   \
  STRINGIFY_CASE(G_CONCAT(G_RETURN_TYPE, _G_HM_FULL)) \
  STRINGIFY_CASE(G_CONCAT(G_RETURN_TYPE, _G_HM_NOT_FOUND))

#endif
