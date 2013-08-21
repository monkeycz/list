#ifndef LIST_N_H
#define LIST_N_H

#include <stdlib.h>

@class NSObject;

typedef struct list_context list_context_n_t;
typedef struct list_iter list_iter_n_t;

#ifdef __cplusplus
extern "C" {
#endif

list_context_n_t* list_new_n(void);
list_context_n_t* list_new_length_n(size_t length);
void list_delete_n(list_context_n_t* context);

list_context_n_t* list_retain_n(list_context_n_t* context);
size_t list_retain_count_n(list_context_n_t* context);

list_context_n_t* list_copy_n(list_context_n_t* context);

int list_append_n(list_context_n_t* context, NSObject* value);
int list_insert_n(list_context_n_t* context, size_t index, NSObject* value);
int list_get_n(list_context_n_t* context, size_t index, NSObject** value);

int list_pop_n(list_context_n_t* context);
int list_remove_n(list_context_n_t* context, size_t index);
int list_remove_value_n(list_context_n_t* context, NSObject* value);
int list_clear_n(list_context_n_t* context);

int list_index_n(list_context_n_t* context, size_t begin, NSObject* value, size_t* index);
int list_has_value_n(list_context_n_t* context, NSObject* value);
size_t list_count_n(list_context_n_t* context);

int list_sort_n(list_context_n_t* context, int reverse);
int list_reverse_n(list_context_n_t* context);

list_iter_n_t* list_iter_new_n(list_context_n_t* context);
int list_iter_get_n(list_iter_n_t* iter, size_t* index, NSObject** value);
void list_iter_delete_n(list_iter_n_t* iter);

void list_print_n(list_context_n_t* context);

#ifdef __cplusplus
}
#endif

#endif /* LIST_N_H */