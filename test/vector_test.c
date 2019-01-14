#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

CVECTOR_NEW(strings_list, char*)

void strings_list_free_items(strings_list* list) {
    CVECTOR_FOR(list, i) {
        free(CVECTOR_GET(list, i));
    }
}

void compare_strings(char* str1, char* str2) {
    assert(strlen(str1) == strlen(str2));
    assert(strncmp(str1, str2, strlen(str1)) == 0);
}

uint32_t strings_list_length(strings_list* list) {
    return CVECTOR_LENGTH(list);
}

void test_remove_item() {
    strings_list strings_list_1;
    assert(strings_list_init(&strings_list_1) == CVECTOR_OK);
    assert(strings_list_add(&strings_list_1, "test 1") == CVECTOR_OK);
    assert(strings_list_add(&strings_list_1, "test 2") == CVECTOR_OK);
    assert(strings_list_add(&strings_list_1, "test 3") == CVECTOR_OK);

    assert(strings_list_remove(&strings_list_1, 1) == CVECTOR_OK);

    compare_strings(strings_list_get(&strings_list_1, 0), "test 1");
    compare_strings(strings_list_get(&strings_list_1, 1), "test 3");
    assert(strings_list_length(&strings_list_1) == 2);
    strings_list_destroy(&strings_list_1);
}

void test_find_item_index() {
    strings_list strings_list1;
    strings_list_init(&strings_list1);

    int i;
    for(i = 0; i < 100; i++) {
        char* string = malloc(64*sizeof(char));
        sprintf(string, "test %d", i);
        strings_list_add(&strings_list1, string);
    }

    char* item = strings_list_get(&strings_list1, 4);
    assert(strings_list_index_of(&strings_list1, item) == 4);
    strings_list_free_items(&strings_list1);
    strings_list_destroy(&strings_list1);
}

void test_move_item() {
    strings_list list;
    strings_list_init(&list);

    strings_list_add(&list, "test 1");
    strings_list_add(&list, "test 2");
    strings_list_add(&list, "test 3");

    assert(strings_list_move(&list, 2, 0) == CVECTOR_OK);

    compare_strings(strings_list_get(&list, 0), "test 3");
    compare_strings(strings_list_get(&list, 1), "test 1");
    compare_strings(strings_list_get(&list, 2), "test 2");

    assert(strings_list_move(&list, 0, 2) == CVECTOR_OK);

    compare_strings(strings_list_get(&list, 0), "test 1");
    compare_strings(strings_list_get(&list, 1), "test 2");
    compare_strings(strings_list_get(&list, 2), "test 3");

    strings_list_destroy(&list);
}

int main() {
    test_move_item();
    test_find_item_index();
    test_remove_item();
    return 0;
}
