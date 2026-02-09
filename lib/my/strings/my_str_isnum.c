/*
** EPITECH PROJECT, 2025
** my_str_isnum
** File description:
** Check if a string is only using numbers
*/

#include <stddef.h>

#include "my/strings.h"

bool my_str_isnum(const char *str)
{
    for (size_t i = 0; i < my_strlen(str); i++)
        if (!my_isnumber(str[i]))
            return false;
    return true;
}
