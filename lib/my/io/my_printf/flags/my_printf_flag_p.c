/*
** EPITECH PROJECT, 2025
** flag_p
** File description:
** Handle the p conversion specifier
*/

#include <stdarg.h>
#include <stddef.h>

#include "my/numbers.h"
#include "my/printf/io.h"
#include "my/printf/types.h"

static void handle_special_cases(specifier_info_t *specifier_info,
    const size_t *nb, size_t *nb_length)
{
    if (nb != nullptr) {
        specifier_info->field_width -= 2;
    } else {
        specifier_info->precision = 0;
        *nb_length = 5;
        if (specifier_info->leading_char)
            *nb_length = 4;
    }
}

void my_printf_flag_p(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    unsigned long *nb = va_arg(args, void *);
    size_t nb_length = my_getnbr_length_base((unsigned long) nb, 16);
    bool is_positive = true;

    handle_special_cases(specifier_info, nb, &nb_length);
    if (specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, nb_length);
    if (nb != nullptr) {
        my_printf_put_leading_char(buffer, specifier_info, is_positive);
        my_printf_putstr(buffer, "0x");
        my_printf_put_precision(buffer, specifier_info, nb_length);
        my_printf_putnbr_base(buffer, (unsigned long) nb, BASE_16);
    } else {
        my_printf_putstr(buffer, "(nil)");
    }
    if (!specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, nb_length);
}
