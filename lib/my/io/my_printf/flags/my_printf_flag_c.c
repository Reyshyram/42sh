/*
** EPITECH PROJECT, 2025
** flag_c
** File description:
** Handle the c conversion specifier
*/

#include <stdarg.h>
#include <wchar.h>

#include "my/printf/io.h"
#include "my/printf/types.h"

static unsigned int get_arg(const specifier_info_t *specifier_info,
    va_list args)
{
    switch (specifier_info->conversion_type) {
        case LONG:
            return va_arg(args, wint_t);
        default:
            return (unsigned char) va_arg(args, int);
    }
}

void my_printf_flag_c(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    unsigned int c = get_arg(specifier_info, args);
    size_t length = 1;
    bool is_positive = true;

    specifier_info->is_unsigned = true;
    specifier_info->precision = 0;
    if (specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, length);
    my_printf_putchar(buffer, (char) c);
    if (!specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, length);
}
