#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_chars(const void *a, const void *b) {
    return (*(char *) a - *(char *) b);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <secret_word>\n", argv[0]);
        return 1;
    }
    char word[MAX_LENGTH + 1];
    strncpy(word, argv[1], MAX_LENGTH + 1);
    if (!validate_secret(word)) {
        return 1;
    }
    bool gameOver = false;
    const char *statement = "";
    char guess;
    size_t i;
    int bad = 0;
    size_t wordlength = strlen(word);
    char secret[wordlength + 1];
    for (i = 0; i < wordlength; i++) {
        if (word[i] == ' ' || word[i] == '-' || word[i] == '\'') {
            secret[i] = word[i];
        } else {
            secret[i] = '_';
        }
    }
    char eliminated[LOSING_MISTAKE + 1];
    eliminated[0] = '\0';
    secret[wordlength] = '\0';

    char guessed[MAX_LENGTH] = "";

    while (!gameOver) {
        printf("%s", CLEAR_SCREEN);
        printf("%s\n", arts[bad]);
        printf("\n    Phrase: %s\n", secret);
        qsort(eliminated, strlen(eliminated), sizeof(char), compare_chars);
        printf("Eliminated: %s\n\n", eliminated);
        guess = read_letter();

        while (string_contains_character(eliminated, guess)
               || string_contains_character(guessed, guess) || !is_lowercase_letter(guess)) {
            guess = read_letter();
        }

        if (string_contains_character(word, guess)) {
            for (size_t j = 0; j < wordlength; j++) {
                if (word[j] == guess) {
                    secret[j] = guess;
                    guessed[strlen(guessed)] = guess;
                }
            }
        }

        else {
            if (!string_contains_character(eliminated, guess)) {
                bad = bad + 1;
                strncat(eliminated, &guess, 1);
            }
        }

        if (strlen(eliminated) == LOSING_MISTAKE) {
            gameOver = true;
            statement = "You lose!";
        }

        if (strchr(secret, '_') == NULL) {
            gameOver = true;
            statement = "You win!";
        }
    }

    if (gameOver) {
        printf("%s", CLEAR_SCREEN);
        printf("%s\n", arts[bad]);
        printf("\n    Phrase: %s\n", secret);
        qsort(eliminated, strlen(eliminated), sizeof(char), compare_chars);
        printf("Eliminated: %s\n\n", eliminated);
        printf("%s The secret phrase was: %s\n", statement, word);
    }

    return 0;
}
