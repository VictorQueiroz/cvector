cmake_minimum_required(VERSION 3.7.0)
project(cvector C)

set(CMAKE_C_STANDARD 90)

add_library(cvector SHARED src/vector.h include/cvector.h)
set_target_properties(cvector PROPERTIES LINKER_LANGUAGE C)
target_compile_options(cvector PRIVATE -Wall -Wextra -pedantic -Werror)
target_include_directories(cvector PRIVATE src)
target_include_directories(cvector PUBLIC include)

add_executable(cvector_test test/vector_test.c)
target_link_libraries(cvector_test cvector)