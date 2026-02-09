/*
** EPITECH PROJECT, 2025
** my_getdbl_as_str
** File description:
** Get a long double as a string
*/

#include <stdint.h>
#include <stdlib.h>

#include "my/misc.h"
#include "my/numbers.h"
#include "my/strings.h"

/*
** When the exponent is equal to 32768 (all the bits set to 1), it means
** that the double is representing infinity or 0/0.
** Ignore the first bit of the mantisa
*/
static dbl_as_str_t *handle_special_values(dbl_as_str_t *digits,
    union double_representation nb_repr, bool is_capital)
{
    dbl_as_str_t *result = my_calloc(4, sizeof(char));

    if (!result)
        return nullptr;
    free(digits);
    if ((nb_repr.bits.mantisa << 1) >> 1) {
        my_strcpy(result, is_capital ? "NAN" : "nan");
    } else {
        my_strcpy(result, is_capital ? "INF" : "inf");
        if (nb_repr.bits.sign)
            my_strcpy(result, is_capital ? "-INF" : "-inf");
    }
    return result;
}

static dbl_as_str_t *handle_zero_case(dbl_as_str_t *digits,
    union double_representation nb_repr, int precision,
    dbl_as_str_info_t *infos)
{
    dbl_as_str_t *result = my_calloc(7 + precision, sizeof(char));
    uint16_t offset = 1;

    free(digits);
    if (nb_repr.bits.sign) {
        my_strcpy(result, "-");
        offset++;
    }
    my_strcpy(result + offset - 1, "0");
    if (precision > 0) {
        my_strcpy(result + offset, ".");
        offset++;
        for (size_t i = 0; (int) i < precision; i++) {
            my_strcpy(result + offset, "0");
            offset++;
        }
    }
    if (infos->is_scientific)
        my_strcpy(result + offset, infos->is_capital ? "E+00" : "e+00");
    return result;
}

static bool is_special_case(union double_representation nb_repr)
{
    if (nb_repr.bits.exponent == 0x7FFF)
        return true;
    if (nb_repr.bits.exponent == 0 || nb_repr.bits.mantisa == 0)
        return true;
    return false;
}

static dbl_as_str_t *handle_special_case(dbl_as_str_t *digits,
    union double_representation nb_repr, int precision,
    dbl_as_str_info_t *infos)
{
    if (nb_repr.bits.exponent == 0x7FFF)
        return handle_special_values(digits, nb_repr, infos->is_capital);
    return handle_zero_case(digits, nb_repr, precision, infos);
}

// Apply the exponent to the digits by repeating multiplication or divisions
static dbl_as_str_t *apply_exponent(dbl_as_str_t *digits, int exponent)
{
    dbl_as_str_t *tmp = nullptr;

    if (exponent > 0) {
        for (size_t i = 0; (int) i < exponent; i++) {
            tmp = my_str_multiply_2(digits);
            free(digits);
            digits = tmp;
        }
    } else {
        for (size_t i = 0; (int) i < -exponent; i++) {
            tmp = my_str_divide_2(digits);
            free(digits);
            digits = tmp;
        }
    }
    return digits;
}

static void get_final_result_precision_gt_or_eq_len(dbl_as_str_t *result,
    const dbl_as_str_t *digits, int precision, size_t offset)
{
    size_t len = my_strlen(digits);

    my_strcpy(result + offset, "0.");
    offset += 2;
    for (size_t i = 0; i < precision - len; i++) {
        my_strcpy(result + offset, "0");
        offset++;
    }
    my_strcpy(result + offset, digits);
}

static void get_final_result_precision_lt_len(dbl_as_str_t *result,
    const dbl_as_str_t *digits, int precision, size_t offset)
{
    size_t len = my_strlen(digits);
    size_t int_len = len - precision;

    my_strncpy(result + offset, digits, int_len);
    offset += int_len;
    if (precision > 0) {
        my_strcpy(result + offset, ".");
        my_strcpy(result + offset + 1, digits + int_len);
    }
}

// Put the 0s before the digits because the digits are stripped of 0s
static dbl_as_str_t *get_final_result(int sign, dbl_as_str_t *digits,
    int precision)
{
    size_t len = my_strlen(digits);
    dbl_as_str_t *result = my_calloc(len + precision + 3, sizeof(char));
    int offset = 0;

    if (!result)
        return nullptr;
    if (sign) {
        my_strcpy(result, "-");
        offset++;
    }
    if (precision >= (int) len)
        get_final_result_precision_gt_or_eq_len(result, digits, precision,
            offset);
    else
        get_final_result_precision_lt_len(result, digits, precision, offset);
    free(digits);
    return result;
}

/*
** Shift by 63 bits because the mantisa has 64 bits including an integer one
** and apply the exponent using - 16383 - 63 to convert to signed number and
** do not reappy the 2^63 already applied when using my_getstr
*/
dbl_as_str_t *my_getdbl_as_str(long double nb, int precision,
    dbl_as_str_info_t *infos)
{
    union double_representation nb_repr = {.nb = nb};
    int exponent = nb_repr.bits.exponent;
    unsigned long mantisa = nb_repr.bits.mantisa;
    dbl_as_str_t *digits = my_getstr((mantisa | ((unsigned long) 1 << 63)));
    dbl_as_str_t *tmp = nullptr;

    if (is_special_case(nb_repr))
        return handle_special_case(digits, nb_repr, precision, infos);
    tmp = my_str_pow10(digits, precision + 1);
    free(digits);
    digits = tmp;
    digits = apply_exponent(digits, exponent - 16383 - 63);
    my_str_round(digits);
    digits = get_final_result(nb_repr.bits.sign, digits, precision);
    if (infos->is_scientific)
        digits = my_dblstr_to_scientific(digits, infos->is_capital, precision);
    return digits;
}
