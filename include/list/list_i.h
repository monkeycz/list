#ifndef LIST_I_H
#define LIST_I_H

#include <stdlib.h>



typedef struct list_context list_context_i_t;
typedef struct list_iter list_iter_i_t;

#ifdef __cplusplus
extern "C" {
#endif

list_context_i_t* list_new_i(void);
list_context_i_t* list_new_length_i(size_t length);
void list_delete_i(list_context_i_t* context);

list_context_i_t* list_retain_i(list_context_i_t* context);
size_t list_retain_count_i(list_context_i_t* context);

list_context_i_t* list_copy_i(list_context_i_t* context);

int list_append_i(list_context_i_t* context, int value);
int list_insert_i(list_context_i_t* context, size_t index, int value);
int list_get_i(list_context_i_t* context, size_t index, int* value);

int list_pop_i(list_context_i_t* context);
int list_remove_i(list_context_i_t* context, size_t index);
int list_remove_value_i(list_context_i_t* context, int value);
int list_clear_i(list_context_i_t* context);

int list_index_i(list_context_i_t* context, size_t begin, int value, size_t* index);
int list_has_value_i(list_context_i_t* context, int value);
size_t list_count_i(list_context_i_t* context);

int list_sort_i(list_context_i_t* context, int reverse);
int list_reverse_i(list_context_i_t* context);

list_iter_i_t* list_iter_new_i(list_context_i_t* context);
int list_iter_get_i(list_iter_i_t* iter, size_t* index, int* value);
void list_iter_delete_i(list_iter_i_t* iter);

void list_print_i(list_context_i_t* context);

#ifdef __cplusplus
}
#endif

#endif /* LIST_I_H */