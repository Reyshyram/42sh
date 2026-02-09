/*
** EPITECH PROJECT, 2025
** flag_z
** File description:
** Handle the z length modifier
*/

#include "my/printf/types.h"

void my_printf_flag_z(specifier_info_t *specifier_info)
{
    specifier_info->conversion_type = SIZE_T;
}
