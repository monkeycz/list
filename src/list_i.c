#include <list/list_i.h>

#include <stdio.h>

#define LIST_VALUE_TYPE		int
#include <list.h>

static int list_value_allocator_i(int value, int* value_dup)
{
	*value_dup = value;
	return 0;
}

static int list_value_deallocator_i(int value)
{
	return 0;
}

static int list_value_comparator_i(int value_1, int value_2)
{
	if (value_1 > value_2)
		return 1;
	else if (value_1 < value_2)
		return -1;
	else
		return 0;
}

static void list_value_printor_i(int value)
{
	printf("%d", value);
}

list_context_i_t* list_new_i(void)
{
	return list_new_length_i(LIST_LENGTH_DEFAULT);
}

list_context_i_t* list_new_length_i(size_t length)
{
	return list_new(length, 
		list_value_allocator_i, list_value_deallocator_i, 
		list_value_comparator_i, list_value_printor_i);
}

void list_delete_i(list_context_i_t* context)
{
	list_delete(context);
}

list_context_i_t* list_retain_i(list_context_i_t* context)
{
	return list_retain(context);	
}

size_t list_retain_count_i(list_context_i_t* context)
{
	return list_retain_count(context);
}

list_context_i_t* list_copy_i(list_context_i_t* context)
{
	return list_copy(context);
}

int list_append_i(list_context_i_t* context, int value)
{
	return list_append(context, value);
}

int list_insert_i(list_context_i_t* context, size_t index, int value)
{
	return list_insert(context, index, value);
}

int list_get_i(list_context_i_t* context, size_t index, int* value)
{
	return list_get(context, index, value);
}

int list_pop_i(list_context_i_t* context)
{
	return list_pop(context);
}

int list_remove_i(list_context_i_t* context, size_t index)
{
	return list_remove(context, index);
}

int list_remove_value_i(list_context_i_t* context, int value)
{
	return list_remove_value(context, value);
}

int list_clear_i(list_context_i_t* context)
{
	return list_clear(context);
}

int list_index_i(list_context_i_t* context, size_t begin, int value, size_t* index)
{
	return list_index(context, begin, value, index);
}

int list_has_value_i(list_context_i_t* context, int value)
{
	return list_has_value(context, value);
}

size_t list_count_i(list_context_i_t* context)
{
	return list_count(context);
}

int list_sort_i(list_context_i_t* context, int reverse)
{
	return list_sort(context, reverse);
}

int list_reverse_i(list_context_i_t* context)
{
	return list_reverse(context);
}

list_iter_i_t* list_iter_new_i(list_context_i_t* context)
{
	return list_iter_new(context);
}

int list_iter_get_i(list_iter_i_t* iter, size_t* index, int* value)
{
	return list_iter_get(iter, index, value);
}

void list_iter_delete_i(list_iter_i_t* iter)
{
	list_iter_delete(iter);
}

void list_print_i(list_context_i_t* context)
{
	list_print(context);
}