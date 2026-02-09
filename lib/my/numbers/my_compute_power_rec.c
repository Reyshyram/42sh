/*
** EPITECH PROJECT, 2025
** my_compute_power_rec
** File description:
** Compute an exponent recursively
*/

#include <limits.h>

int my_compute_power_rec(int nb, int p)
{
    long result = (long) nb;

    if (p < 0)
        return 0;
    if (p == 0)
        return 1;
    result *= my_compute_power_rec((int) result, p - 1);
    if (result > INT_MAX)
        return 0;
    return (int) result;
}
