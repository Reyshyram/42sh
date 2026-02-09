/*
** EPITECH PROJECT, 2025
** str_round
** File description:
** round a double represented by a string
*/

#include "my/numbers.h"
#include "my/strings.h"

static void round_digits(dbl_as_str_t *digits, int *length)
{
    if (digits[*length] >= '5') {
        digits[*length] = '0';
        (*length)--;
    }
    while (*length >= 0 && digits[*length] >= '9') {
        digits[*length] = '0';
        (*length)--;
    }
}

// Rounds a float like printf would
dbl_as_str_t *my_str_round(dbl_as_str_t *digits)
{
    int digits_length = (int) my_strlen(digits);
    int length = digits_length - 1;

    if (length < 0)
        return digits;
    round_digits(digits, &length);
    if (length != digits_length - 1) {
        if (length == -1) {
            digits[0] = '1';
            return digits;
        }
        digits[length] += 1;
    }
    digits[digits_length - 1] = '\0';
    return digits;
}
