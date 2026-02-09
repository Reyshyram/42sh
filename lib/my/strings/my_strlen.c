/*
** EPITECH PROJECT, 2025
** my_strlen
** File description:
** Return the given string's length
*/

#include <stddef.h>

size_t my_strlen(const char *str)
{
    size_t length = 0;

    if (str == nullptr)
        return 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}
