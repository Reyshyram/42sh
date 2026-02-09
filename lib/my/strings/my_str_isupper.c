/*
** EPITECH PROJECT, 2025
** my_str_isupper
** File description:
** Check if a string is only using uppercase letters
*/

#include <stddef.h>

#include "my/strings.h"

bool my_str_isupper(const char *str)
{
    for (size_t i = 0; i < my_strlen(str); i++)
        if (!my_isupper(str[i]))
            return false;
    return true;
}
