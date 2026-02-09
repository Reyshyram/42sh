/*
** EPITECH PROJECT, 2025
** my_putnbr_base_padding
** File description:
** Print a number with padding using a given base
*/

#include <stddef.h>

#include "my/io.h"
#include "my/misc.h"
#include "my/numbers.h"
#include "my/strings.h"

static int my_putnbr_base_padding_callback(__int128_t nb, const char *base,
    size_t base_len)
{
    if (nb >= base_len)
        my_putnbr_base_padding_callback(nb / base_len, base, base_len);
    my_putchar(base[nb % base_len]);
    return SUCCESS;
}

int my_putnbr_base_padding(__int128_t nb, const char *base, size_t n_digits)
{
    size_t base_length = my_strlen(base);
    size_t nb_length = my_getnbr_length_base(nb, base_length);

    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    for (size_t i = 0; i < n_digits - nb_length; i++)
        my_putchar('0');
    my_putnbr_base_padding_callback(nb, base, base_length);
    return SUCCESS;
}
