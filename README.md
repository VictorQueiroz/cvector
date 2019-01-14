# cvector

Macro-based header-only vector implementation for C

### Usage

Usage is pretty straightforward. `VECTOR_NEW` macro will create methods based on the first argument (which represents the vector name). The arguments are listed below:
- {listname}_init
- {listname}_destroy
- {listname}_length
- {listname}_add
- {listname}_get
- {listname}_remove
- {listname}_index_of
- {listname}_insert_at

See example of basic usage below:

```c
#include <vector.h>

VECTOR_NEW(strings_list, const char*)

int main() {
    strings_list str_list;
    strings_list_init(&str_list);
    strings_list_add(&str_list, "string 1");
    
    const char* str1 = strings_list_get(&str_list, 0);
    fprintf(stdout, "string added was %s (vector length = %d)\n", strings_list_length(&str_list));
    
    strings_list_destroy(&str_list);
}
```

### Advantages

- CMake
- Supports C90
- Header-only implementation