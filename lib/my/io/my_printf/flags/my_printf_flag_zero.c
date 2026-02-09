/*
** EPITECH PROJECT, 2025
** flag_zero
** File description:
** Handle the 0 flag
*/

#include "my/printf/types.h"

void my_printf_flag_zero(specifier_info_t *specifier_info)
{
    if (!specifier_info->is_padding_on_left)
        return;
    specifier_info->padding_char = '0';
}
