//
// Created by light on 1/31/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"


struct My_string {
    int size;
    int capacity;
    char* data;
};
typedef struct My_string my_string;


MY_STRING my_string_init_default(void) {
    my_string* pString = (my_string*)malloc(sizeof(my_string));

    if (pString != NULL) {
        pString->size = 0;
        pString->capacity = 1;
        pString->data = (char*)malloc(sizeof(int) * pString->capacity);

        if (pString->data == NULL) {
            free(pString);
            return NULL;
        }
    }
    return (MY_STRING)pString;
}


void my_string_destroy(MY_STRING* phMy_string) {
    my_string* pString = (my_string*)*phMy_string;
    if (pString != NULL) {
        //free(pString->data);
        free(pString);
        *phMy_string = NULL;
    } else {
        printf("WRONG PLACE TO GO\n");
        *phMy_string = NULL;
    }
}

MY_STRING my_string_init_c_string(const char* c_string) {
    my_string* pString = (my_string*)malloc(sizeof(my_string));

    if (pString != NULL) {
        pString->size = strlen(c_string);
        pString->capacity = strlen(c_string) + 1;
        pString->data = (char*)malloc(sizeof(char) * pString->capacity);

        if (pString->data == NULL) {
            free(pString);
            return NULL;
        }
        pString->data = (char*)c_string;

    }
    return (MY_STRING)pString;
}


int my_string_get_capacity(MY_STRING hMy_string) {
    my_string* pString = (my_string*)hMy_string;
    return pString->capacity;
}


int my_string_get_size(MY_STRING hMy_string) {
    my_string* pString = (my_string*)hMy_string;
    return pString->size;
}


int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
    my_string* pLeft_string = (my_string*)hLeft_string;
    my_string* pRight_string = (my_string*)hRight_string;

    if (strcmp(pLeft_string->data, pRight_string->data) < 0) {
        return -1;
    }
    else if (strcmp(pLeft_string->data, pRight_string->data) > 0) {
        return 0;
    }
    else {
        return 1;
    }
}

// of left is smaller than right return <0
// if left is greater than right return 0
// if equal return >0