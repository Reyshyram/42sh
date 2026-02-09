/*
** EPITECH PROJECT, 2025
** put_precision
** File description:
** Print the precision depending on specifier info and number length
*/

#include <stddef.h>

#include "my/printf/io.h"
#include "my/printf/types.h"

void my_printf_put_precision(printf_buffer_t *buffer,
    const specifier_info_t *specifier_info, size_t nb_length)
{
    int precision = specifier_info->precision - (int) nb_length;

    if (precision > 0)
        my_printf_repeat_char(buffer, '0', precision);
}
