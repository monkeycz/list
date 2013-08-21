#include <assert.h>

#define LIST_VALUE_TYPE		int
#include <list.h>
#include <stdio.h>

static void list_value_printor_i(LIST_VALUE_TYPE value)
{
	printf("%d", value);
}

int main(int argc, char* argv[])
{
	list_context_t* list_context = list_new(LIST_LENGTH_DEFAULT, NULL, NULL, NULL, list_value_printor_i);
	assert(list_context != NULL);

	list_context_t* list_context_retain = list_retain(list_context);
	assert(list_retain_count(list_context) == 2);
	assert(list_retain_count(list_context_retain) == 2);
	list_delete(list_context_retain);
	assert(list_retain_count(list_context) == 1);
	assert(list_retain_count(list_context_retain) == 1);

	list_context_t* list_context_copy = list_copy(list_context);
	assert(list_context_copy != NULL);
	assert(list_retain_count(list_context_copy) == 1);
	list_delete(list_context_copy);

	for (int i = 0; i < 2; i++) {
		assert(list_append(list_context, 111) == 0);
		assert(list_append(list_context, 222) == 0);
		assert(list_append(list_context, 333) == 0);

		assert(list_count(list_context) == 3);

		assert(list_has_value(list_context, 111) == 0);
		assert(list_has_value(list_context, 222) == 0);
		assert(list_has_value(list_context, 333) == 0);
		assert(list_has_value(list_context, 444) != 0);

		assert(list_pop(list_context) == 0);
		assert(list_remove(list_context, 0) == 0);
		assert(list_insert(list_context, 0, 111) == 0);
		assert(list_insert(list_context, 9, 333) == 0);
		assert(list_insert(list_context, 9, 111) == 0);

		int value;
		assert(list_get(list_context, 0, &value) == 0);
		assert(value == 111);
		assert(list_get(list_context, 1, &value) == 0);
		assert(value == 222);
		assert(list_get(list_context, 2, &value) == 0);
		assert(value == 333);
		assert(list_get(list_context, 3, &value) == 0);
		assert(value == 111);
		assert(list_get(list_context, 4, &value) != 0);

		size_t index = 0;
		assert(list_index(list_context, 0, 111, &index) == 0);
		assert(index == 0);
		assert(list_index(list_context, index + 1, 111, &index) == 0);
		assert(index == 3);

		list_iter_t* list_iter = list_iter_new(list_context);
		assert(list_iter != NULL);
		assert(list_iter_get(list_iter, &index, &value) == 0);
		assert(index == 0); assert(value == 111);
		assert(list_iter_get(list_iter, &index, &value) == 0);
		assert(index == 1); assert(value == 222);
		assert(list_iter_get(list_iter, &index, &value) == 0);
		assert(index == 2); assert(value == 333);
		assert(list_iter_get(list_iter, &index, &value) == 0);
		assert(index == 3); assert(value == 111);
		assert(list_iter_get(list_iter, &index, &value) != 0);
		list_iter_delete(list_iter);

		assert(list_sort(list_context, 1) == 0);
		assert(list_index(list_context, 0, 111, &index) == 0);
		assert(index == 2);
		assert(list_sort(list_context, 0) == 0);
		assert(list_index(list_context, 0, 111, &index) == 0);
		assert(index == 0);

		assert(list_reverse(list_context) == 0);
		assert(list_index(list_context, 0, 111, &index) == 0);
		assert(index == 2);
		assert(list_reverse(list_context) == 0);
		assert(list_index(list_context, 0, 111, &index) == 0);
		assert(index == 0);

		assert(list_remove_value(list_context, 111) == 0);
		assert(list_has_value(list_context, 111) != 0);
		assert(list_remove_value(list_context, 222) == 0);
		assert(list_has_value(list_context, 222) != 0);
		assert(list_remove_value(list_context, 444) != 0);
		assert(list_has_value(list_context, 444) != 0);

		assert(list_count(list_context) == 1);

		assert(list_clear(list_context) == 0);
		assert(list_count(list_context) == 0);
	}

	list_delete(list_context);

	return 0;
}
