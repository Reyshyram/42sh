/*
** EPITECH PROJECT, 2025
** flag_l
** File description:
** Handle the l length modifier
*/

#include "my/printf/types.h"

void my_printf_flag_l(specifier_info_t *specifier_info)
{
    specifier_info->conversion_type = LONG;
}
