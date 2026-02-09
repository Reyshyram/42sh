/*
** EPITECH PROJECT, 2025
** flag_space
** File description:
** Handle the space flag
*/

#include "my/printf/types.h"

void my_printf_flag_space(specifier_info_t *specifier_info)
{
    if (specifier_info->leading_char == '+')
        return;
    specifier_info->leading_char = ' ';
}
