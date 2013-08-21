#ifndef LIST_S_H
#define LIST_S_H

#include <stdlib.h>



typedef struct list_context list_context_s_t;
typedef struct list_iter list_iter_s_t;

#ifdef __cplusplus
extern "C" {
#endif

list_context_s_t* list_new_s(void);
list_context_s_t* list_new_length_s(size_t length);
void list_delete_s(list_context_s_t* context);

list_context_s_t* list_retain_s(list_context_s_t* context);
size_t list_retain_count_s(list_context_s_t* context);

list_context_s_t* list_copy_s(list_context_s_t* context);

int list_append_s(list_context_s_t* context, char* value);
int list_insert_s(list_context_s_t* context, size_t index, char* value);
int list_get_s(list_context_s_t* context, size_t index, char** value);

int list_pop_s(list_context_s_t* context);
int list_remove_s(list_context_s_t* context, size_t index);
int list_remove_value_s(list_context_s_t* context, char* value);
int list_clear_s(list_context_s_t* context);

int list_index_s(list_context_s_t* context, size_t begin, char* value, size_t* index);
int list_has_value_s(list_context_s_t* context, char* value);
size_t list_count_s(list_context_s_t* context);

int list_sort_s(list_context_s_t* context, int reverse);
int list_reverse_s(list_context_s_t* context);

list_iter_s_t* list_iter_new_s(list_context_s_t* context);
int list_iter_get_s(list_iter_s_t* iter, size_t* index, char** value);
void list_iter_delete_s(list_iter_s_t* iter);

void list_print_s(list_context_s_t* context);

#ifdef __cplusplus
}
#endif

#endif /* LIST_S_H */