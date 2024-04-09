#ifndef HANGMAN_DRIVER_H
#define HANGMAN_DRIVER_H

#include "status.h"
#include "generic_vector.h"
#include "./my_string.h"

void vector_dictionary(GENERIC_VECTOR dictionary[]);

Boolean continue_game(void);

Boolean total_words_remaining(void);

int word_length(void);

int number_of_guesses(void);

char get_character(void);

void clear_keyboard_buffer(void);

void clear_screen(void);

#endif//HANGMAN_DRIVER_H