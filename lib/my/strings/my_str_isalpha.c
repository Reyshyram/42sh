/*
** EPITECH PROJECT, 2025
** my_str_isalpha
** File description:
** Check if a string is only using letters
*/

#include <stddef.h>

#include "my/strings.h"

bool my_str_isalpha(const char *str)
{
    for (size_t i = 0; i < my_strlen(str); i++)
        if (!(my_isupper(str[i]) || my_islower(str[i])))
            return false;
    return true;
}
