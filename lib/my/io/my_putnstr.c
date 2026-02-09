/*
** EPITECH PROJECT, 2025
** my_putnstr
** File description:
** Print the first n characters of a string
*/

#include <stddef.h>
#include <unistd.h>

#include "my/misc.h"

int my_putnstr(const char *str, size_t n)
{
    write(1, str, n);
    return SUCCESS;
}
