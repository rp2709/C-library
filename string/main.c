#include <stdio.h>

#include "String.h"

int main() {

    string_t str;
    string_init(&str, "Hello");

    string_t str2;
    string_init(&str2, " World!");

    string_concat(&str, &str2);

    string_append(&str,'Q');

    printf("%s\n", string_get_c_string(&str));

    return 0;
}