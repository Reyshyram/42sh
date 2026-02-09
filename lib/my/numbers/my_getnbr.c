/*
** EPITECH PROJECT, 2025
** my_getnbr
** File description:
** Convert a string into an int
*/

#include "my/numbers.h"

__int128_t my_getnbr(const char *str)
{
    return my_getnbr_base(str, BASE_10);
}
