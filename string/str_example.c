#include "sc_str.h"

#include <stdio.h>
#include <inttypes.h>

int main(void)
{
	char *s1;
	int64_t idx;

	s1 = sc_str_create("*-hello-*");
	printf("%s \n", s1); // prints **hello**

	sc_str_trim(&s1, "*-");
	printf("%s \n", s1); // prints hello

	sc_str_append_fmt(&s1, "%d", 2);
	printf("%s \n", s1); // prints hello2

	sc_str_replace(&s1, "2", " world!");
	printf("%s \n", s1); // prints hello world!

	sc_str_substring(&s1, 0, 5);
	printf("%s \n", s1); // prints hello

	sc_str_set(&s1, "banana");
	idx = sc_str_index_of(s1, "an", 0);
	printf("index_of(\"an\", 0)      = %" PRId64 "\n", idx); // 1
	idx = sc_str_index_of(s1, "an", 2);
	printf("index_of(\"an\", 2)      = %" PRId64 "\n", idx); // 3
	idx = sc_str_index_of(s1, "an", 4);
	printf("index_of(\"an\", 4)      = %" PRId64 "\n", idx); // -1
	idx = sc_str_index_of(s1, "", 3);
	printf("index_of(\"\", 3)        = %" PRId64 "\n", idx); // 3
	idx = sc_str_index_of(s1, "", 10);
	printf("index_of(\"\", 10)       = %" PRId64 "\n", idx); // -1

	idx = sc_str_last_index_of(s1, "an", 5);
	printf("last_index_of(\"an\", 5) = %" PRId64 "\n", idx); // 3
	idx = sc_str_last_index_of(s1, "an", 2);
	printf("last_index_of(\"an\", 2) = %" PRId64 "\n", idx); // 1
	idx = sc_str_last_index_of(s1, "an", 0);
	printf("last_index_of(\"an\", 0) = %" PRId64 "\n", idx); // -1
	idx = sc_str_last_index_of(s1, "", 4);
	printf("last_index_of(\"\", 4)   = %" PRId64 "\n", idx); // 4

	sc_str_destroy(&s1);

	return 0;
}
