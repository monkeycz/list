#include <list/list_s.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[])
{
	list_context_s_t* list_context_s = list_new_s();
	assert(list_context_s != NULL);

	list_context_s_t* list_context_retain_s = list_retain_s(list_context_s);
	assert(list_retain_count_s(list_context_s) == 2);
	assert(list_retain_count_s(list_context_retain_s) == 2);
	list_delete_s(list_context_retain_s);
	assert(list_retain_count_s(list_context_s) == 1);
	assert(list_retain_count_s(list_context_retain_s) == 1);

	list_context_s_t* list_context_copy_s = list_copy_s(list_context_s);
	assert(list_context_copy_s != NULL);
	assert(list_retain_count_s(list_context_copy_s) == 1);
	list_delete_s(list_context_copy_s);

	for (int i = 0; i < 2; i++) {
		assert(list_append_s(list_context_s, "aaa") == 0);
		assert(list_append_s(list_context_s, "bbb") == 0);
		assert(list_append_s(list_context_s, "ccc") == 0);

		assert(list_count_s(list_context_s) == 3);

		assert(list_has_value_s(list_context_s, "aaa") == 0);
		assert(list_has_value_s(list_context_s, "bbb") == 0);
		assert(list_has_value_s(list_context_s, "ccc") == 0);
		assert(list_has_value_s(list_context_s, "ddd") != 0);

		assert(list_pop_s(list_context_s) == 0);
		assert(list_remove_s(list_context_s, 0) == 0);
		assert(list_insert_s(list_context_s, 0, "aaa") == 0);
		assert(list_insert_s(list_context_s, 9, "ccc") == 0);
		assert(list_insert_s(list_context_s, 9, "aaa") == 0);

		char* value;
		assert(list_get_s(list_context_s, 0, &value) == 0);
		assert(strcmp(value, "aaa") == 0);
		assert(list_get_s(list_context_s, 1, &value) == 0);
		assert(strcmp(value, "bbb") == 0);
		assert(list_get_s(list_context_s, 2, &value) == 0);
		assert(strcmp(value, "ccc") == 0);
		assert(list_get_s(list_context_s, 3, &value) == 0);
		assert(strcmp(value, "aaa") == 0);
		assert(list_get_s(list_context_s, 4, &value) != 0);

		size_t index = 0;
		assert(list_index_s(list_context_s, 0, "aaa", &index) == 0);
		assert(index == 0);
		assert(list_index_s(list_context_s, index + 1, "aaa", &index) == 0);
		assert(index == 3);

		list_iter_s_t* list_iter_s = list_iter_new_s(list_context_s);
		assert(list_iter_s != NULL);
		assert(list_iter_get_s(list_iter_s, &index, &value) == 0);
		assert(index == 0); assert(strcmp(value, "aaa") == 0);
		assert(list_iter_get_s(list_iter_s, &index, &value) == 0);
		assert(index == 1); assert(strcmp(value, "bbb") == 0);
		assert(list_iter_get_s(list_iter_s, &index, &value) == 0);
		assert(index == 2); assert(strcmp(value, "ccc") == 0);
		assert(list_iter_get_s(list_iter_s, &index, &value) == 0);
		assert(index == 3); assert(strcmp(value, "aaa") == 0);
		assert(list_iter_get_s(list_iter_s, &index, &value) != 0);
		list_iter_delete_s(list_iter_s);

		assert(list_sort_s(list_context_s, 1) == 0);
		assert(list_index_s(list_context_s, 0, "aaa", &index) == 0);
		assert(index == 2);
		assert(list_sort_s(list_context_s, 0) == 0);
		assert(list_index_s(list_context_s, 0, "aaa", &index) == 0);
		assert(index == 0);

		assert(list_reverse_s(list_context_s) == 0);
		assert(list_index_s(list_context_s, 0, "aaa", &index) == 0);
		assert(index == 2);
		assert(list_reverse_s(list_context_s) == 0);
		assert(list_index_s(list_context_s, 0, "aaa", &index) == 0);
		assert(index == 0);

		assert(list_remove_value_s(list_context_s, "aaa") == 0);
		assert(list_has_value_s(list_context_s, "aaa") != 0);
		assert(list_remove_value_s(list_context_s, "bbb") == 0);
		assert(list_has_value_s(list_context_s, "bbb") != 0);
		assert(list_remove_value_s(list_context_s, "ddd") != 0);
		assert(list_has_value_s(list_context_s, "ddd") != 0);

		assert(list_count_s(list_context_s) == 1);

		assert(list_clear_s(list_context_s) == 0);
		assert(list_count_s(list_context_s) == 0);
	}

	list_delete_s(list_context_s);

	return 0;
}
