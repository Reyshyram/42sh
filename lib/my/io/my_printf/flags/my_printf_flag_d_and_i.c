/*
** EPITECH PROJECT, 2025
** flag_d_and_i
** File description:
** Handle the d and i conversion specifiers
*/

#include <stdarg.h>
#include <stddef.h>

#include "my/numbers.h"
#include "my/printf/io.h"
#include "my/printf/misc.h"
#include "my/printf/types.h"

static void handle_special_cases(const specifier_info_t *specifier_info,
    __int128_t *nb, size_t *nb_length)
{
    if (*nb < 0) {
        *nb = -(*nb);
        (*nb_length)--;
    }
    if (*nb == 0 && specifier_info->precision == 0)
        (*nb_length)--;
}

void my_printf_flag_d_and_i(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    __int128_t nb = my_printf_get_arg(specifier_info, args);
    size_t nb_length = my_getnbr_length(nb);
    bool is_positive = nb >= 0;

    handle_special_cases(specifier_info, &nb, &nb_length);
    if (specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, nb_length);
    my_printf_put_leading_char(buffer, specifier_info, is_positive);
    if (!is_positive)
        my_printf_putchar(buffer, '-');
    my_printf_put_precision(buffer, specifier_info, nb_length);
    if (!(nb == 0 && specifier_info->precision == 0))
        my_printf_putnbr_base(buffer, nb, BASE_10);
    if (!specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, nb_length);
}
