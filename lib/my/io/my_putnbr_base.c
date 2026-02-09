/*
** EPITECH PROJECT, 2025
** my_putnbr_base
** File description:
** Print a number using a given base
*/

#include <stddef.h>

#include "my/io.h"
#include "my/misc.h"
#include "my/strings.h"

static int my_putnbr_base_callback(__int128_t nb, const char *base,
    size_t base_len)
{
    if (nb >= base_len)
        my_putnbr_base_callback(nb / base_len, base, base_len);
    my_putchar(base[nb % base_len]);
    return SUCCESS;
}

int my_putnbr_base(__int128_t nb, const char *base)
{
    size_t base_len = my_strlen(base);

    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    return my_putnbr_base_callback(nb, base, base_len);
}
