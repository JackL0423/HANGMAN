#include <stdio.h>
#include <stdlib.h>

#include "./headers/hangmanGameDriver.h"
#include "./headers/my_string.h"
#include "./headers/generic_vector.h"
#include "./headers/avl_tree.h"
#include "./headers/hangman_driver.h"

void hangman_driver(void) {
    GENERIC_VECTOR *dict = vector_dictionary();
    GENERIC_VECTOR largest_family = NULL;
    TREE hTree = avl_tree_init_default();
    MY_STRING word_key = my_string_init_default();
    MY_STRING guess_list = my_string_init_c_string(" ");
    MY_STRING word_family = my_string_init_default();
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
    
    

    generic_vector_destroy(dict);
    generic_vector_destroy(&largest_family);
    avl_tree_destroy(&hTree);
    my_string_destroy(&word_key);
    my_string_destroy(&guess_list);
    my_string_destroy(&word_family);

}