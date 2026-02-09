/*
** EPITECH PROJECT, 2025
** my_getnbr_length_base
** File description:
** Return the number of characters in a number, given a divisor
*/

#include <stddef.h>

size_t my_getnbr_length_base(__int128_t nb, size_t divisor)
{
    size_t nb_length = 0;

    if (nb == 0)
        return 1;
    if (nb < 0)
        nb_length++;
    while (nb != 0) {
        nb_length++;
        nb /= divisor;
    }
    return nb_length;
}
