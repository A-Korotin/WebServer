//
// Created by Alexey on 29.01.2023.
//
#include "linked_list.h"

#include <malloc.h>
#include <stdbool.h>


struct linked_list {
    struct linked_list* next;
    union parametric_datastructure_element value;
};

size_t list_size(const struct linked_list* list) {
    size_t size = 0;

    while (list) {
        list = list->next;
        size++;
    }
    return size;
}

static struct linked_list* init_node(union parametric_datastructure_element value) {
    struct linked_list* list = malloc(sizeof (struct linked_list));
    list->next = NULL;
    list->value = value;

    return list;
}

struct linked_list* list_create(union parametric_datastructure_element initial) {
    return init_node(initial);
}

void list_destroy(struct linked_list* list) {
    while(list) {
        struct linked_list* next = list->next;
        free(list);
        list = next;
    }
}

struct node_search_result {
    struct linked_list* result;
    bool exists;
};

static const struct node_search_result NSR_EMPTY = (struct node_search_result) {.exists = false};
inline static struct node_search_result nsr_of(struct linked_list* result) {
    return (struct node_search_result) {.exists = true, .result = result};
}

static struct node_search_result find_node_before_index(struct linked_list* list, size_t index) {
    size_t iter = 0;

    while(list) {
        if (iter++ == index - 1) {
            return nsr_of(list);
        }
        list = list->next;
    }

    return NSR_EMPTY;
}

static struct linked_list* find_last(const struct linked_list* list) {
    struct linked_list* cpy = (struct linked_list*) list;

    while (cpy->next) {
        cpy = cpy->next;
    }

    return cpy;
}

struct linked_list* list_insert_at_index(struct linked_list* list, size_t index, union parametric_datastructure_element element){
    struct linked_list* head = list;

    if (!list) {
        return NULL;
    }

    if (index == 0) {
        return list_push_front(list, element);
    }

    struct node_search_result result = find_node_before_index(list, index);
    struct linked_list* node_before = result.result;

    if (!result.exists) {
        node_before = find_last(list);
    }

    struct linked_list* new = init_node(element);
    new->next = node_before->next;
    node_before->next = new;

    return head;
}


struct linked_list* list_push_back(struct linked_list* list, union parametric_datastructure_element element){
    struct linked_list* last = find_last(list);
    struct linked_list* new = init_node(element);
    last->next = new;
    new->next = NULL;
    return list;
}
struct linked_list* list_push_front(struct linked_list* list, union parametric_datastructure_element element) {
    struct linked_list* new = init_node(element);
    new->next = list;
    return new;
}

struct pde_optional list_get_by_index(const struct linked_list* list, size_t index) {
    if (!list) {
        return PDE_EMPTY;
    }

    size_t iter = 0;
    while (list) {
        if (iter++ == index) {
            return pde_of(list->value);
        }
        list = list->next;
    }

    return PDE_EMPTY;
}
struct pde_optional list_get_first(const struct linked_list* list) {
    if (!list) {
        return PDE_EMPTY;
    }

    return pde_of(list->value);
}
struct pde_optional list_get_last(const struct linked_list* list){
    if (!list) {
        return PDE_EMPTY;
    }

    return pde_of(find_last(list)->value);
}

struct linked_list* list_map(struct linked_list* list, list_map_function function){
    if (!list) {
        return NULL;
    }

    struct linked_list* new_head = init_node(function(list->value));
    list = list->next;
    struct linked_list* iter = new_head;
    while (list) {
        struct linked_list* new_node = init_node(function(list->value));
        iter->next = new_node;
        iter = new_node;
        list = list->next;
    }

    return new_head;
}
void list_for_each(struct linked_list* list, list_for_each_func func) {
    if (!list) {
        return;
    }

    while (list) {
        func(list->value);
        list = list->next;
    }
}
