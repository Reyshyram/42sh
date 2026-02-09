/*
** EPITECH PROJECT, 2025
** my_strcat
** File description:
** Concatenate two strings
*/

#include "my/strings.h"

char *my_strcat(char *dest, const char *src)
{
    my_strcpy(dest + my_strlen(dest), src);
    return dest;
}
