/*
** EPITECH PROJECT, 2025
** flag_n
** File description:
** Handle the n conversion specifier
*/

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "my/printf/types.h"

static void check_others(const printf_buffer_t *buffer,
    const specifier_info_t *specifier_info, va_list args)
{
    switch (specifier_info->conversion_type) {
        case SIZE_T:
            *va_arg(args, size_t *) = buffer->length;
            break;
        case PTRDIFF_T:
            *va_arg(args, ptrdiff_t *) = (ptrdiff_t) buffer->length;
            break;
        default:
            *va_arg(args, int *) = (int) buffer->length;
            break;
    }
}

void my_printf_flag_n(const printf_buffer_t *buffer,
    const specifier_info_t *specifier_info, va_list args)
{
    switch (specifier_info->conversion_type) {
        case CHAR:
            *va_arg(args, char *) = (char) buffer->length;
            break;
        case SHORT:
            *va_arg(args, short *) = (short) buffer->length;
            break;
        case LONG:
            *va_arg(args, long *) = (long) buffer->length;
            break;
        case INTMAX_T:
            *va_arg(args, intmax_t *) = (intmax_t) buffer->length;
            break;
        default:
            check_others(buffer, specifier_info, args);
            break;
    }
}
