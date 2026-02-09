/*
** EPITECH PROJECT, 2025
** my_strupcase
** File description:
** Put every letter of the given string in uppercase
*/

#include <stddef.h>

#include "my/strings.h"

char *my_strupcase(char *str)
{
    for (size_t i = 0; i < my_strlen(str); i++)
        if (my_islower(str[i]))
            str[i] -= 'a' - 'A';
    return str;
}
