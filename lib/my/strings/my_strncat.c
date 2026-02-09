/*
** EPITECH PROJECT, 2025
** my_strncat
** File description:
** Concatenate two strings using n characters of the source string
*/

#include <stddef.h>

#include "my/strings.h"

char *my_strncat(char *dest, const char *src, size_t nb)
{
    my_strncpy(dest + my_strlen(dest), src, nb);
    return dest;
}
