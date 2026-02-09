/*
** EPITECH PROJECT, 2025
** my_getnbr_length
** File description:
** Return the number of characters in a number
*/

#include <stddef.h>

#include "my/numbers.h"

size_t my_getnbr_length(__int128_t nb)
{
    return my_getnbr_length_base(nb, 10);
}
