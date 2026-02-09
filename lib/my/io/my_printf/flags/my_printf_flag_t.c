/*
** EPITECH PROJECT, 2025
** flag_t
** File description:
** Handle the t length modifier
*/

#include "my/printf/types.h"

void my_printf_flag_t(specifier_info_t *specifier_info)
{
    specifier_info->conversion_type = PTRDIFF_T;
}
