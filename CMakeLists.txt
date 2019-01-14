cmake_minimum_required(VERSION 2.0)
project(cvector C)

set(CMAKE_C_STANDARD 90)

add_library(cvector SHARED src/vector.h)
set_target_properties(cvector PROPERTIES LINKER_LANGUAGE C)
target_compile_options(cvector PRIVATE -pedantic -Werror)
target_include_directories(cvector PUBLIC src)

add_executable(cvector_test test/vector_test.c)
target_link_libraries(cvector_test cvector)