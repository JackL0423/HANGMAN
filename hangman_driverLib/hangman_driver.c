#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "hangman_driver.h"
#include "./my_string.h"

#define MAX_WORD_SIZE 30

GENERIC_VECTOR *dictionary(void) {
    GENERIC_VECTOR* hgVector = (GENERIC_VECTOR*)malloc(sizeof(GENERIC_VECTOR) * MAX_WORD_SIZE);
    MY_STRING hString = NULL;
    FILE* fp;

    int indx;

    fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("Did not open 'dictionary.txt'.\n");
        exit(1);
    }

    for (indx=0; indx<MAX_WORD_SIZE; indx++) {
        hgVector[indx] = generic_vector_init_default(my_string_assignment, my_string_destroy);
        if (hgVector[indx] == NULL) {
            printf("hgVector[%d] is NULL.\n", indx);
            exit(1);
        }
    }

    hString = my_string_init_default();

    while (my_string_extraction(hString, fp)) {
        if (my_string_get_size(hString) < MAX_WORD_SIZE) {
            if (generic_vector_push(hgVector[my_string_get_size(hString)], (ITEM)hString) == FAILURE) {
                printf("Failed to pushback generic vector");
                exit(1);
            }
        }
    }

    my_string_destroy(&hString);
    fclose(fp);

    return hgVector;
}

Boolean continue_game(void) {
    char c;

    printf("Play again? (y/n): ");
    scanf("%c", &c);
    clear_keyboard_buffer();

    c = tolower(c);

    if (!isalpha(c) || (isalpha(c) && c != 'y' && c != 'n')) {
        return continue_game();
    }

    if (c == 'y') return TRUE;
    if (c == 'n') return FALSE;

    return FALSE;
}

int word_length(void) {
    int word_len;

    while (word_len <= 2 || word_len >= MAX_WORD_SIZE) {
        printf("Enter length of word (2-29): ");
        scanf("%d", &word_len);
        clear_keyboard_buffer();
    }

    return word_len;
}

Boolean running_total(void) {
    return FALSE;
}

int number_of_guesses(void) {
    return 0;
}

char get_character(void) {
    return 0;
}

void clear_keyboard_buffer(void) {
    char c;
    int noc;
    noc = scanf("%c", &c);
    while (noc == 1 && c != '\n') {
        noc = scanf("%c", &c);
    }
}

void clear_screen(void) {
    printf("Research how to clear the screen for windows");
}