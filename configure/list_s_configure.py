
configure = {
	'PROJECT_NAME': 'list',
	'TYPE_NAME': 's',  

	'INCLUDE_FILE_SUFFIX': '.h', 
	'SRC_FILE_SUFFIX': '.c', 
 
	'INCLUDE_HEAD': '''
	''',
	'SRC_HEAD': '''
	#include <string.h>
	#include <stdio.h>
	''', 
 
	'VALUE_TYPE': 'char*',

	'VALUE_ALLOCATOR': '''
	*value_dup = strdup(value);
	return 0;
	''', 

	'VALUE_DEALLOCATOR': '''
	free(value);
	return 0;
	''', 

	'VALUE_COMPARATOR': '''
	return strcmp(value_1, value_2);
	''', 

	'VALUE_PRINTOR': '''
	printf("'%s'", value);
	''', 
}

try:
	configure['TYPE_NAME_U'] = configure['TYPE_NAME'].upper()
except Exception as e:
	print 'Missing configure parameter. (%s)' % e
