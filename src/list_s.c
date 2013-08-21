#include <list/list_s.h>

#include <string.h>
	#include <stdio.h>

#define LIST_VALUE_TYPE		char*
#include <list.h>

static int list_value_allocator_s(char* value, char** value_dup)
{
	*value_dup = strdup(value);
	return 0;
}

static int list_value_deallocator_s(char* value)
{
	free(value);
	return 0;
}

static int list_value_comparator_s(char* value_1, char* value_2)
{
	return strcmp(value_1, value_2);
}

static void list_value_printor_s(char* value)
{
	printf("'%s'", value);
}

list_context_s_t* list_new_s(void)
{
	return list_new_length_s(LIST_LENGTH_DEFAULT);
}

list_context_s_t* list_new_length_s(size_t length)
{
	return list_new(length, 
		list_value_allocator_s, list_value_deallocator_s, 
		list_value_comparator_s, list_value_printor_s);
}

void list_delete_s(list_context_s_t* context)
{
	list_delete(context);
}

list_context_s_t* list_retain_s(list_context_s_t* context)
{
	return list_retain(context);	
}

size_t list_retain_count_s(list_context_s_t* context)
{
	return list_retain_count(context);
}

list_context_s_t* list_copy_s(list_context_s_t* context)
{
	return list_copy(context);
}

int list_append_s(list_context_s_t* context, char* value)
{
	return list_append(context, value);
}

int list_insert_s(list_context_s_t* context, size_t index, char* value)
{
	return list_insert(context, index, value);
}

int list_get_s(list_context_s_t* context, size_t index, char** value)
{
	return list_get(context, index, value);
}

int list_pop_s(list_context_s_t* context)
{
	return list_pop(context);
}

int list_remove_s(list_context_s_t* context, size_t index)
{
	return list_remove(context, index);
}

int list_remove_value_s(list_context_s_t* context, char* value)
{
	return list_remove_value(context, value);
}

int list_clear_s(list_context_s_t* context)
{
	return list_clear(context);
}

int list_index_s(list_context_s_t* context, size_t begin, char* value, size_t* index)
{
	return list_index(context, begin, value, index);
}

int list_has_value_s(list_context_s_t* context, char* value)
{
	return list_has_value(context, value);
}

size_t list_count_s(list_context_s_t* context)
{
	return list_count(context);
}

int list_sort_s(list_context_s_t* context, int reverse)
{
	return list_sort(context, reverse);
}

int list_reverse_s(list_context_s_t* context)
{
	return list_reverse(context);
}

list_iter_s_t* list_iter_new_s(list_context_s_t* context)
{
	return list_iter_new(context);
}

int list_iter_get_s(list_iter_s_t* iter, size_t* index, char** value)
{
	return list_iter_get(iter, index, value);
}

void list_iter_delete_s(list_iter_s_t* iter)
{
	list_iter_delete(iter);
}

void list_print_s(list_context_s_t* context)
{
	list_print(context);
}