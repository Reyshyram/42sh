/*
** EPITECH PROJECT, 2025
** my_strncpy
** File description:
** Copy n characters of a string into another
*/

#include <stddef.h>

char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
