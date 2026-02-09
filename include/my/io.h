/*
** EPITECH PROJECT, 2025
** my/io.h
** File description:
** IO related functions
*/

#ifndef MY_IO_H
// clang-format off
    #define MY_IO_H

    #include <stddef.h>
// clang-format on

void my_putchar(char c);
int my_putnbr(__int128_t nb);
int my_putnbr_base(__int128_t nb, const char *base);
int my_putnbr_padding(__int128_t nb, size_t n_digits);
int my_putnbr_base_padding(__int128_t nb, const char *base, size_t n_digits);
int my_putstr(const char *str);
int my_putnstr(const char *str, size_t n);
int my_puterr(const char *str);

int my_showstr(const char *str);
int my_show_word_array(char *const *tab);

int my_printf(const char *format, ...);
int my_dprintf(int fd, const char *format, ...);
int my_sprintf(char *str, const char *format, ...);
int my_asprintf(char **str, const char *format, ...);

#endif /* MY_IO_H */
