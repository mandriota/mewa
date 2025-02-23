#include <assert.h>
#include <stdlib.h>

#include "generic.h"

#define G_RETURN_TYPE TEST_ERR

typedef enum {
  TEST_ERR_NOERROR,
	TABLE_ERRS(),
} TEST_ERR;

#define G_TYPE int
#include "table.h"

#define G_TYPE float
#include "table.h"

Map_Entry_int *hm_new_int(size_t length) {
  Map_Entry_int *st = malloc(sizeof(Map_Entry_int) + length * sizeof(int));

  return st;
}

int main() {
  enum { N = 5 };
  Map_Entry_int *entries = hm_new_int(N);

  assert(map_set_int(entries, N, 34, 42) == TEST_ERR_NOERROR);
  assert(map_set_int(entries, N, 123456789123456789, 144) == TEST_ERR_NOERROR);
  assert(map_set_int(entries, N, 1, 11111) == TEST_ERR_NOERROR);
  assert(map_set_int(entries, N, 13, 31) == TEST_ERR_NOERROR);
  assert(map_set_int(entries, N, 990900900090000, 1212121212) == TEST_ERR_NOERROR);
	assert(map_set_int(entries, N, 1984, 7) == TEST_ERR_G_HM_FULL);

	assert(map_pop_int(entries, N, 88) == TEST_ERR_G_HM_NOT_FOUND);
	assert(map_pop_int(entries, N, 990900900090000) == TEST_ERR_NOERROR);

	int a = -1;
	
	assert(map_get_int(entries, N, 6, &a) == TEST_ERR_G_HM_NOT_FOUND && a == -1);
	assert(map_get_int(entries, N, 13, &a) == TEST_ERR_NOERROR && a == 31);
	assert(map_get_int(entries, N, 34, &a) == TEST_ERR_NOERROR && a == 42);
	assert(map_get_int(entries, N, 1, &a) == TEST_ERR_NOERROR && a == 11111);
	assert(map_get_int(entries, N, 990900900090000, &a) == TEST_ERR_G_HM_NOT_FOUND && a == 11111);
	assert(map_get_int(entries, N, 123456789123456789, &a) == TEST_ERR_NOERROR && a == 144);

  free(entries);
	return 0;
}
