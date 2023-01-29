cmake_minimum_required(VERSION 3.24)
project(WebServer C)

set(CMAKE_C_STANDARD 17)

set(LINKED_LIST_SOURCES
        include/util/linked_list.h
        include/util/parametric_list_element.h
        src/util/parametric_list_element.c
        src/util/linked_list.c)

set(HASH_MAP_SOURCES
        include/util/hash_map.h
        src/util/hash_map.c)

set(MAIN src/main.c)

include_directories(SYSTEM ./include/util/)
add_executable(WebServer ${LINKED_LIST_SOURCES} ${HASH_MAP_SOURCES} ${MAIN})
