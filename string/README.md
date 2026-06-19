### Length prefixed string

Length prefixed C strings, length is at the start of the allocated memory

    e.g.,
    -----------------------------------------------
    | 0 | 0 | 0 | 4 | 'T' | 'E' | 'S' | 'T' | '\0'|
    -----------------------------------------------
                    ^
                  return
    User can keep pointer to first character, so it's like C style strings with
    additional functionality.

### Pros
- User gets a null terminated `char*`, so it still works with c style string  
  functions, e.g., printf, strcmp.
- This implementation is mostly about avoiding strlen() cost.  
  Provides a few more functions to make easier create/append/trim/substring  
  operations.

### Cons
- 4 bytes fixed overhead per string and max string size is ~4gb.
- When you create/set/append a string, new memory is allocated. If you are  
  modifying strings a lot, consider using buffer-like implementation for that if  
  performance is critical for your use-case. I modify strings rarely but read  
  a lot (copy/move etc.).
  
```c
#include "sc_str.h"

#include <stdio.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
    char* s1;
    int64_t idx;

    s1 = sc_str_create("*-hello-*");
    printf("%s \n", s1); // prints *-hello-*

    sc_str_trim(&s1, "*-");
    printf("%s \n", s1); // prints hello

    sc_str_append_fmt(&s1, "%d", 2);
    printf("%s \n", s1); // prints hello2

    sc_str_replace(&s1, "2", " world!");
    printf("%s \n", s1); // prints hello world!

    sc_str_substring(&s1, 0, 5);
    printf("%s \n", s1); // prints hello

    /* index_of / last_index_of examples */
    sc_str_set(&s1, "hello hello world");

    idx = sc_str_index_of(s1, "hello", 0);
    printf("index_of(\"hello\", 0) = %" PRId64 "\n", idx); // 0

    idx = sc_str_index_of(s1, "hello", 1);
    printf("index_of(\"hello\", 1) = %" PRId64 "\n", idx); // 6

    idx = sc_str_index_of(s1, "bye", 0);
    printf("index_of(\"bye\", 0)   = %" PRId64 "\n", idx); // -1

    idx = sc_str_last_index_of(s1, "hello", 16);
    printf("last_index_of(\"hello\", 16) = %" PRId64 "\n", idx); // 6

    idx = sc_str_last_index_of(s1, "hello", 5);
    printf("last_index_of(\"hello\", 5)  = %" PRId64 "\n", idx); // 0

    sc_str_destroy(&s1);

    return 0;
}

```