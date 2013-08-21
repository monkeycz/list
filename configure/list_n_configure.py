
configure = {
	'PROJECT_NAME': 'list',
	'TYPE_NAME': 'n',  

	'INCLUDE_FILE_SUFFIX': '.h', 
	'SRC_FILE_SUFFIX': '.m', 
 
	'INCLUDE_HEAD': '''
	@class NSObject;
	''',
	'SRC_HEAD': '''
	#import <Foundation/Foundation.h>
	#include <stdio.h>
	''', 
 
	'VALUE_TYPE': 'NSObject*',

	'VALUE_ALLOCATOR': '''
	*value_dup = [value retain];
	return 0;
	''', 

	'VALUE_DEALLOCATOR': '''
	[value release];
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
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	printf("%s", [[value description] UTF8String]);
	[pool release];
	''', 
}

try:
	configure['TYPE_NAME_U'] = configure['TYPE_NAME'].upper()
except Exception as e:
	print 'Missing configure parameter. (%s)' % e
