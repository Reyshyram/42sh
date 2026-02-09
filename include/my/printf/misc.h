/*
** EPITECH PROJECT, 2025
** my/printf/misc.h
** File description:
** Misc functions for my_printf
*/

#ifndef MY_PRINTF_MISC_H
// clang-format off
    #define MY_PRINTF_MISC_H

    #include "my/printf/types.h"
// clang-format on

long my_printf_get_arg(specifier_info_t *specifier_info, va_list args);
long my_printf_get_uarg(specifier_info_t *specifier_info, va_list args);

#endif /* MY_PRINTF_MISC_H */
