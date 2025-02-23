#include <assert.h>
#include <stdlib.h>

#include "generic.h"

#define G_RETURN_TYPE TEST_ERR

typedef enum {
  TEST_ERR_NOERROR,
	STACK_ERRS(),
} TEST_ERR;

#define G_TYPE int
#include "stack.h"

#define G_TYPE float
#include "stack.h"

Stack_int *st_new_int(size_t length) {
  Stack_int *st = malloc(sizeof(Stack_int) + length * sizeof(int));
  st->len = 0;
  st->cap = length;

	return st;
}

TEST_ERR foo(Stack_int *st, int *rt) {
  TRY(TEST_ERR, st_pop_int(st, rt));
  TRY(TEST_ERR, st_add_int(st, 11));
  TRY(TEST_ERR, st_add_int(st, 13));

  return TEST_ERR_NOERROR;
}

int main(void) {
	Stack_int *st = st_new_int(3);

  int a = -12;
  assert(foo(st, &a) == TEST_ERR_G_ST_EMPTY && a == -12 && st->len == 0);
  st_add_int(st, 12);
  assert(foo(st, &a) == TEST_ERR_NOERROR && a == 12 && st->len == 2);
  assert(foo(st, &a) == TEST_ERR_NOERROR && a == 13 && st->len == 3);
  assert(foo(st, &a) == TEST_ERR_G_ST_FULL && a == 13 && st->len == 3);
  st_pop_int(st, &a);
  assert(a == 11 && st->len == 2);

	free(st);

  return 0;
}
