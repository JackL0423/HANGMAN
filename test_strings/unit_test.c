#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/unit_test.h"
#include "./headers/my_string.h"

int main(int argc, char* argv[]) {

    const char BANNER_STR[81] = "*********************************************************************";
    const int TEST_COUNT = 15;
    int indx;
    char buffer[500];
    int success_count = 0;
    int failure_count = 0;

    Status (*tests[])(char*, int) = {
        test_jlight_string_init_default_return_nonNULL, 
        test_jlight_string_init_default_get_size_returns_0,
        test_jlight_string_init_default_get_capacity_returns_7,
        test_jlight_string_destroy_phMy_string_return_NULL,
        test_jlight_string_destroy_pString_already_NULL,
        test_jlight_string_init_c_string_return_nonNULL,
        test_jlight_string_init_c_string_get_size_return500,
        test_jlight_string_init_c_string_get_capacity_return501,
        test_jlight_string_compare_returns_negative_1,
        test_jlight_string_comapre_returns_0,
        test_jlight_string_comapre_returns_1,
        test_jlight_string_extraction_extracts_string,
        test_jlight_string_insertion_writes_file,
        test_jlight_string_push_back_returns_string,
        test_jlight_string_my_string_at_returns_e,
        test_jlight_string_c_str_returns_string
        };

    int number_of_functions = sizeof(tests)/sizeof(tests[0]);

    printf("%s\n", BANNER_STR);
    printf("\t\tAcceptance tests for String object\n");
    printf("%s\n", BANNER_STR);
    for (indx=0; indx < number_of_functions; indx++) {
        if (tests[indx](buffer, 500) == FAILURE) {
            printf("%s\n", buffer);
            printf("      - Failed: Test %d \n", indx+1);
            failure_count++;
        } else {
            printf("%s\n", buffer);
            printf("      - Passed: Test %d \n", indx+1);
            success_count++;
        }
        printf("\n");
    }

    float pass_rate = 100 * success_count / TEST_COUNT;

    printf("%s\n", BANNER_STR);
    printf("\t\t\tAcceptance Test Results\n");
    printf("%s\n", BANNER_STR);

    printf("Test Statistics:\n");
    printf("    - %d Tests: %d passed (%d failed)\n", TEST_COUNT, success_count, failure_count);
    printf("    - Pass Rate: %6.2f%%\n\n", pass_rate);

    return 0;
}

