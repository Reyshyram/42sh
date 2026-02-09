/*
** EPITECH PROJECT, 2025
** my/printf/types.h
** File description:
** Data types for my_printf
*/

#ifndef MY_PRINTF_TYPES_H
// clang-format off
    #define MY_PRINTF_TYPES_H

    #include <stdarg.h>
    #include <stddef.h>

    #define PRINTF_BUFFER_SIZE 512
// clang-format on

typedef struct printf_buffer_s {
    char *buffer;
    int fd;
    int max_size;
    int pos;
    size_t length;
} printf_buffer_t;

enum conversion_types {
    CHAR,
    SHORT,
    INT,
    LONG,
    LONG_DOUBLE,
    INTMAX_T,
    SIZE_T,
    PTRDIFF_T,
    NONE,
};

typedef struct specifier_info {
    bool is_alternate_form;
    bool is_padding_on_left;
    bool is_unsigned;
    bool is_capital;
    char leading_char;
    char padding_char;
    int field_width;
    int precision;
    enum conversion_types conversion_type;
} specifier_info_t;

struct flag_character {
    char flag;
    void (*func)(specifier_info_t *);
};

struct length_modifier {
    char *flag;
    void (*func)(specifier_info_t *);
};

struct conversion_specifier {
    char flag;
    void (*func)(printf_buffer_t *, specifier_info_t *, va_list);
};

#endif /* !MY_PRINTF_TYPES_H */
