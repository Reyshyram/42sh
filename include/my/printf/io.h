/*
** EPITECH PROJECT, 2025
** my/printf/io.h
** File description:
** io functions for my_printf
*/

#ifndef MY_PRINTF_IO_H
// clang-format off
    #define MY_PRINTF_IO_H

    #include "my/printf/types.h"
// clang-format on

void my_printf_putchar(printf_buffer_t *buffer, char c);
int my_printf_putstr(printf_buffer_t *buffer, const char *str);
int my_printf_putnstr(printf_buffer_t *buffer, const char *str, size_t n);
void my_printf_repeat_char(printf_buffer_t *buffer, char c, size_t n);
int my_printf_putnbr_base(printf_buffer_t *buffer, __int128_t nb,
    const char *base);

void my_printf_put_leading_char(printf_buffer_t *buffer,
    const specifier_info_t *specifier_info, bool is_positive);
void my_printf_put_precision(printf_buffer_t *buffer,
    const specifier_info_t *specifier_info, size_t nb_length);
void my_printf_put_padding(printf_buffer_t *buffer,
    const specifier_info_t *specifier_info, bool is_positive,
    size_t nb_length);

#endif /* MY_PRINTF_IO_H */
