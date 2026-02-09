/*
** EPITECH PROJECT, 2025
** my_printf_putnbr_base
** File description:
** Print a number using a given base
*/

#include <stddef.h>

#include "my/misc.h"
#include "my/printf/io.h"
#include "my/printf/types.h"
#include "my/strings.h"

static int my_printf_putnbr_base_callback(printf_buffer_t *buffer,
    __int128_t nb, const char *base, size_t base_len)
{
    if (nb >= base_len)
        my_printf_putnbr_base_callback(buffer, nb / base_len, base, base_len);
    my_printf_putchar(buffer, base[nb % base_len]);
    return SUCCESS;
}

int my_printf_putnbr_base(printf_buffer_t *buffer, __int128_t nb,
    const char *base)
{
    size_t base_len = my_strlen(base);

    if (nb < 0) {
        my_printf_putchar(buffer, '-');
        nb = -nb;
    }
    return my_printf_putnbr_base_callback(buffer, nb, base, base_len);
}
