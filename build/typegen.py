
include_template = '''
#ifndef LIST_{TYPE_NAME_U}_H
#define LIST_{TYPE_NAME_U}_H

#include <stdlib.h>

{INCLUDE_HEAD}

typedef struct list_context list_context_{TYPE_NAME}_t;
typedef struct list_iter list_iter_{TYPE_NAME}_t;

#ifdef __cplusplus
extern "C" {
#endif

list_context_{TYPE_NAME}_t* list_new_{TYPE_NAME}(void);
list_context_{TYPE_NAME}_t* list_new_length_{TYPE_NAME}(size_t length);
void list_delete_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);

list_context_{TYPE_NAME}_t* list_retain_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);
size_t list_retain_count_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);

list_context_{TYPE_NAME}_t* list_copy_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);

int list_append_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, {VALUE_TYPE} value);
int list_insert_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, size_t index, {VALUE_TYPE} value);
int list_get_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, size_t index, {VALUE_TYPE}* value);

int list_pop_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);
int list_remove_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, size_t index);
int list_remove_value_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, {VALUE_TYPE} value);
int list_clear_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);

int list_index_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, size_t begin, {VALUE_TYPE} value, size_t* index);
int list_has_value_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, {VALUE_TYPE} value);
size_t list_count_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);

int list_sort_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, int reverse);
int list_reverse_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);

list_iter_{TYPE_NAME}_t* list_iter_new_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);
int list_iter_get_{TYPE_NAME}(list_iter_{TYPE_NAME}_t* iter, size_t* index, {VALUE_TYPE}* value);
void list_iter_delete_{TYPE_NAME}(list_iter_{TYPE_NAME}_t* iter);

void list_print_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context);

#ifdef __cplusplus
}
#endif

#endif /* LIST_{TYPE_NAME_U}_H */
'''

src_template = '''
#include <list/list_{TYPE_NAME}.h>

{SRC_HEAD}

#define LIST_VALUE_TYPE		{VALUE_TYPE}
#include <list.h>

static int list_value_allocator_{TYPE_NAME}({VALUE_TYPE} value, {VALUE_TYPE}* value_dup)
{
	{VALUE_ALLOCATOR}
}

static int list_value_deallocator_{TYPE_NAME}({VALUE_TYPE} value)
{
	{VALUE_DEALLOCATOR}
}

static int list_value_comparator_{TYPE_NAME}({VALUE_TYPE} value_1, {VALUE_TYPE} value_2)
{
	{VALUE_COMPARATOR}
}

static void list_value_printor_{TYPE_NAME}({VALUE_TYPE} value)
{
	{VALUE_PRINTOR}
}

list_context_{TYPE_NAME}_t* list_new_{TYPE_NAME}(void)
{
	return list_new_length_{TYPE_NAME}(LIST_LENGTH_DEFAULT);
}

list_context_{TYPE_NAME}_t* list_new_length_{TYPE_NAME}(size_t length)
{
	return list_new(length, 
		list_value_allocator_{TYPE_NAME}, list_value_deallocator_{TYPE_NAME}, 
		list_value_comparator_{TYPE_NAME}, list_value_printor_{TYPE_NAME});
}

void list_delete_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	list_delete(context);
}

list_context_{TYPE_NAME}_t* list_retain_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	return list_retain(context);	
}

size_t list_retain_count_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	return list_retain_count(context);
}

list_context_{TYPE_NAME}_t* list_copy_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	return list_copy(context);
}

int list_append_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, {VALUE_TYPE} value)
{
	return list_append(context, value);
}

int list_insert_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, size_t index, {VALUE_TYPE} value)
{
	return list_insert(context, index, value);
}

int list_get_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, size_t index, {VALUE_TYPE}* value)
{
	return list_get(context, index, value);
}

int list_pop_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	return list_pop(context);
}

int list_remove_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, size_t index)
{
	return list_remove(context, index);
}

int list_remove_value_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, {VALUE_TYPE} value)
{
	return list_remove_value(context, value);
}

int list_clear_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	return list_clear(context);
}

int list_index_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, size_t begin, {VALUE_TYPE} value, size_t* index)
{
	return list_index(context, begin, value, index);
}

int list_has_value_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, {VALUE_TYPE} value)
{
	return list_has_value(context, value);
}

size_t list_count_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	return list_count(context);
}

int list_sort_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context, int reverse)
{
	return list_sort(context, reverse);
}

int list_reverse_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	return list_reverse(context);
}

list_iter_{TYPE_NAME}_t* list_iter_new_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	return list_iter_new(context);
}

int list_iter_get_{TYPE_NAME}(list_iter_{TYPE_NAME}_t* iter, size_t* index, {VALUE_TYPE}* value)
{
	return list_iter_get(iter, index, value);
}

void list_iter_delete_{TYPE_NAME}(list_iter_{TYPE_NAME}_t* iter)
{
	list_iter_delete(iter);
}

void list_print_{TYPE_NAME}(list_context_{TYPE_NAME}_t* context)
{
	list_print(context);
}
'''

import sys, imp

def main():
	args = sys.argv[1:]
	if len(args) < 1:
		print '%s <configure_name>' % __file__
		print 'eg: %s xxxx_xx_configure' % __file__
		return

	try:
		configure_name = args[0]
		configure = imp.load_module(configure_name, *imp.find_module(configure_name)).configure
	except Exception as e:
		print 'Invalid configure file. (%s)' % e
		return

	try:
		include_filename = '%s_%s%s' % \
			(configure['PROJECT_NAME'], configure['TYPE_NAME'], configure['INCLUDE_FILE_SUFFIX'])
		with open(include_filename, 'w+') as f:
			global include_template
			include_code = include_template.strip()
			for k, v in configure.items():
				include_code = include_code.replace('{' + k + '}', v.strip())
			f.write(include_code)

		src_filename = '%s_%s%s' % \
			(configure['PROJECT_NAME'], configure['TYPE_NAME'], configure['SRC_FILE_SUFFIX'])
		with open(src_filename, 'w+') as f:
			global src_template
			src_code = src_template.strip()
			for k, v in configure.items():
				src_code = src_code.replace('{' + k + '}', v.strip())
			f.write(src_code)
	except Exception as e:
		print 'Failed to generate the code. (%s)' % e
		return

	print 'ok'
	print include_filename
	print src_filename

if __name__ == '__main__':
	main()
