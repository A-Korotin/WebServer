#ifndef WEBSERVER_LINKED_LIST_H
#define WEBSERVER_LINKED_LIST_H
#include "parametric_datastructure_element.h"

#include <corecrt.h>

typedef union parametric_datastructure_element (list_map_function) (union parametric_datastructure_element);
typedef void (list_for_each_func) (union parametric_datastructure_element);

struct linked_list;

size_t list_size(const struct linked_list* list);

struct linked_list* list_create(union parametric_datastructure_element initial);
void list_destroy(struct linked_list* list);

struct linked_list* list_insert_at_index(struct linked_list* list, size_t index, union parametric_datastructure_element element);
struct linked_list* list_push_back(struct linked_list* list, union parametric_datastructure_element element);
struct linked_list* list_push_front(struct linked_list* list, union parametric_datastructure_element element);

struct pde_optional list_get_by_index(const struct linked_list* list, size_t index);
struct pde_optional list_get_first(const struct linked_list* list);
struct pde_optional list_get_last(const struct linked_list* list);

struct linked_list * list_map(struct linked_list* list, list_map_function function);
void list_for_each(struct linked_list* list, list_for_each_func func);



#endif //WEBSERVER_LINKED_LIST_H
