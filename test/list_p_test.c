#include <list/list_p.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	list_context_p_t* list_context_p = list_new_p();
	assert(list_context_p != NULL);

	list_context_p_t* list_context_retain_p = list_retain_p(list_context_p);
	assert(list_retain_count_p(list_context_p) == 2);
	assert(list_retain_count_p(list_context_retain_p) == 2);
	list_delete_p(list_context_retain_p);
	assert(list_retain_count_p(list_context_p) == 1);
	assert(list_retain_count_p(list_context_retain_p) == 1);

	list_context_p_t* list_context_copy_p = list_copy_p(list_context_p);
	assert(list_context_copy_p != NULL);
	assert(list_retain_count_p(list_context_copy_p) == 1);
	list_delete_p(list_context_copy_p);

	int aaa = 111;
	int bbb = 222;
	int ccc = 333;
	int ddd = 444;

	for (int i = 0; i < 2; i++) {
		assert(list_append_p(list_context_p, &aaa) == 0);
		assert(list_append_p(list_context_p, &bbb) == 0);
		assert(list_append_p(list_context_p, &ccc) == 0);

		assert(list_count_p(list_context_p) == 3);

		assert(list_has_value_p(list_context_p, &aaa) == 0);
		assert(list_has_value_p(list_context_p, &bbb) == 0);
		assert(list_has_value_p(list_context_p, &ccc) == 0);
		assert(list_has_value_p(list_context_p, &ddd) != 0);

		assert(list_pop_p(list_context_p) == 0);
		assert(list_remove_p(list_context_p, 0) == 0);
		assert(list_insert_p(list_context_p, 0, &aaa) == 0);
		assert(list_insert_p(list_context_p, 9, &ccc) == 0);
		assert(list_insert_p(list_context_p, 9, &aaa) == 0);

		void* value;
		assert(list_get_p(list_context_p, 0, &value) == 0);
		assert(*(int*)value == 111);
		assert(list_get_p(list_context_p, 1, &value) == 0);
		assert(*(int*)value == 222);
		assert(list_get_p(list_context_p, 2, &value) == 0);
		assert(*(int*)value == 333);
		assert(list_get_p(list_context_p, 3, &value) == 0);
		assert(*(int*)value == 111);
		assert(list_get_p(list_context_p, 4, &value) != 0);

		size_t index = 0;
		assert(list_index_p(list_context_p, 0, &aaa, &index) == 0);
		assert(index == 0);
		assert(list_index_p(list_context_p, index + 1, &aaa, &index) == 0);
		assert(index == 3);

		list_iter_p_t* list_iter_p = list_iter_new_p(list_context_p);
		assert(list_iter_p != NULL);
		assert(list_iter_get_p(list_iter_p, &index, &value) == 0);
		assert(index == 0); assert(*(int*)value == 111);
		assert(list_iter_get_p(list_iter_p, &index, &value) == 0);
		assert(index == 1); assert(*(int*)value == 222);
		assert(list_iter_get_p(list_iter_p, &index, &value) == 0);
		assert(index == 2); assert(*(int*)value == 333);
		assert(list_iter_get_p(list_iter_p, &index, &value) == 0);
		assert(index == 3); assert(*(int*)value == 111);
		assert(list_iter_get_p(list_iter_p, &index, &value) != 0);
		list_iter_delete_p(list_iter_p);

		assert(list_sort_p(list_context_p, 0) == 0);
		assert(list_index_p(list_context_p, 0, &aaa, &index) == 0);
		assert(index == 2);
		assert(list_sort_p(list_context_p, 1) == 0);
		assert(list_index_p(list_context_p, 0, &aaa, &index) == 0);
		assert(index == 0);

		assert(list_reverse_p(list_context_p) == 0);
		assert(list_index_p(list_context_p, 0, &aaa, &index) == 0);
		assert(index == 2);
		assert(list_reverse_p(list_context_p) == 0);
		assert(list_index_p(list_context_p, 0, &aaa, &index) == 0);
		assert(index == 0);

		assert(list_remove_value_p(list_context_p, &aaa) == 0);
		assert(list_has_value_p(list_context_p, &aaa) != 0);
		assert(list_remove_value_p(list_context_p, &bbb) == 0);
		assert(list_has_value_p(list_context_p, &bbb) != 0);
		assert(list_remove_value_p(list_context_p, &ddd) != 0);
		assert(list_has_value_p(list_context_p, &ddd) != 0);

		assert(list_count_p(list_context_p) == 1);

		assert(list_clear_p(list_context_p) == 0);
		assert(list_count_p(list_context_p) == 0);
	}

	list_delete_p(list_context_p);

	return 0;
}
