/*
** EPITECH PROJECT, 2025
** get_arg
** File description:
** Get the correct arg type for signed values
*/

#include <stdarg.h>

#include "my/printf/types.h"

long my_printf_get_arg(const specifier_info_t *specifier_info, va_list args)
{
    switch (specifier_info->conversion_type) {
        case CHAR:
            return (char) va_arg(args, int);
        case SHORT:
            return (short) va_arg(args, int);
        case LONG:
        case INTMAX_T:
        case SIZE_T:
        case PTRDIFF_T:
            return va_arg(args, long);
        default:
            return va_arg(args, int);
    }
}
