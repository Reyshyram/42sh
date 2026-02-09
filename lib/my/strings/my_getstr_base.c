/*
** EPITECH PROJECT, 2025
** my_getstr_base
** File description:
** convert a number into a given base
*/

#include <stdlib.h>
#include <sys/types.h>

#include "my/numbers.h"
#include "my/strings.h"

static void initialize(char *result, const size_t *nb_length, size_t *min,
    __int128_t *nb)
{
    result[*nb_length] = '\0';
    if (*nb < 0) {
        result[0] = '-';
        *min += 1;
        *nb *= -1;
    }
}

char *my_getstr_base(__int128_t nb, const char *base)
{
    size_t n = my_strlen(base);
    size_t nb_length = my_getnbr_length_base(nb, n);
    char *result = malloc(sizeof(char) * (nb_length + 1));
    ssize_t i = (ssize_t) nb_length - 1;
    size_t min = 0;

    if (!result)
        return nullptr;
    initialize(result, &nb_length, &min, &nb);
    while (i >= (ssize_t) min) {
        result[i] = base[nb % n];
        nb /= n;
        i--;
    }
    return result;
}
