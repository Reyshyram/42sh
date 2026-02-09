/*
** EPITECH PROJECT, 2025
** my_printf_handle_flags
** File description:
** Handle the flags for my_printf
*/

#include <stdarg.h>
#include <stddef.h>

#include "my/numbers.h"
#include "my/printf/flags.h"
#include "my/printf/io.h"
#include "my/printf/types.h"
#include "my/strings.h"

static const char *handle_flag_characters(const char *format,
    specifier_info_t *specifier_info)
{
    specifier_info->is_alternate_form = false;
    specifier_info->is_padding_on_left = true;
    specifier_info->leading_char = '\0';
    specifier_info->padding_char = ' ';
    for (int i = 0; FLAG_CHARACTERS[i].flag; i++) {
        if (FLAG_CHARACTERS[i].flag == *format) {
            FLAG_CHARACTERS[i].func(specifier_info);
            i = -1;
            format++;
        }
    }
    return format;
}

static const char *handle_field_width(const char *format,
    specifier_info_t *specifier_info, va_list args)
{
    specifier_info->field_width = 0;
    if (!my_isnumber(*format) && *format != '*')
        return format;
    if (*format == '*') {
        specifier_info->field_width = va_arg(args, int);
        format++;
    } else {
        specifier_info->field_width = (int) my_getnbr(format);
        while (my_isnumber(*format))
            format++;
    }
    return format;
}

static const char *handle_precision(const char *format,
    specifier_info_t *specifier_info, va_list args)
{
    specifier_info->precision = -1;
    if (*format != '.')
        return format;
    format++;
    specifier_info->padding_char = ' ';
    if (!my_isnumber(*format) && *format != '*' && *format != '-') {
        specifier_info->precision = 0;
        return format;
    }
    if (*format == '*') {
        specifier_info->precision = va_arg(args, int);
        format++;
    } else {
        specifier_info->precision = (int) my_getnbr(format);
        while (my_isnumber(*format))
            format++;
    }
    return format;
}

static const char *handle_length_modifiers(const char *format,
    specifier_info_t *specifier_info)
{
    size_t flag_len = 0;

    specifier_info->conversion_type = NONE;
    for (int i = 0; LENGTH_MODIFIERS[i].flag; i++) {
        flag_len = my_strlen(LENGTH_MODIFIERS[i].flag);
        if (my_strncmp(LENGTH_MODIFIERS[i].flag, format, flag_len) == 0) {
            LENGTH_MODIFIERS[i].func(specifier_info);
            format += flag_len;
            break;
        }
    }
    return format;
}

static int handle_conversion_specifier(printf_buffer_t *buffer,
    const char *const format, specifier_info_t *specifier_info, va_list args)
{
    specifier_info->is_unsigned = false;
    specifier_info->is_capital = false;
    for (int i = 0; CONVERSION_SPECIFIERS[i].flag; i++) {
        if (CONVERSION_SPECIFIERS[i].flag == *format) {
            CONVERSION_SPECIFIERS[i].func(buffer, specifier_info, args);
            return true;
        }
    }
    return false;
}

const char *my_printf_handle_flags(printf_buffer_t *buffer, const char *format,
    va_list args)
{
    const char *const start_when_no_specifier = format;
    const char *end_when_no_specifier = nullptr;
    specifier_info_t specifier_info;

    format = handle_flag_characters(format, &specifier_info);
    format = handle_field_width(format, &specifier_info, args);
    format = handle_precision(format, &specifier_info, args);
    end_when_no_specifier = (char *) format;
    format = handle_length_modifiers(format, &specifier_info);
    if (!handle_conversion_specifier(buffer, format, &specifier_info, args)) {
        my_printf_putchar(buffer, '%');
        my_printf_putnstr(buffer, start_when_no_specifier,
            end_when_no_specifier - start_when_no_specifier);
        my_printf_putchar(buffer, *format);
    }
    return format;
}
