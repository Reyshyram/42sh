/*
** EPITECH PROJECT, 2025
** flag_s
** File description:
** Handle the s conversion specifier
*/

#include <stdarg.h>
#include <stddef.h>

#include "my/printf/io.h"
#include "my/printf/types.h"
#include "my/strings.h"

static const char *get_arg(const specifier_info_t *specifier_info,
    va_list args)
{
    switch (specifier_info->conversion_type) {
        case LONG:
            return (const char *) va_arg(args, const wchar_t *);
        default:
            return va_arg(args, const char *);
    }
}

void my_printf_flag_s(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    const char *str = get_arg(specifier_info, args);
    size_t length = my_strlen(str);
    bool is_positive = true;

    specifier_info->is_unsigned = true;
    if (specifier_info->precision < (int) length
        && specifier_info->precision >= 0)
        length = specifier_info->precision;
    specifier_info->precision = 0;
    if (specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, length);
    my_printf_putnstr(buffer, str, length);
    if (!specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, length);
}
