/*
** EPITECH PROJECT, 2025
** flag_capital_e
** File description:
** Handle the E conversion specifier
*/

#include <stdarg.h>

#include "my/printf/flags.h"
#include "my/printf/types.h"

void my_printf_flag_capital_e(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    specifier_info->is_capital = true;
    my_printf_flag_e(buffer, specifier_info, args);
}
