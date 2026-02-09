/*
** EPITECH PROJECT, 2025
** my_strhelper
** File description:
** Helper functions for string related operations
*/

#include <stddef.h>

bool my_isupper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

bool my_islower(char c)
{
    return (c >= 'a' && c <= 'z');
}

bool my_isnumber(char c)
{
    return (c >= '0' && c <= '9');
}

bool my_isprintable(char c)
{
    return (c >= 32 && c <= 126);
}

int my_getindex(char c, const char *str)
{
    size_t index = 0;

    while (*str) {
        if (c == *str)
            return (int) index;
        str++;
        index++;
    }
    return -1;
}
