/*
** EPITECH PROJECT, 2025
** flag_o
** File description:
** Handle the o conversion specifier
*/

#include <stdarg.h>
#include <stddef.h>

#include "my/numbers.h"
#include "my/printf/io.h"
#include "my/printf/misc.h"
#include "my/printf/types.h"

static void handle_special_cases(const specifier_info_t *specifier_info,
    const size_t *nb, size_t *nb_length)
{
    if (*nb == 0 && specifier_info->precision == 0
        && !specifier_info->is_alternate_form)
        (*nb_length)--;
    if (*nb != 0 && specifier_info->is_alternate_form)
        (*nb_length)++;
}

void my_printf_flag_o(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    unsigned long nb = my_printf_get_uarg(specifier_info, args);
    size_t nb_length = my_getnbr_length_base(nb, 8);
    bool is_positive = true;

    specifier_info->is_unsigned = true;
    handle_special_cases(specifier_info, &nb, &nb_length);
    if (specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, nb_length);
    my_printf_put_precision(buffer, specifier_info, nb_length);
    if (!(nb == 0 && specifier_info->precision == 0)) {
        if (nb != 0 && specifier_info->is_alternate_form)
            my_printf_putchar(buffer, '0');
        my_printf_putnbr_base(buffer, nb, BASE_8);
    }
    if (!specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, nb_length);
}
