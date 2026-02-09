/*
** EPITECH PROJECT, 2025
** flag_e
** File description:
** Handle the e conversion specifier
*/

#include <stdarg.h>
#include <stddef.h>

#include "my/numbers.h"
#include "my/printf/io.h"
#include "my/printf/types.h"
#include "my/strings.h"

static void handle_special_cases(bool is_positive, size_t *nb_length)
{
    if (!is_positive) {
        (*nb_length)--;
    }
}

static long double get_arg(const specifier_info_t *specifier_info,
    va_list args)
{
    switch (specifier_info->conversion_type) {
        case LONG_DOUBLE:
            return va_arg(args, long double);
        default:
            return (long double) va_arg(args, double);
    }
}

void my_printf_flag_e(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args)
{
    long double nb = get_arg(specifier_info, args);
    dbl_as_str_info_t infos = {specifier_info->is_capital, true};
    const dbl_as_str_t *nb_as_str = my_getdbl_as_str(nb,
        specifier_info->precision >= 0 ? specifier_info->precision : 6,
        &infos);
    size_t nb_length = my_strlen(nb_as_str);
    union double_representation nb_repr = {.nb = nb};

    handle_special_cases(!nb_repr.bits.sign, &nb_length);
    specifier_info->precision = 0;
    if (specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, !nb_repr.bits.sign,
            nb_length);
    my_printf_put_leading_char(buffer, specifier_info, !nb_repr.bits.sign);
    my_printf_put_precision(buffer, specifier_info, nb_length);
    my_printf_putstr(buffer, nb_as_str);
    if (!specifier_info->is_padding_on_left)
        my_printf_put_padding(buffer, specifier_info, !nb_repr.bits.sign,
            nb_length);
}
