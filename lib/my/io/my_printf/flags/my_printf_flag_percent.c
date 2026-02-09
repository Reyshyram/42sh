/*
** EPITECH PROJECT, 2025
** flag_percent
** File description:
** Handle the % conversion specifiers
*/

#include <stdarg.h>

#include "my/printf/io.h"
#include "my/printf/types.h"

void my_printf_flag_percent(printf_buffer_t *buffer,
    [[maybe_unused]] specifier_info_t *specifier_info,
    [[maybe_unused]] va_list args)
{
    my_printf_putchar(buffer, '%');
}
