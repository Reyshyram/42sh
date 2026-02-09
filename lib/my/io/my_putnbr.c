/*
** EPITECH PROJECT, 2025
** my_putnbr
** File description:
** Print a number
*/

#include "my/io.h"
#include "my/numbers.h"

int my_putnbr(__int128_t nb)
{
    return my_putnbr_base(nb, BASE_10);
}
