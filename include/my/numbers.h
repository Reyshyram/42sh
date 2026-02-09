/*
** EPITECH PROJECT, 2025
** my/numbers.h
** File description:
** Functions related to numbers
*/

#ifndef MY_NUMBERS_H
// clang-format off
    #define MY_NUMBERS_H

    #include <stddef.h>
    #include <stdint.h>

    #define BASE_2 "01"
    #define BASE_8 "01234567"
    #define BASE_10 "0123456789"
    #define BASE_16 "0123456789abcdef"
    #define BASE_16_CAP "0123456789ABCDEF"
    #define ABS(value) (((value) < 0) ? -(value) : (value))
    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
    #define MAX(a, b) (((a) > (b)) ? (a) : (b))
// clang-format on

union double_representation {
    long double nb;
    struct {
        uint64_t mantisa : 64;
        uint32_t exponent : 15;
        uint32_t sign : 1;
    } bits;
};

int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_find_prime_sup(int nb);
bool my_isprime(int nb);

__int128_t my_getnbr(const char *str);
size_t my_getnbr_length(__int128_t nb);
size_t my_getnbr_length_base(__int128_t nb, size_t divisor);
__int128_t my_getnbr_base(const char *str, const char *base);
float my_getflt(const char *str);

typedef char dbl_as_str_t;

typedef struct {
    int dot;
    int first_nonzero;
} digit_info_t;

typedef struct {
    bool is_capital;
    bool is_scientific;
} dbl_as_str_info_t;

dbl_as_str_t *my_getdbl_as_str(long double nb, int precision,
    dbl_as_str_info_t *infos);
dbl_as_str_t *my_dblstr_to_scientific(dbl_as_str_t *str, bool is_capital,
    int precision);
dbl_as_str_t *my_str_multiply_2(const dbl_as_str_t *num);
dbl_as_str_t *my_str_divide_2(const dbl_as_str_t *num);
dbl_as_str_t *my_str_pow10(const dbl_as_str_t *num, size_t n);
dbl_as_str_t *my_str_round(dbl_as_str_t *digits);

#endif /* MY_NUMBERS_H */
