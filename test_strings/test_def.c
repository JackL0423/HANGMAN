#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/unit_test.h"
#include "./headers/my_string.h"


Status test_jlight_string_init_default_return_nonNULL(char* buffer, int size) {
    MY_STRING hString;

    hString = my_string_init_default();
    printf("    + Testing init_default:\n");
    printf("      - Checking function returns non NULL: ");
    if (hString == NULL) {
        strncpy(buffer, "FAILED", size);
        return FAILURE;
    }
    else {
        my_string_destroy(&hString);
        strncpy(buffer, "PASSED", size);
        return SUCCESS;
    }
}

Status test_jlight_string_init_default_get_size_returns_0(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_default();

    printf("    + Testing init_default:\n");
    printf("      - Checking function size returns 0: ");
    if (my_string_get_size(hString) != 0) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    my_string_destroy(&hString);
    return status;
}

Status test_jlight_string_init_default_get_capacity_returns_7(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_default();

    printf("    + Testing init_default:\n");
    printf("      - Checking function capacity return 7: ");
    if (my_string_get_capacity(hString) != 7) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    my_string_destroy(&hString);
    return status;
}

Status test_jlight_string_destroy_phMy_string_return_NULL(char* buffer, int size) {
    MY_STRING hString = NULL;

    hString = my_string_init_default();

    my_string_destroy(&hString);

    printf("    + Testing destroy:\n");
    printf("      - Checking Handle set to NULL: ");
    if (hString != NULL) {
        strncpy(buffer, "FAILED", size);
        return FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        return SUCCESS;
    }
}

Status test_jlight_string_destroy_pString_already_NULL(char* buffer, int size) {
    MY_STRING hString = NULL;

    my_string_destroy(&hString);

    printf("    + Testing destroy:\n");
    printf("      - Checking if segmentation fault: ");
    if (hString != NULL) {
        strncpy(buffer, "FAILED", size);
        return FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        return SUCCESS;
    }

}

Status test_jlight_string_init_c_string_return_nonNULL(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("test string for the test");

    printf("    + Testing init_c_string:\n");
    printf("      - Passing in string: 'test string for the test'\n");
    printf("      - Checking does not return NULL: ");
    if (hString == NULL) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    my_string_destroy(&hString);
    return status;
}

Status test_jlight_string_init_c_string_get_size_return500(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("test string for the test");

    printf("    + Testing init_c_string:\n");
    printf("      - Passing in the string: 'test string for the test'\n");
    printf("      - Checking retuns size 24: ");
    if (my_string_get_size(hString) != 24) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    my_string_destroy(&hString);
    return status;
}

Status test_jlight_string_init_c_string_get_capacity_return501(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("test string for the test");

    printf("    + Testing init_c_string:\n");
    printf("      - Passing in the string: 'test string for the test'\n");
    printf("      - Checking returns capacity 25: ");
    if (my_string_get_capacity(hString) != 25) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    my_string_destroy(&hString);
    return status;
}

Status test_jlight_string_compare_returns_negative_1(char* buffer, int size) {
    MY_STRING hLeft = NULL;
    MY_STRING hRight = NULL;
    Status status;

    hLeft = my_string_init_c_string("the");
    hRight = my_string_init_c_string("there");

    printf("    + Testing string_compare:\n");
    printf("      - Passing in string 'the' and 'there' returns 1: ");
    if (my_string_compare(hLeft, hRight) != -1) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    my_string_destroy(&hLeft);
    my_string_destroy(&hRight);

    return status;

}

Status test_jlight_string_comapre_returns_0(char* buffer, int size) {
    MY_STRING hLeft = NULL;
    MY_STRING hRight = NULL;
    Status status;

    hLeft = my_string_init_c_string("there");
    hRight = my_string_init_c_string("there");

    printf("    + Testing string_compare:\n");
    printf("      - Passing in strings 'there' and 'there' returns 0: ");
    if (my_string_compare(hLeft, hRight) != 0) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    my_string_destroy(&hLeft);
    my_string_destroy(&hRight);

    return status;
}

Status test_jlight_string_comapre_returns_1(char* buffer, int size) {
    MY_STRING hLeft = NULL;
    MY_STRING hRight = NULL;
    Status status;

    hLeft = my_string_init_c_string("there");
    hRight = my_string_init_c_string("the");

    printf("    + Testing string_compare:\n");
    printf("      - Passing in strings 'there' and 'the' returns 1: ");
    if (my_string_compare(hLeft, hRight) != 1) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    my_string_destroy(&hLeft);
    my_string_destroy(&hRight);

    return status;

}

Status test_jlight_string_extraction_extracts_string(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;
    FILE* fp;

    hString = my_string_init_default();
    fp = fopen("test_strings/test_input.txt", "r");

    printf("    + Testing string_extraction:\n");
    printf("      - Expecting for file to be read and extract str: ");
    if(fp == NULL || my_string_extraction(hString, fp) == FAILURE) {
        strncpy(buffer, "FAILED", size);
        if (fp == NULL) {
            printf("        ^ Problem opening the file.\n");
        }
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    fclose(fp);
    my_string_destroy(&hString);
    return status;
}

Status test_jlight_string_insertion_writes_file(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;
    FILE* fp;

    hString = my_string_init_c_string("This is for the test output.");
    fp = fopen("test_output.txt", "w");

    printf("    + Testing string_insertion:\n");
    printf("      - Expecting file to be writen and insert str: ");
    if (fp == NULL || my_string_insertion(hString, fp) == FAILURE) {
        strncpy(buffer, "FAILED", size);
        if (fp == NULL) {
            printf("        ^ Problem writing the file.\n");
        }
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }

    fclose(fp);
    my_string_destroy(&hString);

    return status;
}

Status test_jlight_string_push_back_returns_string(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("Ther");
    
    printf("    + Testing push_back:\n");
    printf("      - String was 'Ther' and added 'e': ");
    if (my_string_push_back(hString, 'e') == FAILURE) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }
    my_string_destroy(&hString);

    return status;
}

Status test_jlight_string_my_string_at_returns_e(char* buffer, int size) {
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("There");

    printf("    + Testing my_string_at:\n");
    printf("      - String passed in was 'There' and checking at index 2 returns 'e': ");
    if (*my_string_at(hString, 2) != 'e') {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }
    my_string_destroy(&hString);

    return status;
}

Status test_jlight_string_c_str_returns_string(char* buffer, int size) {
    MY_STRING hString = NULL;
    MY_STRING hTestResult = NULL;
    Status status;

    hString = my_string_init_c_string("Special String");

    hTestResult = my_string_init_c_string(my_string_c_str(hString));
    //printf("\n hTestResult: %s", my_string_c_str(hTestResult));

    printf("    + Testing my_string_c_str:\n");
    printf("      - String passed was 'Special String' and expect it to be returned: ");
    if (my_string_compare(hString, hTestResult) != 0) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    } else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }
    my_string_destroy(&hString);
    //my_string_destroy(&hTestResult);
    
    return status;
}

Status test_jlight_string_my_string_assignment_returns_copy(char* buffer, int size) {
    MY_STRING hLeft = NULL;
    MY_STRING hRight = NULL;
    Status status;

    hLeft = my_string_init_c_string("I am the left");
    hRight = my_string_init_c_string("I am the one to copy");
    

    printf("    + Testing my_string_assignment:\n");
    printf("      - Expecting copy of 'I am the original' to be made: ");
    if (my_string_assignment(hLeft, hRight) == FAILURE) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    } 
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }
    my_string_destroy(&hRight);
    my_string_destroy(&hLeft);

    return status;
}

Status test_jlight_string_my_string_init_copy_returns_copy(char* buffer, int size) {
    MY_STRING hOriginal = NULL;
    MY_STRING hCopy = NULL;
    Status status;

    hOriginal = my_string_init_c_string("I am the original");

    printf("    + Testing my_string_init_copy:\n");
    printf("      - Expecting copy of 'I am the original' to be made: ");
    hCopy = my_string_init_copy(hOriginal);
    if (my_string_compare(hOriginal, hCopy) != 0) {
        strncpy(buffer, "FAILURE", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }
    my_string_destroy(&hOriginal);
    my_string_destroy(&hCopy);

    return status;
}


Status test_jlight_string_my_string_swapy_returns_copy(char* buffer, int size) {
    MY_STRING hLeft = NULL;
    MY_STRING hRight = NULL;
    MY_STRING hTestRight = NULL;
    MY_STRING hTestLeft = NULL;
    Status status;

    hLeft = my_string_init_c_string("This will be the right string");
    hRight = my_string_init_c_string("This will be the left string");

    hTestRight = my_string_init_c_string("This will be the right string");
    hTestLeft = my_string_init_c_string("This will be the left string");

    printf("    + Testing my_string_swap:\n");
    printf("      - Expecting for the strings to swap: ");
    my_string_swap(hLeft, hRight);
    if (my_string_compare(hLeft, hTestLeft) != 0 || my_string_compare(hRight, hTestRight) != 0) {
        strncpy(buffer, "FAILED", size);
        status = FAILURE;
    }
    else {
        strncpy(buffer, "PASSED", size);
        status = SUCCESS;
    }
    my_string_destroy(&hLeft); my_string_destroy(&hRight);
    my_string_destroy(&hTestLeft); my_string_destroy(&hTestRight);

    return status;
}