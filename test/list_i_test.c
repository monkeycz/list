#include <list/list_i.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	list_context_i_t* list_context_i = list_new_i();
	assert(list_context_i != NULL);

	list_context_i_t* list_context_retain_i = list_retain_i(list_context_i);
	assert(list_retain_count_i(list_context_i) == 2);
	assert(list_retain_count_i(list_context_retain_i) == 2);
	list_delete_i(list_context_retain_i);
	assert(list_retain_count_i(list_context_i) == 1);
	assert(list_retain_count_i(list_context_retain_i) == 1);

	list_context_i_t* list_context_copy_i = list_copy_i(list_context_i);
	assert(list_context_copy_i != NULL);
	assert(list_retain_count_i(list_context_copy_i) == 1);
	list_delete_i(list_context_copy_i);

	for (int i = 0; i < 2; i++) {
		assert(list_append_i(list_context_i, 111) == 0);
		assert(list_append_i(list_context_i, 222) == 0);
		assert(list_append_i(list_context_i, 333) == 0);

		assert(list_count_i(list_context_i) == 3);

		assert(list_has_value_i(list_context_i, 111) == 0);
		assert(list_has_value_i(list_context_i, 222) == 0);
		assert(list_has_value_i(list_context_i, 333) == 0);
		assert(list_has_value_i(list_context_i, 444) != 0);

		assert(list_pop_i(list_context_i) == 0);
		assert(list_remove_i(list_context_i, 0) == 0);
		assert(list_insert_i(list_context_i, 0, 111) == 0);
		assert(list_insert_i(list_context_i, 9, 333) == 0);
		assert(list_insert_i(list_context_i, 9, 111) == 0);

		int value;
		assert(list_get_i(list_context_i, 0, &value) == 0);
		assert(value == 111);
		assert(list_get_i(list_context_i, 1, &value) == 0);
		assert(value == 222);
		assert(list_get_i(list_context_i, 2, &value) == 0);
		assert(value == 333);
		assert(list_get_i(list_context_i, 3, &value) == 0);
		assert(value == 111);
		assert(list_get_i(list_context_i, 4, &value) != 0);

		size_t index = 0;
		assert(list_index_i(list_context_i, 0, 111, &index) == 0);
		assert(index == 0);
		assert(list_index_i(list_context_i, index + 1, 111, &index) == 0);
		assert(index == 3);

		list_iter_i_t* list_iter_i = list_iter_new_i(list_context_i);
		assert(list_iter_i != NULL);
		assert(list_iter_get_i(list_iter_i, &index, &value) == 0);
		assert(index == 0); assert(value == 111);
		assert(list_iter_get_i(list_iter_i, &index, &value) == 0);
		assert(index == 1); assert(value == 222);
		assert(list_iter_get_i(list_iter_i, &index, &value) == 0);
		assert(index == 2); assert(value == 333);
		assert(list_iter_get_i(list_iter_i, &index, &value) == 0);
		assert(index == 3); assert(value == 111);
		assert(list_iter_get_i(list_iter_i, &index, &value) != 0);
		list_iter_delete_i(list_iter_i);

		assert(list_sort_i(list_context_i, 1) == 0);
		assert(list_index_i(list_context_i, 0, 111, &index) == 0);
		assert(index == 2);
		assert(list_sort_i(list_context_i, 0) == 0);
		assert(list_index_i(list_context_i, 0, 111, &index) == 0);
		assert(index == 0);

		assert(list_reverse_i(list_context_i) == 0);
		assert(list_index_i(list_context_i, 0, 111, &index) == 0);
		assert(index == 2);
		assert(list_reverse_i(list_context_i) == 0);
		assert(list_index_i(list_context_i, 0, 111, &index) == 0);
		assert(index == 0);

		assert(list_remove_value_i(list_context_i, 111) == 0);
		assert(list_has_value_i(list_context_i, 111) != 0);
		assert(list_remove_value_i(list_context_i, 222) == 0);
		assert(list_has_value_i(list_context_i, 222) != 0);
		assert(list_remove_value_i(list_context_i, 444) != 0);
		assert(list_has_value_i(list_context_i, 444) != 0);

		assert(list_count_i(list_context_i) == 1);

		assert(list_clear_i(list_context_i) == 0);
		assert(list_count_i(list_context_i) == 0);
	}

	list_delete_i(list_context_i);

	return 0;
}
