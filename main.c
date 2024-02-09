#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main() {
    MY_STRING hMy_string1 = NULL;
    MY_STRING hMy_string2 = NULL;

    hMy_string1 = my_string_init_c_string("there");
    hMy_string2 = my_string_init_c_string("there");

    printf("size: %d\n", my_string_get_size(hMy_string1));
    printf("capacity: %d\n", my_string_get_capacity(hMy_string1));

    printf("Result: %d\n", my_string_compare(hMy_string1, hMy_string2));

    my_string_destroy(&hMy_string1);
    my_string_destroy(&hMy_string2);
    return 0;
}