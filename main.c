#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main() {
    MY_STRING hMy_string = NULL;
    FILE* fp;

    hMy_string = my_string_init_default();
    fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
    }

    while(my_string_extraction(hMy_string, fp)) {
        my_string_insertion(hMy_string, stdout);
        printf("\n");
    }

    my_string_destroy(&hMy_string);
    fclose(fp);
    return 0;
}