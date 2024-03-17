#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "my_string.h"
#include "status.h"

//  Unit Tests
Status test_jlight_string_init_default_return_nonNULL(char* buffer, int size);

Status test_jlight_string_init_default_get_size_returns_0(char* buffer, int size);

Status test_jlight_string_init_default_get_capacity_returns_7(char* buffer, int size);

Status test_jlight_string_destroy_phMy_string_return_NULL(char* buffer, int size);

Status test_jlight_string_destroy_pString_already_NULL(char* buffer, int size);

Status test_jlight_string_init_c_string_return_nonNULL(char* buffer, int size);

Status test_jlight_string_init_c_string_get_size_return500(char* buffer, int size);

Status test_jlight_string_init_c_string_get_capacity_return501(char* buffer, int size);

Status test_jlight_string_init_c_string_data_is_destroyed(char* buffer, int size);

Status test_jlight_string_compare_returns_negative_1(char* buffer, int size);

Status test_jlight_string_comapre_returns_0(char* buffer, int size);

Status test_jlight_string_comapre_returns_1(char* buffer, int size);

Status test_jlight_string_extraction_extracts_string(char* buffer, int size);

Status test_jlight_string_insertion_writes_file(char* buffer, int size);

Status test_jlight_string_push_back_returns_string(char* buffer, int size);

Status test_jlight_string_my_string_at_returns_e(char* buffer, int size);

Status test_jlight_string_c_str_returns_string(char* buffer, int size);

Status test_jlight_string_my_string_assignment_returns_copy(char* buffer, int size);

Status test_jlight_string_my_string_init_copy_returns_copy(char* buffer, int size);

Status test_jlight_string_my_string_swapy_returns_copy(char* buffer, int size);
#endif//UNIT_TEST_H