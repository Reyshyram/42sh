/*
** EPITECH PROJECT, 2025
** flag_minus
** File description:
** Handle the - flag
*/

#include "my/printf/types.h"

void my_printf_flag_minus(specifier_info_t *specifier_info)
{
    specifier_info->padding_char = ' ';
    specifier_info->is_padding_on_left = false;
}
