//
// Created by light on 1/31/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

#define GROWTH_RATE 2

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
        pString->capacity = 7;
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
    if (pString->data != NULL) {
        free(pString->data);
        free(pString);
    } 
    *phMy_string = NULL;
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
        strcpy(pString->data, (char*)c_string);

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


Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
    my_string* pString = (my_string*)hMy_string;    
    char word[100];
    char* temp;
    int i;

    while (fscanf(fp, "%s", word) != EOF) {
        
        if (strlen(word) >= my_string_get_capacity(hMy_string)) {
            temp = malloc(sizeof(char) * pString->capacity * GROWTH_RATE);
            if (temp == NULL) {
                return FAILURE;
            }

            for (i=0; i < pString->size; i++) {
                temp[i] = pString->data[i];
            }
            free(pString->data);
            strcpy(temp, word);
            pString->data = temp;
            pString->capacity *= GROWTH_RATE;
            pString->size = strlen(word);

        }
        strcpy(pString->data, word);
        
        return SUCCESS;

    }


    return FAILURE;
}


Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
    my_string* pString = (my_string*)hMy_string;

    if (pString->data == NULL) {
        return FAILURE;
    }
    fputs(pString->data, fp);
    
    return SUCCESS;
}

