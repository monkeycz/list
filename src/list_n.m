#include <list/list_n.h>

#import <Foundation/Foundation.h>
	#include <stdio.h>

#define LIST_VALUE_TYPE		NSObject*
#include <list.h>

static int list_value_allocator_n(NSObject* value, NSObject** value_dup)
{
	*value_dup = [value retain];
	return 0;
}

static int list_value_deallocator_n(NSObject* value)
{
	[value release];
	return 0;
}

static int list_value_comparator_n(NSObject* value_1, NSObject* value_2)
{
	if (value_1 > value_2)
		return 1;
	else if (value_1 < value_2)
		return -1;
	else
		return 0;
}

static void list_value_printor_n(NSObject* value)
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	printf("%s", [[value description] UTF8String]);
	[pool release];
}

list_context_n_t* list_new_n(void)
{
	return list_new_length_n(LIST_LENGTH_DEFAULT);
}

list_context_n_t* list_new_length_n(size_t length)
{
	return list_new(length, 
		list_value_allocator_n, list_value_deallocator_n, 
		list_value_comparator_n, list_value_printor_n);
}

void list_delete_n(list_context_n_t* context)
{
	list_delete(context);
}

list_context_n_t* list_retain_n(list_context_n_t* context)
{
	return list_retain(context);	
}

size_t list_retain_count_n(list_context_n_t* context)
{
	return list_retain_count(context);
}

list_context_n_t* list_copy_n(list_context_n_t* context)
{
	return list_copy(context);
}

int list_append_n(list_context_n_t* context, NSObject* value)
{
	return list_append(context, value);
}

int list_insert_n(list_context_n_t* context, size_t index, NSObject* value)
{
	return list_insert(context, index, value);
}

int list_get_n(list_context_n_t* context, size_t index, NSObject** value)
{
	return list_get(context, index, value);
}

int list_pop_n(list_context_n_t* context)
{
	return list_pop(context);
}

int list_remove_n(list_context_n_t* context, size_t index)
{
	return list_remove(context, index);
}

int list_remove_value_n(list_context_n_t* context, NSObject* value)
{
	return list_remove_value(context, value);
}

int list_clear_n(list_context_n_t* context)
{
	return list_clear(context);
}

int list_index_n(list_context_n_t* context, size_t begin, NSObject* value, size_t* index)
{
	return list_index(context, begin, value, index);
}

int list_has_value_n(list_context_n_t* context, NSObject* value)
{
	return list_has_value(context, value);
}

size_t list_count_n(list_context_n_t* context)
{
	return list_count(context);
}

int list_sort_n(list_context_n_t* context, int reverse)
{
	return list_sort(context, reverse);
}

int list_reverse_n(list_context_n_t* context)
{
	return list_reverse(context);
}

list_iter_n_t* list_iter_new_n(list_context_n_t* context)
{
	return list_iter_new(context);
}

int list_iter_get_n(list_iter_n_t* iter, size_t* index, NSObject** value)
{
	return list_iter_get(iter, index, value);
}

void list_iter_delete_n(list_iter_n_t* iter)
{
	list_iter_delete(iter);
}

void list_print_n(list_context_n_t* context)
{
	list_print(context);
}