
configure = {
	'PROJECT_NAME': 'list',
	'TYPE_NAME': 'i',  

	'INCLUDE_FILE_SUFFIX': '.h', 
	'SRC_FILE_SUFFIX': '.c', 
 
	'INCLUDE_HEAD': '''
	''',
	'SRC_HEAD': '''
	#include <stdio.h>
	''', 
 
	'VALUE_TYPE': 'int',

	'VALUE_ALLOCATOR': '''
	*value_dup = value;
	return 0;
	''', 

	'VALUE_DEALLOCATOR': '''
	return 0;
	''', 

	'VALUE_COMPARATOR': '''
	if (value_1 > value_2)
		return 1;
	else if (value_1 < value_2)
		return -1;
	else
		return 0;
	''', 

	'VALUE_PRINTOR': '''
	printf("%d", value);
	''', 
}

try:
	configure['TYPE_NAME_U'] = configure['TYPE_NAME'].upper()
except Exception as e:
	print 'Missing configure parameter. (%s)' % e
