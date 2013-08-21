#ifndef LIST_P_H
#define LIST_P_H

#include <stdlib.h>



typedef struct list_context list_context_p_t;
typedef struct list_iter list_iter_p_t;

#ifdef __cplusplus
extern "C" {
#endif

list_context_p_t* list_new_p(void);
list_context_p_t* list_new_length_p(size_t length);
void list_delete_p(list_context_p_t* context);

list_context_p_t* list_retain_p(list_context_p_t* context);
size_t list_retain_count_p(list_context_p_t* context);

list_context_p_t* list_copy_p(list_context_p_t* context);

int list_append_p(list_context_p_t* context, void* value);
int list_insert_p(list_context_p_t* context, size_t index, void* value);
int list_get_p(list_context_p_t* context, size_t index, void** value);

int list_pop_p(list_context_p_t* context);
int list_remove_p(list_context_p_t* context, size_t index);
int list_remove_value_p(list_context_p_t* context, void* value);
int list_clear_p(list_context_p_t* context);

int list_index_p(list_context_p_t* context, size_t begin, void* value, size_t* index);
int list_has_value_p(list_context_p_t* context, void* value);
size_t list_count_p(list_context_p_t* context);

int list_sort_p(list_context_p_t* context, int reverse);
int list_reverse_p(list_context_p_t* context);

list_iter_p_t* list_iter_new_p(list_context_p_t* context);
int list_iter_get_p(list_iter_p_t* iter, size_t* index, void** value);
void list_iter_delete_p(list_iter_p_t* iter);

void list_print_p(list_context_p_t* context);

#ifdef __cplusplus
}
#endif

#endif /* LIST_P_H */