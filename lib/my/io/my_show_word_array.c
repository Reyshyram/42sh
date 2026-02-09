/*
** EPITECH PROJECT, 2025
** my_show_word_array
** File description:
** Print an array of strings
*/

#include <stddef.h>

#include "my/io.h"
#include "my/misc.h"

int my_show_word_array(char *const *tab)
{
    for (size_t i = 0; tab[i]; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return SUCCESS;
}
