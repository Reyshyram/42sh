/*
** EPITECH PROJECT, 2025
** put_leading_char
** File description:
** Print the leading char depending on specifier info
*/

#include "my/printf/io.h"
#include "my/printf/types.h"

void my_printf_put_leading_char(printf_buffer_t *buffer,
    const specifier_info_t *specifier_info, bool is_positive)
{
    if (is_positive && specifier_info->leading_char)
        my_printf_putchar(buffer, specifier_info->leading_char);
}
