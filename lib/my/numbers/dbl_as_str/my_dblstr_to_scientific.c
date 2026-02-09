/*
** EPITECH PROJECT, 2025
** my_dblstr_to_scientific
** File description:
** Convert to scientific notation
*/

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#include "my/misc.h"
#include "my/numbers.h"
#include "my/strings.h"

static void find_parts(const dbl_as_str_t *str, ssize_t *dot,
    ssize_t *first_nonzero, size_t start)
{
    size_t len = my_strlen(str);

    for (size_t i = start; i < len; i++) {
        if (str[i] == '.' && *dot == -1) {
            *dot = (ssize_t) i;
            continue;
        }
        if (*first_nonzero == -1 && str[i] != '0' && str[i] != '.')
            *first_nonzero = (ssize_t) i;
    }
    if (*dot == -1)
        *dot = (ssize_t) len;
}

static int compute_exponent(ssize_t dot, ssize_t first_nonzero)
{
    if (dot > first_nonzero)
        return (int) dot - (int) first_nonzero - 1;
    return (int) -(first_nonzero - dot);
}

static uint16_t add_nb(char *result, const dbl_as_str_t *digits,
    ssize_t first_nonzero, int precision)
{
    size_t len = my_strlen(digits);
    uint16_t pos = 2;
    size_t nb_chars_added = 0;

    result[0] = digits[first_nonzero];
    result[1] = '.';
    for (size_t i = first_nonzero + 1;
        i < len && (int) nb_chars_added < precision; i++) {
        if (digits[i] == '.')
            continue;
        result[pos] = digits[i];
        pos++;
        nb_chars_added++;
    }
    while ((int) nb_chars_added < precision) {
        result[pos] = '0';
        pos++;
        nb_chars_added++;
    }
    return pos;
}

static uint16_t add_exponent(char *result, uint16_t pos, int exponent)
{
    size_t exponent_length = 0;
    char tmp[6];

    result[pos - 1] = (exponent >= 0) ? '+' : '-';
    if (exponent >= 100) {
        while (exponent > 0) {
            tmp[exponent_length] = (char) ('0' + (exponent % 10));
            exponent_length++;
            exponent /= 10;
        }
        for (ssize_t i = (ssize_t) exponent_length - 1; i >= 0; i--) {
            result[pos] = tmp[i];
            pos++;
        }
    } else {
        result[pos] = (char) ('0' + ((exponent / 10) % 10));
        result[pos + 1] = (char) ('0' + (exponent % 10));
        pos += 2;
    }
    return pos;
}

dbl_as_str_t *my_dblstr_to_scientific(dbl_as_str_t *str, bool is_capital,
    int precision)
{
    int sign = (str[0] == '-');
    size_t start = sign ? 1 : 0;
    ssize_t dot = -1;
    ssize_t first_nonzero = -1;
    int exponent = 0;
    uint16_t pos = 0;
    dbl_as_str_t *result = my_calloc(precision + 10, sizeof(char));

    find_parts(str, &dot, &first_nonzero, start);
    exponent = compute_exponent(dot, first_nonzero);
    if (sign) {
        result[pos] = '-';
        pos++;
    }
    pos += add_nb(result + pos, str, first_nonzero, precision) + 2;
    result[pos - 2] = is_capital ? 'E' : 'e';
    pos = add_exponent(result, pos, ABS(exponent));
    result[pos] = '\0';
    free(str);
    return result;
}
