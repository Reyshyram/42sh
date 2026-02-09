/*
** EPITECH PROJECT, 2025
** str_divide_2
** File description:
** divide by 2 a double represented by a string
*/

#include "my/misc.h"
#include "my/numbers.h"
#include "my/strings.h"
#include <stdlib.h>

// Strip the result to remove 0s
static dbl_as_str_t *strip_result(const dbl_as_str_t *result, size_t pos)
{
    char *result_stripped = nullptr;
    size_t start_no_zeroes = 0;

    while (start_no_zeroes < pos - 1 && result[start_no_zeroes] == '0')
        start_no_zeroes++;
    result_stripped = my_calloc(pos - start_no_zeroes + 1, sizeof(char));
    if (!result_stripped)
        return nullptr;
    my_strncpy(result_stripped, result + start_no_zeroes,
        pos - start_no_zeroes);
    result_stripped[pos - start_no_zeroes] = '\0';
    return result_stripped;
}

dbl_as_str_t *my_str_divide_2(const dbl_as_str_t *num)
{
    size_t len = my_strlen(num);
    dbl_as_str_t *result = my_calloc(len + 1, sizeof(char));
    dbl_as_str_t *result_stripped = nullptr;
    int carry = 0;
    int current_digit = 0;
    size_t pos = 0;

    if (!result)
        return nullptr;
    for (size_t i = 0; i < len; i++) {
        current_digit = (carry * 10) + (num[i] - '0');
        result[pos] = (char) ((current_digit / 2) + '0');
        carry = current_digit % 2;
        pos++;
    }
    result_stripped = strip_result(result, pos);
    free(result);
    return result_stripped;
}
