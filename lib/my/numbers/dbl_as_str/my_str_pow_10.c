/*
** EPITECH PROJECT, 2025
** str_pow_10
** File description:
** powers of 10 on a double represented by a string
*/

#include <stddef.h>

#include "my/misc.h"
#include "my/numbers.h"
#include "my/strings.h"

dbl_as_str_t *my_str_pow10(const dbl_as_str_t *num, size_t n)
{
    size_t len = my_strlen(num);
    dbl_as_str_t *result = my_calloc(len + n + 1, sizeof(char));

    if (!result)
        return nullptr;
    my_strcpy(result, num);
    for (size_t i = 0; i < n; i++)
        result[len + i] = '0';
    return result;
}
