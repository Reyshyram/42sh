/*
** EPITECH PROJECT, 2025
** my_strndup
** File description:
** Duplicate the first n characters of a string
*/

#include "my/strings.h"
#include <stdlib.h>

char *my_strndup(const char *src, size_t nb_chars)
{
    char *result = malloc(sizeof(char) * (nb_chars + 1));

    if (!result)
        return nullptr;
    my_strncpy(result, src, nb_chars);
    return result;
}
