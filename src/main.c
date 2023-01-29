#include <stdio.h>

#include "hash_map.h"

void for_each(union parametric_list_element element) {
    printf("%zu ", element.as_size_t);
}


void print_optional_as_size_t(struct ple_optional element) {
    if (!element.exists) {
        puts("EMPTY");
        return;
    }
    printf("%zu\n", element.element.as_size_t);
}

int main() {
    struct hash_map* map = hash_map_create(128);
    hash_map_put(map, "key1", ple_from_size_t(10));
    hash_map_put(map, "1key", ple_from_size_t(20));
    struct ple_optional anOptional = hash_map_get(map, "1key");
    print_optional_as_size_t(anOptional);
    return 0;
}
