/*
** EPITECH PROJECT, 2025
** flag_capital_s
** File description:
** Handle the S conversion specifier
*/

#include <stdarg.h>

#include "my/printf/flags.h"
#include "my/printf/types.h"

void my_printf_flag_capital_s(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    specifier_info->conversion_type = LONG;
    my_printf_flag_s(buffer, specifier_info, args);
}
