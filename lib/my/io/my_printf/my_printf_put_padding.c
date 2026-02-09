/*
** EPITECH PROJECT, 2025
** put_padding
** File description:
** Print the padding depending on specifier info and number length
*/

#include <stddef.h>

#include "my/printf/io.h"
#include "my/printf/types.h"

void my_printf_put_padding(printf_buffer_t *buffer,
    const specifier_info_t *specifier_info, bool is_positive, size_t nb_length)
{
    int padding = specifier_info->field_width;
    int precision = specifier_info->precision - (int) nb_length;

    if (precision > 0)
        padding -= precision;
    if (is_positive && specifier_info->leading_char
        && !specifier_info->is_unsigned) {
        nb_length++;
    }
    padding -= (int) nb_length;
    if (padding > 0) {
        my_printf_repeat_char(buffer, specifier_info->padding_char,
            is_positive ? padding : padding - 1);
    }
}
