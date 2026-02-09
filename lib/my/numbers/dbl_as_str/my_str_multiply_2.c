/*
** EPITECH PROJECT, 2025
** str_multiply_2
** File description:
** multiply by 2 a double represented by a string
*/

#include <stdlib.h>
#include <sys/types.h>

#include "my/misc.h"
#include "my/numbers.h"
#include "my/strings.h"

dbl_as_str_t *my_str_multiply_2(const dbl_as_str_t *num)
{
    size_t n = my_strlen(num);
    dbl_as_str_t *result = my_calloc(n + 2, sizeof(char));
    int carry = 0;
    int current_digit = 0;
    ssize_t pos = (ssize_t) n;

    if (!result)
        return nullptr;
    result[n + 1] = '\0';
    for (ssize_t i = (ssize_t) n - 1; i >= 0; i--) {
        current_digit = ((num[i] - '0') * 2) + carry;
        result[pos] = (char) ((current_digit % 10) + '0');
        carry = current_digit / 10;
        pos--;
    }
    if (carry)
        result[pos] = (char) (carry + '0');
    else
        pos++;
    return my_strdup(result + pos);
}
