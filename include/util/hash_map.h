#ifndef WEBSERVER_HASH_MAP_H
#define WEBSERVER_HASH_MAP_H
#include "parametric_list_element.h"
#include "linked_list.h"

#include <inttypes.h>

struct hash_map_entry {
    const char* key;
    union parametric_list_element value;
};

typedef size_t (hash_function)(const char*);
typedef bool (equals_function)(union parametric_list_element, union parametric_list_element);

struct hash_map;

struct hash_map *hash_map_create(size_t n_buckets);

void hash_map_destroy(struct hash_map*);

void hash_map_put(struct hash_map* map,
                  const char* key, union parametric_list_element value);

struct ple_optional hash_map_get(const struct hash_map* map, const char* key);

//
struct linked_list* hash_map_get_entries(const struct hash_map* map);

#endif //WEBSERVER_HASH_MAP_H
