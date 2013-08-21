
configure = {
	'PROJECT_NAME': 'list',
	'TYPE_NAME': 'p',  

	'INCLUDE_FILE_SUFFIX': '.h', 
	'SRC_FILE_SUFFIX': '.c', 
 
	'INCLUDE_HEAD': '''
	''',
	'SRC_HEAD': '''
	#include <stdio.h>
	''', 
 
	'VALUE_TYPE': 'void*',

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
	printf("<%p>", value);
	''', 
}

try:
	configure['TYPE_NAME_U'] = configure['TYPE_NAME'].upper()
except Exception as e:
	print 'Missing configure parameter. (%s)' % e
