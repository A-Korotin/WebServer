#ifndef WEBSERVER_PARAMETRIC_DATASTRUCTURE_ELEMENT_H
#define WEBSERVER_PARAMETRIC_DATASTRUCTURE_ELEMENT_H
#include <inttypes.h>
#include <stdbool.h>

union parametric_datastructure_element {
    size_t as_size_t;
    const char* as_c_str;
};

extern inline union parametric_datastructure_element pde_from_size_t(size_t element);
extern inline union parametric_datastructure_element pde_from_c_str(const char* element);


struct pde_optional {
    bool exists;
    union parametric_datastructure_element element;
};

extern const struct pde_optional PDE_EMPTY;

struct pde_optional pde_of(union parametric_datastructure_element element);

#endif //WEBSERVER_PARAMETRIC_DATASTRUCTURE_ELEMENT_H
