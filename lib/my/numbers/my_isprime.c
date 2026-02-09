/*
** EPITECH PROJECT, 2025
** my_isprime
** File description:
** Check wether a number is prime or not
** (it is not prime if it is a multiple of 2 or 3)
*/

#include <stddef.h>

bool my_isprime(int nb)
{
    if (nb <= 1)
        return false;
    if (nb <= 3)
        return true;
    if (nb % 2 == 0 || nb % 3 == 0)
        return false;
    for (size_t i = 5; (int) i < ((nb / 2) + 1); i++) {
        if (nb % i == 0)
            return false;
    }
    return true;
}
