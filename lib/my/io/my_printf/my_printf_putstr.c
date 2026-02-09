/*
** EPITECH PROJECT, 2025
** my_printf_putstr
** File description:
** Print a string
*/

#include <stddef.h>

#include "my/misc.h"
#include "my/printf/io.h"
#include "my/printf/types.h"

int my_printf_putstr(printf_buffer_t *buffer, const char *str)
{
    for (size_t i = 0; str[i]; i++)
        my_printf_putchar(buffer, str[i]);
    return SUCCESS;
}
