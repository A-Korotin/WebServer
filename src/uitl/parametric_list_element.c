//
// Created by Alexey on 29.01.2023.
//
#include "parametric_list_element.h"

inline union parametric_list_element ple_from_size_t(size_t element){
    return (union parametric_list_element) {.as_size_t = element};
}
inline union parametric_list_element ple_from_c_str(const char* element){
    return (union parametric_list_element) {.as_c_str = element};
}
inline union parametric_list_element ple_from_generic_pointer(void* element){
    return (union parametric_list_element) {.as_generic_pointer = element};
}


const struct ple_optional PLE_EMPTY = (struct ple_optional) { .exists = false };

struct ple_optional ple_of(union parametric_list_element element){
    return (struct ple_optional) { .exists = true, .element = element };
}
