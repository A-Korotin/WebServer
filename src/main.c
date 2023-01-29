#include <stdio.h>

#include "linked_list.h"

void for_each(union parametric_datastructure_element element) {
    printf("%zu ", element.as_size_t);
}

union parametric_datastructure_element map_func(union parametric_datastructure_element element) {
    return (union parametric_datastructure_element) {.as_size_t=++element.as_size_t};
}

void print_optional_as_size_t(struct pde_optional element) {
    if (!element.exists) {
        puts("EMPTY");
        return;
    }
    printf("%zu\n", element.element.as_size_t);
}

int main() {
    size_t iter = 0;
    struct linked_list* list = list_create(pde_from_size_t(iter++));

    for (; iter < 10; ++iter) {
        list = list_push_back(list, pde_from_size_t(iter));
    }

    list = list_insert_at_index(list, 1, pde_from_size_t(10));

    list_for_each(list, for_each);
    return 0;
}
