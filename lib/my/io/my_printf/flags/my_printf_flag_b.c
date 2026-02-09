/*
** EPITECH PROJECT, 2025
** flag_b
** File description:
** Handle the b conversion specifier
*/

#include <stdarg.h>
#include <stddef.h>

#include "my/numbers.h"
#include "my/printf/io.h"
#include "my/printf/misc.h"
#include "my/printf/types.h"

static void handle_special_cases(specifier_info_t *specifier_info,
    const unsigned long *nb, size_t *nb_length)
{
    if (*nb == 0 && specifier_info->precision == 0
        && !specifier_info->is_alternate_form)
        (*nb_length)--;
    if (*nb != 0 && specifier_info->is_alternate_form) {
        specifier_info->field_width -= 2;
    }
}

void my_printf_flag_b(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    unsigned long nb = my_printf_get_uarg(specifier_info, args);
    size_t nb_length = my_getnbr_length_base(nb, 2);
    bool is_positive = true;

    specifier_info->is_unsigned = true;
    handle_special_cases(specifier_info, &nb, &nb_length);
    if (specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, nb_length);
    if (nb != 0 && specifier_info->is_alternate_form)
        my_printf_putstr(buffer, specifier_info->is_capital ? "0B" : "0b");
    my_printf_put_precision(buffer, specifier_info, nb_length);
    if (!(nb == 0 && specifier_info->precision == 0))
        my_printf_putnbr_base(buffer, nb, BASE_2);
    if (!specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, is_positive, nb_length);
}
