/*
** EPITECH PROJECT, 2025
** flag_sharp
** File description:
** Handle the # flag
*/

#include "my/printf/types.h"

void my_printf_flag_sharp(specifier_info_t *specifier_info)
{
    specifier_info->is_alternate_form = true;
}
