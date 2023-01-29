#ifndef WEBSERVER_PARAMETRIC_LIST_ELEMENT_H
#define WEBSERVER_PARAMETRIC_LIST_ELEMENT_H
#include <inttypes.h>
#include <stdbool.h>


union parametric_list_element {
    size_t as_size_t;
    const char* as_c_str;
    void* as_generic_pointer;
};


extern inline union parametric_list_element ple_from_size_t(size_t element);
extern inline union parametric_list_element ple_from_c_str(const char* element);
extern inline union parametric_list_element ple_from_generic_pointer(void* element);


struct ple_optional {
    bool exists;
    union parametric_list_element element;
};

extern const struct ple_optional PLE_EMPTY;

struct ple_optional ple_of(union parametric_list_element element);

#endif //WEBSERVER_PARAMETRIC_LIST_ELEMENT_H
