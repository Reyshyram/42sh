/*
** EPITECH PROJECT, 2025
** my_find_prime_sup
** File description:
** Find the smallest prime that is at least equal to the given number
*/

#include "my/misc.h"
#include "my/numbers.h"
#include <limits.h>

int my_find_prime_sup(int nb)
{
    for (int i = nb; i <= INT_MAX; i++)
        if (my_isprime(i))
            return i;
    return SUCCESS;
}
