/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** Copy a string into another
*/

#include <stddef.h>

#include "my/strings.h"

char *my_strcpy(char *dest, const char *src)
{
    size_t i = 0;

    for (i = 0; src[i]; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
