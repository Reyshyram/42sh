/*
** EPITECH PROJECT, 2025
** my/printf/flags.h
** File description:
** Flags for my_printf
*/

#ifndef MY_PRINTF_FLAGS_H
// clang-format off
    #define MY_PRINTF_FLAGS_H

    #include "my/printf/types.h"
// clang-format on

const char *my_printf_handle_flags(printf_buffer_t *buffer, const char *format,
    va_list args);

void my_printf_flag_sharp(specifier_info_t *specifier_info);
void my_printf_flag_zero(specifier_info_t *specifier_info);
void my_printf_flag_minus(specifier_info_t *specifier_info);
void my_printf_flag_space(specifier_info_t *specifier_info);
void my_printf_flag_plus(specifier_info_t *specifier_info);

void my_printf_flag_hh(specifier_info_t *specifier_info);
void my_printf_flag_h(specifier_info_t *specifier_info);
void my_printf_flag_ll(specifier_info_t *specifier_info);
void my_printf_flag_l(specifier_info_t *specifier_info);
void my_printf_flag_z(specifier_info_t *specifier_info);
void my_printf_flag_t(specifier_info_t *specifier_info);
void my_printf_flag_capital_l(specifier_info_t *specifier_info);
void my_printf_flag_j(specifier_info_t *specifier_info);

void my_printf_flag_d_and_i(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_u(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_o(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_x(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_capital_x(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_b(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_capital_b(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_c(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_s(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_capital_s(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_p(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_n(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_f(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_capital_f(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_e(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_capital_e(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);
void my_printf_flag_percent(printf_buffer_t *buffer,
    specifier_info_t *specifier_info, va_list args);

static const struct flag_character FLAG_CHARACTERS[] = {
    {'#', my_printf_flag_sharp},
    {'0', my_printf_flag_zero},
    {'-', my_printf_flag_minus},
    {' ', my_printf_flag_space},
    {'+', my_printf_flag_plus},
    {'\0', nullptr},
};

static const struct length_modifier LENGTH_MODIFIERS[] = {
    {"hh", my_printf_flag_hh},
    {"h", my_printf_flag_h},
    {"ll", my_printf_flag_ll},
    {"l", my_printf_flag_l},
    {"q", my_printf_flag_ll},
    {"L", my_printf_flag_capital_l},
    {"j", my_printf_flag_j},
    {"z", my_printf_flag_z},
    {"Z", my_printf_flag_z},
    {"t", my_printf_flag_t},
    {nullptr, nullptr},
};

static const struct conversion_specifier CONVERSION_SPECIFIERS[] = {
    {'d', my_printf_flag_d_and_i},
    {'i', my_printf_flag_d_and_i},
    {'u', my_printf_flag_u},
    {'o', my_printf_flag_o},
    {'x', my_printf_flag_x},
    {'X', my_printf_flag_capital_x},
    {'b', my_printf_flag_b},
    {'B', my_printf_flag_capital_b},
    {'c', my_printf_flag_c},
    {'s', my_printf_flag_s},
    {'S', my_printf_flag_capital_s},
    {'p', my_printf_flag_p},
    {'n', my_printf_flag_n},
    {'f', my_printf_flag_f},
    {'F', my_printf_flag_capital_f},
    {'e', my_printf_flag_e},
    {'E', my_printf_flag_capital_e},
    {'%', my_printf_flag_percent},
    {'\0', nullptr},
};

#endif /* MY_PRINTF_FLAGS_H */
