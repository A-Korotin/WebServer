cmake_minimum_required(VERSION 3.24)
project(WebServer C)

set(CMAKE_C_STANDARD 17)


include_directories(SYSTEM ./include/util/)
add_executable(WebServer src/main.c include/util/linked_list.h include/util/parametric_list_element.h src/uitl/linked_list.c src/uitl/parametric_list_element.c include/util/hash_map.h src/uitl/hash_map.c)
