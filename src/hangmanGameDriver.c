#include <stdio.h>
#include <stdlib.h>

#include "./headers/hangmanGameDriver.h"
#include "./headers/my_string.h"
#include "./headers/generic_vector.h"
#include "./headers/avl_tree.h"
#include "./headers/hangman_driver.h"

void hangman_driver(void) {
    GENERIC_VECTOR *dict = vector_dictionary();
    if (generic_vector_is_empty(dict)) {
        printf("Failed to allocate space for vector dictionary.\n");
        exit(1);
    }
    GENERIC_VECTOR largest_family = NULL;
    TREE hTree = avl_tree_init_default();
    if (hTree == NULL) {
        printf("Failed to allocate space for tree.\n");
        exit(1);
    }
    MY_STRING word_key = my_string_init_default();
    if (word_key == NULL) {
        printf("Failed to allocate space for word_key.\n");
        exit(1);
    }
    MY_STRING guess_list = my_string_init_c_string(" ");
    if (guess_list == NULL) {
        printf("Failed to allocate space for guess_list.\n");
        exit(1);
    }
    MY_STRING word_family = my_string_init_default();
    if (word_family == NULL) {
        printf("Failed to allocate space word_family.\n");
        exit(1);
    }
    int word_len, number_guesses, running_total, indx;
    char current_guess;

    //clear_screen?
    word_len = word_length();
    number_guesses = number_of_guesses();
    running_total = total_words_remaining();

    for (indx=0; indx<word_len; indx++) {
        my_string_push_back(word_key, '-');
    }

    //clear_screen?

    do {
        printf("You have %d remaining guesses left\nLetters used: ", number_guesses);
        my_string_insertion(guess_list, stdout);

        printf("\nCurrent word: ");
        my_string_insertion(word_key, stdout);

        do {
            current_guess = get_character();
        } while (used_character(guess_list, current_guess));

        my_string_push_back(guess_list, current_guess);
        my_string_push_back(guess_list, ',');
        my_string_push_back(guess_list, ' ');

        if (running_total) {
            printf("Running total of words remaining:\n");
        }


        //  Issue with either get_word_key_value (avl tree problem) or avl_tree_push
        for (indx=0; indx < generic_vector_get_size(dict[word_len]); indx++) {
            printf("Got into the for loop...\n");
            get_word_key_value(word_key, word_family, generic_vector_at(dict[word_len], indx), current_guess);
            printf("Got past word_key_value.\n");
            avl_tree_push(hTree, word_family, generic_vector_at(dict[word_len], indx));
            printf("Got past avl_push.\n");
        }
        
        largest_family = avl_tree_get_largest_family(hTree, running_total);
        generic_vector_destroy(&(dict[word_len]));
        dict[word_len] = generic_vector_init_default((ITEM)my_string_assignment, my_string_destroy);

        for (indx=0; indx < generic_vector_get_size(largest_family); indx++) {
            generic_vector_push_back(dict[word_len], generic_vector_at(largest_family, indx));
        }

        get_word_key_value(word_key, word_family, generic_vector_at(dict[word_len], 0), current_guess);
        
        if (my_string_compare(word_key, word_family) == 0) {
            printf("\nIncorrect, word does not have %c in it\n\n", current_guess);
            number_guesses--;
        }

        my_string_assignment(&word_key, word_family);

        generic_vector_destroy(&largest_family);
        avl_tree_destroy(&hTree);
        my_string_destroy(&word_family);

        word_family = my_string_init_default();
        hTree = avl_tree_init_default();
        
        if (number_guesses == 0) {
            printf("Game over.\n The word was: ");
            my_string_insertion(generic_vector_at(dict[word_len], 0), stdout);
            printf("\n\n");
            break;
        }
    } while(number_guesses > 0);
    
    
    avl_tree_destroy(&hTree);
    my_string_destroy(&word_key);
    my_string_destroy(&guess_list);
    my_string_destroy(&word_family);
    for (indx=0; indx < 30; indx++) {
        generic_vector_destroy(&dict[indx]);
    }
    generic_vector_destroy(&largest_family);
}