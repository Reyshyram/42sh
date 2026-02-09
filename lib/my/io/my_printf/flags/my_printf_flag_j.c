/*
** EPITECH PROJECT, 2025
** flag_j
** File description:
** Handle the j length modifier
*/

#include "my/printf/types.h"

void my_printf_flag_j(specifier_info_t *specifier_info)
{
    specifier_info->conversion_type = INTMAX_T;
}
