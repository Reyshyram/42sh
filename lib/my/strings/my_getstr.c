/*
** EPITECH PROJECT, 2025
** my_getstr
** File description:
** convert a number into a string
*/

#include "my/numbers.h"
#include "my/strings.h"

char *my_getstr(__int128_t nb)
{
    return my_getstr_base(nb, BASE_10);
}
