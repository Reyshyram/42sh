/*
** EPITECH PROJECT, 2025
** my_putnbr_padding
** File description:
** Print a number with padding
*/

#include "my/io.h"
#include "my/numbers.h"
#include <stddef.h>

int my_putnbr_padding(__int128_t nb, size_t n_digits)
{
    return my_putnbr_base_padding(nb, BASE_10, n_digits);
}
