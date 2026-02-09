/*
** EPITECH PROJECT, 2025
** flag_h
** File description:
** Handle the h length modifier
*/

#include "my/printf/types.h"

void my_printf_flag_h(specifier_info_t *specifier_info)
{
    specifier_info->conversion_type = SHORT;
}
