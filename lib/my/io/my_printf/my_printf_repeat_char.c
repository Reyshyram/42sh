/*
** EPITECH PROJECT, 2025
** my_printf_repeat_char
** File description:
** repeats char n times
*/

#include <stddef.h>

#include "my/printf/io.h"
#include "my/printf/types.h"

void my_printf_repeat_char(printf_buffer_t *buffer, char c, size_t n)
{
    for (size_t i = 0; i < n; i++)
        my_printf_putchar(buffer, c);
}
