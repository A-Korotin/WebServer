//
// Created by Alexey on 29.01.2023.
//
#include "parametric_datastructure_element.h"

inline union parametric_datastructure_element pde_from_size_t(size_t element){
    return (union parametric_datastructure_element) {.as_size_t = element};
}
inline union parametric_datastructure_element pde_from_c_str(const char* element){
    return (union parametric_datastructure_element) {.as_c_str = element};
}

const struct pde_optional PDE_EMPTY = (struct pde_optional) { .exists = false };

struct pde_optional pde_of(union parametric_datastructure_element element){
    return (struct pde_optional) { .exists = true, .element = element };
}
