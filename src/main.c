#include <stdio.h>
#include <stdlib.h>

#include "headers/hangman_driver.h"
#include "headers/hangmanGameDriver.h"

int main(int argc, char const *argv[])
{
    //  do {} while loop for the code to run in here.
    do {
        hangman_driver();
    } while (continue_game());
    
    return 0;
}