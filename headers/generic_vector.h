#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H

#include "status.h"
#include "generic.h"

typedef void* GENERIC_VECTOR;

GENERIC_VECTOR generic_vector_init_default(
    ITEM (*fp_init_copy)(ITEM hString), 
    void (*fp_destroy)(ITEM* phString));

void generic_vector_destroy(GENERIC_VECTOR* phVector);

Status generic_vector_push(GENERIC_VECTOR hVector, ITEM hMY_STRING);

Status generic_vector_pop_back(GENERIC_VECTOR hVector, ITEM hMY_STRING);

Status generic_vector_at(GENERIC_VECTOR hVector, int indx);

Boolean generic_vector_is_empty(GENERIC_VECTOR hVector);

int generic_vector_get_size(GENERIC_VECTOR hVector);

int generic_vector_get_capacity(GENERIC_VECTOR hVector);

#endif//GENERIC_VECTOR_H