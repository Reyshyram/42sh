/*
** EPITECH PROJECT, 2025
** my_strlowcase
** File description:
** Put every letter of the given string in lowercase
*/

#include <stddef.h>

#include "my/strings.h"

char *my_strlowcase(char *str)
{
    for (size_t i = 0; i < my_strlen(str); i++)
        if (my_isupper(str[i]))
            str[i] += 'a' - 'A';
    return str;
}
