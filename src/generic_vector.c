#include <stdio.h>
#include <stdlib.h>

#include "headers/generic_vector.h"


struct generic_vector {
    int size;
    int capacity;
    ITEM* data;
    ITEM (*fp_init_copy)(ITEM);
    void (*fp_destroy)(ITEM*);
};
typedef struct generic_vector Generic_vector;


GENERIC_VECTOR generic_vector_init_default(ITEM (*fp_init_copy)(ITEM), void (*fp_destroy)(ITEM*)) {
    Generic_vector* pVector = (Generic_vector*)malloc(sizeof(Generic_vector));
    int indx;
    if (pVector != NULL) {
        pVector->size = 0;
        pVector->capacity = 1;
        pVector->fp_init_copy = fp_init_copy;
        pVector->fp_destroy = fp_destroy;
        pVector->data = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);
        if (pVector->data == NULL) {
            free(pVector);
            return NULL;
        }
        for (indx=0; indx<pVector->capacity; indx++) {
            pVector->data[indx] = NULL;
        }
    }
    return pVector;
}

void generic_vector_destroy(GENERIC_VECTOR* phVector) {
    Generic_vector* pVector = (Generic_vector*)*phVector;
    int indx;
    for (indx=0; indx<pVector->size; indx++) {
        pVector->fp_destroy(&pVector->data[indx]);
    }
    free(pVector->data);
    free(pVector);
    *phVector = NULL;
}

Boolean generic_vector_is_empty(GENERIC_VECTOR hVector) {
    Generic_vector* pVector = (Generic_vector*)hVector;
    return (pVector->size <= 0) ? TRUE : FALSE;
}

int generic_vector_get_size(GENERIC_VECTOR hVector) {
    Generic_vector* pVector = (Generic_vector*)hVector;
    return pVector->size;
}

int generic_vector_get_capacity(GENERIC_VECTOR hVector) {
    Generic_vector* pVector = (Generic_vector*)hVector;
    return pVector->capacity;
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM hItem) {
    Generic_vector* pVector = (Generic_vector*)hVector;
    ITEM* temp;
    int indx;

    if (generic_vector_get_size(hVector) >= generic_vector_get_capacity(hVector)) {
        temp = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity * 2);
        if (temp == NULL) {
            return FAILURE;
        }
        
        for (indx=0; indx < pVector->size; indx++) {
            temp[indx] = pVector->data[indx];
        }
        for (; indx < pVector->capacity * 2; indx++) {
            temp[indx] = NULL;
        }
        
        free(pVector->data);
        pVector->data = temp;
        pVector->capacity *= 2;
    }

    pVector->data[pVector->size] = pVector->fp_init_copy(hItem);    //  Deep copy
    if (pVector->data[pVector->size] == NULL) {
        return FAILURE;
    }
    pVector->size++;
    return SUCCESS;
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector) {
    Generic_vector* pVector = (Generic_vector*)hVector;
    if (generic_vector_is_empty(hVector) == TRUE) {
        return FAILURE;
    }
    pVector->fp_destroy(pVector->data + pVector->size -1);
    return SUCCESS;
}

ITEM* generic_vector_at(GENERIC_VECTOR hVector, int indx) {
    Generic_vector* pVector = (Generic_vector*)hVector;

    if (indx < 0 || indx >= pVector->size) {
        return NULL;
    }

    return pVector->data[indx];
}
