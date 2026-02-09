/*
** EPITECH PROJECT, 2025
** my_strdup
** File description:
** Duplicate a string and return a pointer to the new one
*/

#include <stdlib.h>

#include "my/strings.h"

char *my_strdup(const char *src)
{
    size_t n = my_strlen(src);
    char *result = malloc(sizeof(char) * (n + 1));

    if (!result)
        return nullptr;
    my_strcpy(result, src);
    return result;
}
