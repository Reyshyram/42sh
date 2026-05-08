/*
** EPITECH PROJECT, 2025
** my_str_isnum
** File description:
** Check if a string is only using numbers
*/

#include <string.h>

#include "my/strings.h"

bool my_str_isnum(const char *str)
{
    size_t start = 0;

    if (str[0] == '-')
        start = 1;
    for (size_t i = start; i < strlen(str); i++)
        if (!my_isnumber(str[i]))
            return false;
    return true;
}
