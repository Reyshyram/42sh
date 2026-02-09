/*
** EPITECH PROJECT, 2025
** get_uarg
** File description:
** Get the correct arg type for unsigned values
*/

#include <stdarg.h>
#include <stddef.h>

#include "my/printf/types.h"

unsigned long my_printf_get_uarg(const specifier_info_t *specifier_info,
    va_list args)
{
    switch (specifier_info->conversion_type) {
        case CHAR:
            return (unsigned char) va_arg(args, unsigned int);
        case SHORT:
            return (unsigned short) va_arg(args, unsigned int);
        case PTRDIFF_T:
            return va_arg(args, ptrdiff_t);
        case LONG:
        case INTMAX_T:
        case SIZE_T:
            return va_arg(args, unsigned long);
        default:
            return va_arg(args, unsigned int);
    }
}
