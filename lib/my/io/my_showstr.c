/*
** EPITECH PROJECT, 2025
** my_showstr
** File description:
** Print a string with non-printable characters converted in hexa
*/

#include "my/io.h"
#include "my/misc.h"
#include "my/numbers.h"
#include "my/strings.h"

int my_showstr(const char *str)
{
    while (*str) {
        if (my_isprintable(*str))
            my_putchar(*str);
        else {
            my_putchar('\\');
            my_putnbr_base(*str / 16, BASE_16);
            my_putnbr_base(*str % 16, BASE_16);
        }
        str++;
    }
    return SUCCESS;
}
