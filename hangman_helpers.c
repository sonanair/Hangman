#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

bool validate_secret(const char *secret) {
    if (secret == NULL) {
        printf("Error: The secret is NULL.\n");
        printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
               "apostrophes\n");
        return false;
    }

    size_t length = strlen(secret);
    if (length > MAX_LENGTH) {
        printf("the secret phrase is over 256 characters\n");
        return false;
    }

    for (size_t i = 0; i < length; i++) {
        char c = secret[i];

        if (!(is_lowercase_letter(c) || c == ' ' || c == '\'' || c == '-')) {
            printf("invalid character: '%c'\n", c);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        }
    }

    return true;
}

bool string_contains_character(const char *s, char c) {
    while (*s) {
        if (*s == c) {
            return true;
        }
        s++;
    }
    return false;
}

char read_letter(void) {
    char guess;
    printf("Guess a letter: ");
    scanf("%c", &guess);
    while (getchar() != '\n')
        ;
    return guess;
}

