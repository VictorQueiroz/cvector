#ifndef CVECTOR_LIBRARY_H
#define CVECTOR_LIBRARY_H

#include <stdint.h>
#include <stdlib.h>

#define CVECTOR_OK 0
#define CVECTOR_MEMORY_ALLOCATION_FAILED -1
#define CVECTOR_INVALID_LIST_OFFSET -2

#define CVECTOR_SUCCESS_OR_RETURN_ERROR(error) \
    if(error != CVECTOR_OK) {\
        return error;\
    }

#define CVECTOR_STRUCT_PARAMS(type) \
    uint32_t capacity;\
    uint32_t offset;\
    uint32_t item_length;\
    type* data;

#define CVECTOR_INIT(ptr, type) \
    ptr->item_length = sizeof(type);\
    ptr->offset = 0;\
    ptr->capacity = 32;\
    ptr->data = (type*) malloc(ptr->item_length*ptr->capacity);\
    if(ptr->data == NULL) {\
        return CVECTOR_MEMORY_ALLOCATION_FAILED;\
    }

#define CVECTOR_INSERT_AT(list, item, index) \
    if((list->capacity - list->offset) <= 1) {\
        list->capacity += 32;\
        list->data = realloc(list->data, list->item_length*list->capacity);\
        if(list->data == NULL) {\
            return CVECTOR_MEMORY_ALLOCATION_FAILED;\
        }\
    }\
    {\
        uint32_t i;\
        for(i = index; i < list->offset; i++) {\
            list->data[list->offset - i] = list->data[(list->offset - 1) - i];\
        }\
    }\
    list->data[index] = item;\
    list->offset++;\
    return CVECTOR_OK;

#define CVECTOR_ADD(list, item) CVECTOR_INSERT_AT(list, item, list->offset)

#define CVECTOR_GET(list, index) list->data[index]

#define CVECTOR_LENGTH(list) list->offset

#define CVECTOR_REMOVE(list, index) \
    if(index > (list->offset - 1)) return CVECTOR_INVALID_LIST_OFFSET;\
    uint32_t i;\
    for(i = index; i < list->offset - 1; i++) {\
        list->data[i] = list->data[i + 1];\
    }\
    list->offset--;\
    return CVECTOR_OK;

#define CVECTOR_NEW(listname, typename) \
    typedef struct {\
        CVECTOR_STRUCT_PARAMS(typename)\
    } listname;\
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
        free(list->data);\
    }\
    void listname##_free(listname* list) {\
        listname##_destroy(list);\
        free(list);\
    }\
    int listname##_add(listname* list, typename item) {\
        CVECTOR_ADD(list, item)\
        return CVECTOR_OK;\
    }\
    uint32_t listname##_length(listname* list) {\
        return CVECTOR_LENGTH(list);\
    }\
    typename listname##_get(listname* list, uint32_t i) {\
        return CVECTOR_GET(list, i);\
    }\
    int listname##_remove(listname* list, uint32_t index) {\
        CVECTOR_REMOVE(list, index)\
        return CVECTOR_OK;\
    }\
    uint32_t listname##_index_of(listname* list, typename target_item) {\
        CVECTOR_FOR(list, current_index) {\
            typename current_item = CVECTOR_GET(list, current_index);\
            if(current_item == target_item) {\
                return current_index;\
            }\
        }\
        return -1;\
    }\
    void listname##_free_items(listname* list);\
    int listname##_insert_at(listname* list, typename item, uint32_t dest) {\
        CVECTOR_INSERT_AT(list, item, dest);\
        return CVECTOR_OK;\
    }\
    int listname##_move(listname* list, uint32_t src, uint32_t dest) {\
        typename item = listname##_get(list, src);\
        CVECTOR_SUCCESS_OR_RETURN_ERROR(listname##_remove(list, src));\
        CVECTOR_SUCCESS_OR_RETURN_ERROR(listname##_insert_at(list, item, dest));\
        return CVECTOR_OK;\
    }

#define CVECTOR_FOR(list, index) \
    uint32_t index;\
    for(index = 0; index < list->offset; index++)

#endif
