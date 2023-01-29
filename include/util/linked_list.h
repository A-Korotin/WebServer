#ifndef WEBSERVER_LINKED_LIST_H
#define WEBSERVER_LINKED_LIST_H
#include "parametric_list_element.h"

#include <corecrt.h>

typedef union parametric_list_element (list_map_function) (union parametric_list_element);
typedef void (list_for_each_func) (union parametric_list_element);
typedef void (list_modifying_for_each_func) (union parametric_list_element*, void*);
typedef bool (list_predicate_func) (union parametric_list_element, void*);

struct linked_list;

size_t list_size(const struct linked_list* list);

struct linked_list* list_create(union parametric_list_element initial);
void list_destroy(struct linked_list* list);

struct linked_list* list_insert_at_index(struct linked_list* list, size_t index, union parametric_list_element element);
struct linked_list* list_push_back(struct linked_list* list, union parametric_list_element element);
struct linked_list* list_push_front(struct linked_list* list, union parametric_list_element element);

struct ple_optional list_get_by_index(const struct linked_list* list, size_t index);
struct ple_optional list_get_first(const struct linked_list* list);
struct ple_optional list_get_last(const struct linked_list* list);

struct linked_list * list_map(const struct linked_list* list, list_map_function function);
void list_for_each(const struct linked_list* list, list_for_each_func func);
void list_modifying_for_each(struct linked_list* list, list_modifying_for_each_func func, void* external_param);
bool list_any(const struct linked_list*, list_predicate_func func, void* external_param);
bool list_all(const struct linked_list*, list_predicate_func func, void* external_param);

struct linked_list* list_copy(const struct linked_list* list);

#endif //WEBSERVER_LINKED_LIST_H
