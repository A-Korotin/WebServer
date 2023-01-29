#include "hash_map.h"

#include <malloc.h>
#include <string.h>


inline static struct hash_map_entry* entry_of(const char* key, union parametric_list_element value) {
    struct hash_map_entry* entry = malloc(sizeof (struct hash_map_entry));
    entry->key = key;
    entry->value = value;
    return entry;
}

static size_t c_str_hash_function(const char* c_str) {
    size_t hash = 0;
    size_t iter = 0;

    while(c_str[iter] != '\0') {
        hash += c_str[iter] * 127;
        iter++;
    }

    return hash;
}

static bool c_str_equals(const char* first, const char* second) {
    return strcmp(first, second) == 0;
}

struct hash_map {
    struct linked_list* entries;
    struct linked_list** buckets;

    size_t n_buckets;
};


struct hash_map *hash_map_create( size_t n_buckets) {
    struct hash_map* map = malloc(sizeof (struct hash_map));

    map->entries = NULL;
    map->buckets = malloc(sizeof (struct linked_list*) * n_buckets);

    map->n_buckets = n_buckets;
    for (size_t i = 0; i < n_buckets; ++i) {
        map->buckets[i] = NULL;
    }

    return map;
}

void entry_destroy(union parametric_list_element element) {
    free(element.as_generic_pointer);
}

void hash_map_destroy(struct hash_map* map) {
    if (!map) {
        return;
    }
    list_for_each(map->entries, entry_destroy);
    list_destroy(map->entries);

    for (size_t i = 0; i < map->n_buckets; ++i) {
        list_destroy(map->buckets[i]);
    }
}

inline static size_t get_bucket_idx(const struct hash_map* map, const char* key) {
    return c_str_hash_function(key) & (map->n_buckets - 1);
}

inline static bool repeated_entry(struct hash_map_entry* entry, const char* key_to_check) {
    return c_str_equals(entry->key, key_to_check);
}


static bool collision_predicate(union parametric_list_element element, void* entry) {
    struct hash_map_entry* first_entry = (struct hash_map_entry*) element.as_generic_pointer;
    struct hash_map_entry* second_entry = (struct hash_map_entry*) entry;
    return c_str_equals(first_entry->key, second_entry->key);
}

static void bucket_update_func(union parametric_list_element* element, void* entry) {
    struct hash_map_entry* original = (struct hash_map_entry*) element->as_generic_pointer;
    struct hash_map_entry* new = (struct hash_map_entry*) entry;

    // collision
    if (c_str_equals(original->key, new->key)) {
        free(original);
        element->as_generic_pointer = new;
    }
}

void hash_map_put(struct hash_map* map,
                  const char *key, union parametric_list_element value) {

    size_t index = get_bucket_idx(map, key);
    struct linked_list* bucket = map->buckets[index];
    struct hash_map_entry* entry = entry_of(key, value);
    if (bucket == NULL) {
        map->buckets[index] = list_create(ple_from_generic_pointer(entry));
        return;
    }

    // no collision
    if (!list_any(bucket, collision_predicate, entry)) {
        list_push_back(bucket, ple_from_generic_pointer(entry));
        return;
    }
    // collision occurred
    list_modifying_for_each(bucket, bucket_update_func, entry);
}

static bool entry_check_predicate(union parametric_list_element element, void* key) {
    struct hash_map_entry* entry = (struct hash_map_entry*) element.as_generic_pointer;

    return c_str_equals(entry->key, (const char*) key);

}

struct ple_optional hash_map_get(const struct hash_map* map, const char *key) {
    size_t index = get_bucket_idx(map, key);
    struct linked_list* bucket = map->buckets[index];
    // key is not in the entry list
    if(!list_any(bucket, entry_check_predicate, (void*) key)) {
        return PLE_EMPTY;
    }
    // key is in the entry list
    size_t size = list_size(bucket);

    for (size_t i = 0; i < size; ++i) {
        struct hash_map_entry* entry = (struct hash_map_entry*) list_get_by_index(bucket, i).element.as_generic_pointer;
        if (c_str_equals(entry->key, key)) {
            return ple_of(entry->value);
        }
    }
    return PLE_EMPTY;
}


struct linked_list* hash_map_get_entries(const struct hash_map* map) {
    return list_copy(map->entries);
}

