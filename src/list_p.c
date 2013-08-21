#include <list/list_p.h>

#include <stdio.h>

#define LIST_VALUE_TYPE		void*
#include <list.h>

static int list_value_allocator_p(void* value, void** value_dup)
{
	*value_dup = value;
	return 0;
}

static int list_value_deallocator_p(void* value)
{
	return 0;
}

static int list_value_comparator_p(void* value_1, void* value_2)
{
	if (value_1 > value_2)
		return 1;
	else if (value_1 < value_2)
		return -1;
	else
		return 0;
}

static void list_value_printor_p(void* value)
{
	printf("<%p>", value);
}

list_context_p_t* list_new_p(void)
{
	return list_new_length_p(LIST_LENGTH_DEFAULT);
}

list_context_p_t* list_new_length_p(size_t length)
{
	return list_new(length, 
		list_value_allocator_p, list_value_deallocator_p, 
		list_value_comparator_p, list_value_printor_p);
}

void list_delete_p(list_context_p_t* context)
{
	list_delete(context);
}

list_context_p_t* list_retain_p(list_context_p_t* context)
{
	return list_retain(context);	
}

size_t list_retain_count_p(list_context_p_t* context)
{
	return list_retain_count(context);
}

list_context_p_t* list_copy_p(list_context_p_t* context)
{
	return list_copy(context);
}

int list_append_p(list_context_p_t* context, void* value)
{
	return list_append(context, value);
}

int list_insert_p(list_context_p_t* context, size_t index, void* value)
{
	return list_insert(context, index, value);
}

int list_get_p(list_context_p_t* context, size_t index, void** value)
{
	return list_get(context, index, value);
}

int list_pop_p(list_context_p_t* context)
{
	return list_pop(context);
}

int list_remove_p(list_context_p_t* context, size_t index)
{
	return list_remove(context, index);
}

int list_remove_value_p(list_context_p_t* context, void* value)
{
	return list_remove_value(context, value);
}

int list_clear_p(list_context_p_t* context)
{
	return list_clear(context);
}

int list_index_p(list_context_p_t* context, size_t begin, void* value, size_t* index)
{
	return list_index(context, begin, value, index);
}

int list_has_value_p(list_context_p_t* context, void* value)
{
	return list_has_value(context, value);
}

size_t list_count_p(list_context_p_t* context)
{
	return list_count(context);
}

int list_sort_p(list_context_p_t* context, int reverse)
{
	return list_sort(context, reverse);
}

int list_reverse_p(list_context_p_t* context)
{
	return list_reverse(context);
}

list_iter_p_t* list_iter_new_p(list_context_p_t* context)
{
	return list_iter_new(context);
}

int list_iter_get_p(list_iter_p_t* iter, size_t* index, void** value)
{
	return list_iter_get(iter, index, value);
}

void list_iter_delete_p(list_iter_p_t* iter)
{
	list_iter_delete(iter);
}

void list_print_p(list_context_p_t* context)
{
	list_print(context);
}