#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "./headers/hangman_driver.h"
#include "./headers/my_string.h"
#include "./headers/avl_tree.h"
#include "./headers/status.h"

#define MAX_WORD_SIZE (30)

void vector_dictionary(GENERIC_VECTOR dictionary[]) {
    MY_STRING hString = NULL;
    FILE* fp;

    int indx;

    fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("Did not open 'dictionary.txt'.\n");
        exit(1);
    }

    hString = my_string_init_default();
    if (hString == NULL) exit(1);
    
    for (indx=1; indx < MAX_WORD_SIZE; indx++) {
        dictionary[indx] = generic_vector_init_default((ITEM)my_string_init_copy, my_string_destroy);
        if (dictionary[indx] == NULL) {
            printf("hgVector[%d] is NULL.\n", indx);
            exit(1);
        }
    }

    while (my_string_extraction(hString, fp)) {
        generic_vector_push_back(dictionary[my_string_get_size(hString)], hString);
    }

    my_string_destroy(&hString);
    fclose(fp);
}

Boolean continue_game(void) {
    char c;

    printf("Would you like to play again? (y/n): ");
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
    int word_len = 0;

    while (word_len <= 2 || word_len >= MAX_WORD_SIZE) {
        printf("Enter length of word (2-29): ");
        scanf("%d", &word_len);
        clear_keyboard_buffer();
    }

    return word_len;
}

Boolean total_words_remaining(void) {
    char c;

    printf("Would you like the total number of words remaining to be showed (for grading)? (y/n) ");
    scanf("%c", &c);
    clear_keyboard_buffer();

    c = tolower(c);

    if (!isalpha(c) || (isalpha(c) && c != 'y' && c != 'n')) {
        return total_words_remaining();
    }
    
    if (c == 'y') return TRUE;
    if (c == 'n') return FALSE;
    
    return FALSE;
}

int number_of_guesses(void) {
    int guesses;
    
    do {
        printf("Enter number of guesses you would like to have: ");
        scanf("%d", &guesses);
        clear_keyboard_buffer();
    } while (guesses <= 0 || guesses > 26);

    return guesses;
}

char get_character(void) {

    char c;

    printf("\nGuess a character: ");
    scanf("%c", &c);
    clear_keyboard_buffer();

    if (isalpha(c)) {
        c = tolower(c);
    } else {
        return get_character();
    }
    return c;
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
    printf("Research how to clear the screen for windows.\n");
}
