//
// Created by light on 1/31/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/my_string.h"

#define GROWTH_RATE (2)

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
        pString->data = (char*)malloc(sizeof(char) * pString->capacity);

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
    int flag;

    if (strcmp(pLeft_string->data, pRight_string->data) < 0) {
        flag =  -1;
    }
    else if (strcmp(pLeft_string->data, pRight_string->data) > 0) {
        flag =  1;
    }
    else {
        flag = 0;
    }

    return flag;
}


Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
    my_string* pString = (my_string*)hMy_string;    
    char word[100];
    char* temp;
    int i;

    while (fscanf(fp, "%s", word) != EOF) {
        
        if ((int)strlen(word) >= my_string_get_capacity(hMy_string)) {
            temp = (char*)malloc(sizeof(char) * pString->capacity * GROWTH_RATE);
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
    char* temp = my_string_c_str(hMy_string);

    if (pString->data == NULL) {
        return FAILURE;
    }
    else {
        fprintf(fp, "%s", temp);
    }
    
    return SUCCESS;
}


Status my_string_push_back(MY_STRING hMy_string, char item) {
    my_string* pString = (my_string*)hMy_string;
    char* temp;
    int i;
    if (hMy_string == NULL) {
        return FAILURE;
    }

    if (my_string_get_size(hMy_string)+1 >= my_string_get_capacity(hMy_string)) {     //  Check if string needs resize.
        temp = (char*)malloc(sizeof(char) * pString->capacity * GROWTH_RATE);
        if (temp == NULL) {
            return FAILURE;
        }

        for (i=0; i < my_string_get_size(hMy_string); i++) {
            temp[i] = pString->data[i];
        }

        free(pString->data);
        pString->data = temp;
        pString->capacity *= GROWTH_RATE;
    }
    pString->data[pString->size++] = item;

    return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string) {
    my_string* pString = (my_string*)hMy_string;
    
    if (pString->size > 0) {
        pString->size--;
        return SUCCESS;
    }
    
    return FAILURE;
    
}


char* my_string_at(MY_STRING hMy_string, int index) {
    my_string* pString = (my_string*)hMy_string;
    if (my_string_empty(hMy_string)) {
        return NULL;
    }
    if (index > my_string_get_size(hMy_string)) {
        return NULL;
    }

    return &pString->data[index];
}


char* my_string_c_str(MY_STRING hMy_string) {
    if (my_string_empty(hMy_string)) {
        return NULL;
    }

    return my_string_at(hMy_string, 0);
}


Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
    my_string* pResult = (my_string*)hResult;
    my_string* pAppend = (my_string*)hAppend;
    char* temp;
    int indx;

    if (my_string_empty(hResult) || my_string_empty(hAppend)) {
        return FAILURE;
    }

    if ((my_string_get_size(hResult)+my_string_get_size(hAppend)) >= my_string_get_capacity(hResult)) {
        temp = (char*)malloc(sizeof(char) * pResult->capacity * GROWTH_RATE);
        if (temp == NULL) {
            return FAILURE;
        }

        for (indx = 0; indx < pResult->size; indx++) {
            temp[indx] = pResult->data[indx];
        }
        free(pResult->data);

        pResult->data = temp;
    }

    strcat(pResult->data, pAppend->data);

    return SUCCESS;
}


Boolean my_string_empty(MY_STRING hMy_string) {
    my_string* pString = (my_string*)hMy_string;
    return (pString->size <= 0) ? TRUE : FALSE;
}


Status my_string_assignment(MY_STRING hLeft, MY_STRING hRight) {
    my_string* pStringLeft = (my_string*)hLeft;
    my_string* pStringRight = (my_string*)hRight;
    char* temp;
    int indx;
    //  Make hleft a deep copy of hRight
    if (my_string_get_size(hRight) >= my_string_get_capacity(hLeft)) {
        //  resize left
        temp = (char*)malloc(sizeof(char) * pStringRight->capacity);
        if (temp == NULL) {
            return FAILURE;
        }
        for (indx=0; indx<pStringRight->size; indx++) {
            temp[indx]= pStringRight->data[indx];
        }
        free(pStringLeft->data);
        pStringLeft->data = temp;
        pStringLeft->capacity = pStringRight->capacity;
    }

    for (indx=0; indx<pStringLeft->size; indx++) {
        pStringLeft->data[indx] = pStringRight->data[indx];
    }
    pStringLeft->size = pStringRight->size;

    return SUCCESS;
}


MY_STRING my_string_init_copy(MY_STRING hMy_string) {
    my_string* pString = (my_string*)hMy_string;
    my_string* temp = (my_string*)malloc(sizeof(my_string));
    int indx;
    if (temp != NULL) {
        temp->size = pString->size;
        temp->capacity = pString->capacity;
        temp->data = (char*)malloc(sizeof(char) * temp->capacity);
        for (indx=0; indx<temp->size; indx++) {
            temp->data[indx] = pString->data[indx];
        }
    }

    return (MY_STRING)temp;
}


void my_string_swap(MY_STRING hLeft, MY_STRING hRight) {
    MY_STRING pTemp = my_string_init_default();
    //pTemp = hLeft;
    my_string_assignment(pTemp, hLeft);
    //hLeft = hRight;
    my_string_assignment(hLeft, hRight);
    //hRight = pTemp;
    my_string_assignment(hRight, pTemp);

    free(pTemp);
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess) {
    int indx;
    while (my_string_empty(new_key) == FALSE) {
        my_string_pop_back(new_key);
    }

    for (indx=0; indx<my_string_get_size(word); indx++) {
        if (!my_string_push_back(new_key, *my_string_at(word, indx) == guess ? guess : *my_string_at(current_word_family, indx))) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

Boolean used_character(MY_STRING guess_list, char c) {
    my_string* pString = (my_string*)guess_list;
    int indx;
    
    for (indx=0; indx < my_string_get_size(guess_list); indx++) {
        if (pString->data[indx] == c) {
            printf("Letter already guessed.. Try again\n");
            return TRUE;
        }
    }
    return FALSE;
}