#ifndef LIST_H
#define LIST_H

/* ************************** INCLUDE BEGIN *************************** */

#include <stdlib.h>

#ifndef LIST_VALUE_TYPE
#error NO define LIST_VALUE_TYPE, eg: `#define LIST_VALUE_TYPE int`
#endif

#if 0
#define LIST_VALUE_TYPE		void*
#endif

#define LIST_LENGTH_DEFAULT 1024

typedef struct list_context list_context_t;
typedef struct list_iter list_iter_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*list_value_allocator)(LIST_VALUE_TYPE, LIST_VALUE_TYPE*);
typedef int (*list_value_deallocator)(LIST_VALUE_TYPE);
typedef int (*list_value_comparator)(LIST_VALUE_TYPE, LIST_VALUE_TYPE);
typedef void (*list_value_printor)(LIST_VALUE_TYPE);

static list_context_t* list_new(size_t length, 
	list_value_allocator value_allocator, list_value_deallocator value_deallocator, 
	list_value_comparator value_comparator, list_value_printor value_printor);
static void list_delete(list_context_t* context);

static list_context_t* list_retain(list_context_t* context);
static size_t list_retain_count(list_context_t* context);

static list_context_t* list_copy(list_context_t* context);

static int list_append(list_context_t* context, LIST_VALUE_TYPE value);
static int list_insert(list_context_t* context, size_t index, LIST_VALUE_TYPE value);
static int list_get(list_context_t* context, size_t index, LIST_VALUE_TYPE* value);

static int list_pop(list_context_t* context);
static int list_remove(list_context_t* context, size_t index);
static int list_remove_value(list_context_t* context, LIST_VALUE_TYPE value);
static int list_clear(list_context_t* context);

static int list_index(list_context_t* context, size_t begin, LIST_VALUE_TYPE value, size_t* index);
static int list_has_value(list_context_t* context, LIST_VALUE_TYPE value);
static size_t list_count(list_context_t* context);

static int list_sort(list_context_t* context, int reverse);
static int list_reverse(list_context_t* context);

static list_iter_t* list_iter_new(list_context_t* context);
static int list_iter_get(list_iter_t* iter, size_t* index, LIST_VALUE_TYPE* value);
static void list_iter_delete(list_iter_t* iter);

static void list_print(list_context_t* context);

#ifdef __cplusplus
}
#endif

/* *************************** INCLUDE END **************************** */

/* **************************** SRC BEGIN ***************************** */

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

struct list_context
{
	pthread_mutex_t mutex;

	size_t retain_count;

	LIST_VALUE_TYPE* value_list;
	size_t length;
	size_t count;

	list_value_allocator value_allocator;
	list_value_deallocator value_deallocator;
	list_value_comparator value_comparator;
	list_value_printor value_printor;
};

struct list_iter
{
	pthread_mutex_t mutex;

	list_context_t* context;

	size_t count;
	size_t index;
};

static int list_value_allocator_default(LIST_VALUE_TYPE value, LIST_VALUE_TYPE* value_dup)
{
	*value_dup = value;
	return 0;
}

static int list_value_deallocator_default(LIST_VALUE_TYPE value)
{
	return 0;
}

static int list_value_comparator_default(LIST_VALUE_TYPE value_1, LIST_VALUE_TYPE value_2)
{
	if (value_1 > value_2)
		return 1;
	else if (value_1 < value_2)
		return -1;
	else
		return 0;
}

static void list_value_printor_default(LIST_VALUE_TYPE value)
{
	printf("v");
}

static list_context_t* list_new(size_t length, 
	list_value_allocator value_allocator, list_value_deallocator value_deallocator, 
	list_value_comparator value_comparator, list_value_printor value_printor)
{
	list_context_t* context = (list_context_t*)malloc(sizeof(list_context_t));
	if (context == NULL)
		goto __list_new_failed_1;

	if (pthread_mutex_init(&context->mutex, NULL) != 0)
		goto __list_new_failed_2;

	context->retain_count = 1;

	context->value_list = calloc(length, sizeof(LIST_VALUE_TYPE));
	if (context->value_list == NULL)
		goto __list_new_failed_3;
	context->length = length;
	context->count = 0;

	context->value_allocator = value_allocator == NULL ? 
		list_value_allocator_default : value_allocator;
	context->value_deallocator = value_deallocator == NULL ? 
		list_value_deallocator_default : value_deallocator;
	context->value_comparator = value_comparator == NULL ? 
		list_value_comparator_default : value_comparator;
	context->value_printor = value_printor == NULL ? 
		list_value_printor_default : value_printor;

	return context;

__list_new_failed_4:
	free(context->value_list);

__list_new_failed_3:
	pthread_mutex_destroy(&context->mutex);

__list_new_failed_2:
	free(context);

__list_new_failed_1:
	return NULL;
}

static void list_delete(list_context_t* context)
{
	if (context == NULL)
		return;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return;

	if (context->retain_count > 1) {
		context->retain_count--;
		pthread_mutex_unlock(&context->mutex);
		return;
	}

	for (size_t i = 0; i < context->count; i++) {
		context->value_deallocator(context->value_list[i]);
	}

	if (context->value_list != NULL)
		free(context->value_list);

	pthread_mutex_unlock(&context->mutex);

	pthread_mutex_destroy(&context->mutex);

	free(context);
}

static list_context_t* list_retain(list_context_t* context)
{
	if (context == NULL)
		return NULL;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return NULL;

	context->retain_count++;

	pthread_mutex_unlock(&context->mutex);

	return context;
}

static size_t list_retain_count(list_context_t* context)
{
	if (context == NULL)
		return 0;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return 0;

	size_t retain_count = context->retain_count;

	pthread_mutex_unlock(&context->mutex);

	return retain_count;
}

static list_context_t* list_copy(list_context_t* context)
{
	if (context == NULL)
		return NULL;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return NULL;

	list_context_t* new_context = list_new(context->length, 
		context->value_allocator, context->value_deallocator, 
		context->value_comparator, context->value_printor);
	if (new_context != NULL) {
		for (size_t i = 0; i < context->count; i++) {
			if (list_append(new_context, context->value_list[i]) != 0) {
				list_delete(new_context);
				new_context = NULL;
				break;
			}
		}
	}

	pthread_mutex_unlock(&context->mutex);

	return new_context;
}

static int list_append(list_context_t* context, LIST_VALUE_TYPE value)
{
	if (context == NULL)
		goto __list_append_failed_1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		goto __list_append_failed_1;

	if (context->count + 1 > context->length)
		goto __list_append_failed_2;

	LIST_VALUE_TYPE value_dup;

	if (context->value_allocator(value, &value_dup) != 0)
		goto __list_append_failed_2;

	context->value_list[context->count] = value_dup;

	context->count++;

	pthread_mutex_unlock(&context->mutex);

	return 0;

__list_append_failed_3:
	context->value_deallocator(value_dup);

__list_append_failed_2:
	pthread_mutex_unlock(&context->mutex);

__list_append_failed_1:
	return -1;
}

static int list_insert(list_context_t* context, size_t index, LIST_VALUE_TYPE value)
{
	if (context == NULL)
		goto __list_insert_failed_1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		goto __list_insert_failed_1;

	if (context->count + 1 > context->length)
		goto __list_insert_failed_2;

	LIST_VALUE_TYPE value_dup;

	if (context->value_allocator(value, &value_dup) != 0)
		goto __list_insert_failed_2;

	if (context->count <= 0 || index >= context->count) {
		context->value_list[context->count] = value_dup;
	} else {
		for (size_t i = context->count - 1; i >= index; i--) {
			context->value_list[i + 1] = context->value_list[i];
			if (i <= 0)
				break;
		}
		context->value_list[index] = value_dup;
	}

	context->count++;

	pthread_mutex_unlock(&context->mutex);

	return 0;

__list_insert_failed_3:
	context->value_deallocator(value_dup);

__list_insert_failed_2:
	pthread_mutex_unlock(&context->mutex);

__list_insert_failed_1:
	return -1;
}

static int list_get(list_context_t* context, size_t index, LIST_VALUE_TYPE* value)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	bool is_existed = false;

	if (index < context->count) {
		is_existed = true;
		if (value != NULL)
			*value = context->value_list[index];
	}

	pthread_mutex_unlock(&context->mutex);

	return is_existed ? 0 : 1;
}

static int list_pop(list_context_t* context)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	bool is_existed = false;

	if (context->count > 0) {
		is_existed = true;

		context->value_deallocator(context->value_list[context->count - 1]);
		context->count--;
	}

	pthread_mutex_unlock(&context->mutex);

	return is_existed ? 0 : 1;
}

static int list_remove(list_context_t* context, size_t index)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	bool is_existed = false;

	if (index < context->count) {
		is_existed = true;

		context->value_deallocator(context->value_list[index]);

		for (size_t i = index; i + 1 < context->count; i++)
			context->value_list[i] = context->value_list[i + 1];

		context->count--;		
	}

	pthread_mutex_unlock(&context->mutex);

	return is_existed ? 0 : 1;
}

static int list_remove_value(list_context_t* context, LIST_VALUE_TYPE value)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	bool is_existed = false;

	for (size_t i = 0; i < context->count; ) {
		if (context->value_comparator(context->value_list[i], value) == 0) {
			is_existed = true;

			context->value_deallocator(context->value_list[i]);

			for (size_t l = i; l + 1 < context->count; l++)
				context->value_list[l] = context->value_list[l + 1];

			context->count--;
		} else {
			i++;
		}
	}

	pthread_mutex_unlock(&context->mutex);

	return is_existed ? 0 : 1;
}

static int list_clear(list_context_t* context)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;	

	for (size_t i = 0; i < context->count; i++)
		context->value_deallocator(context->value_list[i]);
	context->count = 0;

	pthread_mutex_unlock(&context->mutex);

	return 0;
}

static int list_index(list_context_t* context, size_t begin, LIST_VALUE_TYPE value, size_t* index)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	bool is_existed = false;

	for (size_t i = begin; i < context->count; i++) {
		if (context->value_comparator(context->value_list[i], value) == 0) {
			is_existed = true;
			if (index != NULL)
				*index = i;
			break;
		}
	}

	pthread_mutex_unlock(&context->mutex);

	return is_existed ? 0 : 1;
}

static int list_has_value(list_context_t* context, LIST_VALUE_TYPE value)
{
	return list_index(context, 0, value, NULL);
}

static size_t list_count(list_context_t* context)
{
	if (context == NULL)
		return 0;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return 0;

	size_t count = context->count;

	pthread_mutex_unlock(&context->mutex);

	return count;
}

static int list_sort(list_context_t* context, int reverse)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	for (size_t i = context->count; i > 0; i--) {
		for (size_t l = 0; l < i - 1; l++) {
			LIST_VALUE_TYPE value_left = context->value_list[l];
			LIST_VALUE_TYPE value_right = context->value_list[l + 1];
			int result = context->value_comparator(value_left, value_right);
			if ((reverse == 0 && result > 0) || (reverse != 0 && result < 0)) {
				context->value_list[l] = value_right;
				context->value_list[l + 1] = value_left;
			}
		}
	}

	pthread_mutex_unlock(&context->mutex);

	return 0;
}

static int list_reverse(list_context_t* context)
{
	if (context == NULL)
		return -1;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return -1;

	for (size_t i = 0; i < context->count / 2; i++) {
		LIST_VALUE_TYPE value_left = context->value_list[i];
		LIST_VALUE_TYPE value_right = context->value_list[context->count - 1 - i];
		context->value_list[i] = value_right;
		context->value_list[context->count - 1 - i] = value_left;
	}

	pthread_mutex_unlock(&context->mutex);

	return 0;
}

static list_iter_t* list_iter_new(list_context_t* context)
{
	if (context == NULL)
		goto __list_iter_new_failed_1;

	list_iter_t* iter = (list_iter_t*)malloc(sizeof(list_iter_t));
	if (iter == NULL)
		goto __list_iter_new_failed_1;

	if (pthread_mutex_init(&iter->mutex, NULL) != 0)
		goto __list_iter_new_failed_2;

	iter->context = list_retain(context);
	if (iter->context == NULL)
		goto __list_iter_new_failed_3;

	iter->count = iter->context->count;
	iter->index = 0;

	return iter;

__list_iter_new_failed_4:
	list_delete(iter->context);

__list_iter_new_failed_3:
	pthread_mutex_destroy(&iter->mutex);

__list_iter_new_failed_2:
	free(iter);

__list_iter_new_failed_1:
	return NULL;
}

static int list_iter_get(list_iter_t* iter, size_t* index, LIST_VALUE_TYPE* value)
{
	if (iter == NULL)
		return -1;

	if (pthread_mutex_lock(&iter->mutex) != 0)
		return -1;

	if (iter->count != iter->context->count) {
		pthread_mutex_unlock(&iter->mutex);
		return -1;
	}

	if (iter->index >= iter->count) {
		pthread_mutex_unlock(&iter->mutex);
		return 1;
	}

	if (index != NULL)
		*index = iter->index;
	if (value != NULL)
		*value = iter->context->value_list[iter->index];

	iter->index++;

	pthread_mutex_unlock(&iter->mutex);

	return 0;
}

static void list_iter_delete(list_iter_t* iter)
{
	if (iter == NULL)
		return;

	if (pthread_mutex_lock(&iter->mutex) != 0)
		return;

	list_delete(iter->context);

	pthread_mutex_unlock(&iter->mutex);

	pthread_mutex_destroy(&iter->mutex);

	free(iter);
}

static void list_print(list_context_t* context)
{
	if (context == NULL)
		return;

	if (pthread_mutex_lock(&context->mutex) != 0)
		return;

	printf("[");
	for (size_t i = 0; i < context->count; i++) {
		if (i != 0)
			printf(", ");
		context->value_printor(context->value_list[i]);
	}
	printf("]\n");

	pthread_mutex_unlock(&context->mutex);
}

/* ***************************** SRC END ****************************** */

#endif /* LIST_H */