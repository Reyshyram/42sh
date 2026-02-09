/*
** EPITECH PROJECT, 2025
** my_revstr
** File description:
** Reverse a string
*/

#include <stddef.h>

#include "my/strings.h"

char *my_revstr(char *str)
{
    char *start = str;
    char *end = str;
    char temp;

    while (*end != '\0')
        end++;
    end--;
    for (size_t i = 0; i < my_strlen(str) / 2; i++) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    return str;
}
