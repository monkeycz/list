#include <list/list_n.h>
#include <assert.h>
#import <Foundation/Foundation.h>

int main(int argc, char* argv[])
{
	list_context_n_t* list_context_n = list_new_n();
	assert(list_context_n != NULL);

	list_context_n_t* list_context_retain_n = list_retain_n(list_context_n);
	assert(list_retain_count_n(list_context_n) == 2);
	assert(list_retain_count_n(list_context_retain_n) == 2);
	list_delete_n(list_context_retain_n);
	assert(list_retain_count_n(list_context_n) == 1);
	assert(list_retain_count_n(list_context_retain_n) == 1);

	list_context_n_t* list_context_copy_n = list_copy_n(list_context_n);
	assert(list_context_copy_n != NULL);
	assert(list_retain_count_n(list_context_copy_n) == 1);
	list_delete_n(list_context_copy_n);

	NSObject* aaa = [[NSObject alloc] init];
	NSObject* bbb = [[NSObject alloc] init];
	NSObject* ccc = [[NSObject alloc] init];
	NSObject* ddd = [[NSObject alloc] init];

	for (int i = 0; i < 2; i++) {
		assert(list_append_n(list_context_n, aaa) == 0);
		assert(list_append_n(list_context_n, bbb) == 0);
		assert(list_append_n(list_context_n, ccc) == 0);

		assert(list_count_n(list_context_n) == 3);

		assert(list_has_value_n(list_context_n, aaa) == 0);
		assert(list_has_value_n(list_context_n, bbb) == 0);
		assert(list_has_value_n(list_context_n, ccc) == 0);
		assert(list_has_value_n(list_context_n, ddd) != 0);

		assert(list_pop_n(list_context_n) == 0);
		assert(list_remove_n(list_context_n, 0) == 0);
		assert(list_insert_n(list_context_n, 0, aaa) == 0);
		assert(list_insert_n(list_context_n, 9, ccc) == 0);
		assert(list_insert_n(list_context_n, 9, aaa) == 0);

		NSObject* value;
		assert(list_get_n(list_context_n, 0, &value) == 0);
		assert(value == aaa);
		assert(list_get_n(list_context_n, 1, &value) == 0);
		assert(value == bbb);
		assert(list_get_n(list_context_n, 2, &value) == 0);
		assert(value == ccc);
		assert(list_get_n(list_context_n, 3, &value) == 0);
		assert(value == aaa);
		assert(list_get_n(list_context_n, 4, &value) != 0);

		size_t index = 0;
		assert(list_index_n(list_context_n, 0, aaa, &index) == 0);
		assert(index == 0);
		assert(list_index_n(list_context_n, index + 1, aaa, &index) == 0);
		assert(index == 3);

		list_iter_n_t* list_iter_n = list_iter_new_n(list_context_n);
		assert(list_iter_n != NULL);
		assert(list_iter_get_n(list_iter_n, &index, &value) == 0);
		assert(index == 0); assert(value == aaa);
		assert(list_iter_get_n(list_iter_n, &index, &value) == 0);
		assert(index == 1); assert(value == bbb);
		assert(list_iter_get_n(list_iter_n, &index, &value) == 0);
		assert(index == 2); assert(value == ccc);
		assert(list_iter_get_n(list_iter_n, &index, &value) == 0);
		assert(index == 3); assert(value == aaa);
		assert(list_iter_get_n(list_iter_n, &index, &value) != 0);
		list_iter_delete_n(list_iter_n);

		assert(list_sort_n(list_context_n, 1) == 0);
		assert(list_index_n(list_context_n, 0, aaa, &index) == 0);
		assert(index == 2);
		assert(list_sort_n(list_context_n, 0) == 0);
		assert(list_index_n(list_context_n, 0, aaa, &index) == 0);
		assert(index == 0);

		assert(list_reverse_n(list_context_n) == 0);
		assert(list_index_n(list_context_n, 0, aaa, &index) == 0);
		assert(index == 2);
		assert(list_reverse_n(list_context_n) == 0);
		assert(list_index_n(list_context_n, 0, aaa, &index) == 0);
		assert(index == 0);

		assert(list_remove_value_n(list_context_n, aaa) == 0);
		assert(list_has_value_n(list_context_n, aaa) != 0);
		assert(list_remove_value_n(list_context_n, bbb) == 0);
		assert(list_has_value_n(list_context_n, bbb) != 0);
		assert(list_remove_value_n(list_context_n, ddd) != 0);
		assert(list_has_value_n(list_context_n, ddd) != 0);

		assert(list_count_n(list_context_n) == 1);

		assert(list_clear_n(list_context_n) == 0);
		assert(list_count_n(list_context_n) == 0);
	}

	[aaa release];
	[bbb release];
	[ccc release];
	[ddd release];

	list_delete_n(list_context_n);

	return 0;
}
