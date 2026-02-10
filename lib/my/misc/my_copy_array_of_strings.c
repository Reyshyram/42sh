/*
** EPITECH PROJECT, 2026
** my_copy_array_of_strings
** File description:
** Copy an array of strings
*/

#include <stddef.h>
#include <stdlib.h>

#include "my/misc.h"
#include "my/strings.h"

static void free_copy(char **copy, size_t i)
{
    for (size_t j = 0; j < i; j++)
        free(copy[j]);
    free(copy);
}

char **my_copy_array_of_strings(char **array)
{
    size_t array_length = 0;
    size_t current_str_length = 0;
    char **copy = nullptr;

    while (array[array_length])
        array_length++;
    copy = malloc(sizeof(char *) * (array_length + 1));
    if (!copy)
        return nullptr;
    for (size_t i = 0; i < array_length; i++) {
        current_str_length = my_strlen(array[i]);
        copy[i] = malloc(sizeof(char) * (current_str_length + 1));
        if (!copy[i]) {
            free_copy(copy, i);
            return nullptr;
        }
        my_memcpy(copy[i], array[i], current_str_length + 1);
    }
    copy[array_length] = nullptr;
    return copy;
}
