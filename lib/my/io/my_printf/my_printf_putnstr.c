/*
** EPITECH PROJECT, 2025
** my_printf_putnstr
** File description:
** Print the first n characters of a string
*/

#include <stddef.h>

#include "my/misc.h"
#include "my/printf/io.h"
#include "my/printf/types.h"

int my_printf_putnstr(printf_buffer_t *buffer, const char *str, size_t n)
{
    for (size_t i = 0; i < n; i++)
        my_printf_putchar(buffer, str[i]);
    return SUCCESS;
}
