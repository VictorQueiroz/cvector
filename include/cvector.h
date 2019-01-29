#ifndef CVECTOR_PUBLIC_HEADER_H
#define CVECTOR_PUBLIC_HEADER_H

#include <stdint.h>
#include <string.h>

typedef size_t cvector_size_t;

#define CVECTOR_OK 0
#define CVECTOR_MEMORY_ALLOCATION_FAILED -1
#define CVECTOR_INVALID_LIST_OFFSET -2

#define CVECTOR_SUCCESS_OR_RETURN_ERROR(error) \
    if(error != CVECTOR_OK) {\
        return error;\
    }

#define CVECTOR_INIT(ptr, type) \
    ptr->item_length = sizeof(type);\
    ptr->offset = 0;\
    ptr->capacity = 32;\
    ptr->data = (type*) malloc(ptr->item_length*ptr->capacity);\
    if(ptr->data == NULL) {\
        return CVECTOR_MEMORY_ALLOCATION_FAILED;\
    }

#define vector_get(l, i) CVECTOR_GET(list, i)

#define vector_push_back(l, i) vector(l, i)

#define vector_add(list, item) vector_insert_at(list, item, list->offset)

#define CVECTOR_GET(list, index) list->data[index]

#define CVECTOR_LENGTH(list) list->offset

#define vector_foreach(list, index_var) \
    cvector_size_t index_var;\
    for(index_var = 0; index_var < list->offset; index_var++)

#define CVECTOR_STRUCT_PARAMS(type) \
    cvector_size_t capacity;\
    cvector_size_t offset;\
    cvector_size_t item_length;\
    type* data;

#define CVECTOR_HEAD_STRUCT(listname, typename) \
    typedef struct {\
        CVECTOR_STRUCT_PARAMS(typename)\
    } listname;

#define CVECTOR_DECLARATIONS(listname, typename) \
    int listname##_init(listname* list);\
    listname* listname##_alloc();\
    void listname##_destroy(listname* list);\
    void listname##_free(listname* list);\
    int listname##_add(listname* list, typename item);\
    cvector_size_t listname##_length(listname* list);\
    typename listname##_get(listname* list, cvector_size_t i);\
    int listname##_remove(listname* list, cvector_size_t index);\
    cvector_size_t listname##_index_of(listname* list, typename target_item);\
    void listname##_free_items(listname* list);\
    int listname##_insert_at(listname* list, typename item, cvector_size_t dest);\
    int listname##_move(listname* list, cvector_size_t src, cvector_size_t dest);

#define CVECTOR_HEAD(listname, typename) \
    CVECTOR_HEAD_STRUCT(listname, typename)\
    CVECTOR_DECLARATIONS(listname, typename)

#define CVECTOR_REMOVE(list, index) \
    if(index > (list->offset - 1)) return CVECTOR_INVALID_LIST_OFFSET;\
    cvector_size_t i;\
    for(i = index; i < list->offset - 1; i++) {\
        list->data[i] = list->data[i + 1];\
    }\
    list->offset--;\
    return CVECTOR_OK;

#define vector_insert_at(list, item, index) \
    if((list->capacity - list->offset) <= 1) {\
        list->capacity += 32;\
        list->data = realloc(list->data, list->item_length*list->capacity);\
        if(list->data == NULL) {\
            return CVECTOR_MEMORY_ALLOCATION_FAILED;\
        }\
    }\
    {\
        cvector_size_t i;\
        for(i = index; i < list->offset; i++) {\
            list->data[list->offset - i] = list->data[(list->offset - 1) - i];\
        }\
    }\
    list->data[index] = item;\
    list->offset++;\
    return CVECTOR_OK;

#define CVECTOR_NEW(listname, typename) \
    int listname##_init(listname* list) {\
        CVECTOR_INIT(list, typename)\
        return CVECTOR_OK;\
    }\
    listname* listname##_alloc() {\
        listname* list = malloc(1*sizeof(listname));\
        listname##_init(list);\
        return list;\
    }\
    void listname##_destroy(listname* list) {\
        listname##_free_items(list);\
        free(list->data);\
    }\
    void listname##_free(listname* list) {\
        listname##_destroy(list);\
        free(list);\
    }\
    int listname##_add(listname* list, typename item) {\
        vector_add(list, item)\
        return CVECTOR_OK;\
    }\
    cvector_size_t listname##_length(listname* list) {\
        return CVECTOR_LENGTH(list);\
    }\
    typename listname##_get(listname* list, cvector_size_t i) {\
        return CVECTOR_GET(list, i);\
    }\
    int listname##_remove(listname* list, cvector_size_t index) {\
        CVECTOR_REMOVE(list, index)\
        return CVECTOR_OK;\
    }\
    cvector_size_t listname##_index_of(listname* list, typename target_item) {\
        vector_foreach(list, current_index) {\
            typename current_item = CVECTOR_GET(list, current_index);\
            if(current_item == target_item) {\
                return current_index;\
            }\
        }\
        return -1;\
    }\
    int listname##_insert_at(listname* list, typename item, cvector_size_t dest) {\
        vector_insert_at(list, item, dest);\
        return CVECTOR_OK;\
    }\
    int listname##_move(listname* list, cvector_size_t src, cvector_size_t dest) {\
        typename item = listname##_get(list, src);\
        CVECTOR_SUCCESS_OR_RETURN_ERROR(listname##_remove(list, src));\
        CVECTOR_SUCCESS_OR_RETURN_ERROR(listname##_insert_at(list, item, dest));\
        return CVECTOR_OK;\
    }

#endif //CVECTOR_PUBLIC_HEADER_H
