/*
** EPITECH PROJECT, 2025
** flag_capital_l
** File description:
** Handle the L length modifier
*/

#include "my/printf/flags.h"
#include "my/printf/types.h"

void my_printf_flag_capital_l(specifier_info_t *specifier_info)
{
    specifier_info->conversion_type = LONG_DOUBLE;
}
