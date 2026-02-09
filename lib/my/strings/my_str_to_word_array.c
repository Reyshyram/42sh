/*
** EPITECH PROJECT, 2026
** my_str_to_word_array.c
** File description:
** Split a string into multiple substrings
*/

#include <stdlib.h>

#include "my/strings.h"

static size_t count_words(const char *str, const char *delims)
{
    size_t nb_words = 0;
    bool in_word = false;
    bool char_in_str = false;

    for (size_t i = 0; str[i]; i++) {
        char_in_str = my_is_char_in_str(delims, str[i]);
        if (char_in_str)
            in_word = false;
        if (!char_in_str && !in_word) {
            in_word = true;
            nb_words++;
        }
    }
    return nb_words;
}

// NOLINTBEGIN(clang-analyzer-security.ArrayBound)
char **my_str_to_word_array(char *str, const char *delims)
{
    char **array = malloc(sizeof(char *) * (count_words(str, delims) + 1));
    size_t i = 0;
    char *saveptr = nullptr;

    if (!array)
        return nullptr;
    for (char *token = my_strtok_r(str, delims, &saveptr); token;
        token = my_strtok_r(nullptr, delims, &saveptr)) {
        array[i] = my_strdup(token);
        i++;
    }
    array[i] = nullptr;
    return array;
}
// NOLINTEND(clang-analyzer-security.ArrayBound)
