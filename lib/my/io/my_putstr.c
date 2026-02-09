/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** Print a string
*/

#include "my/misc.h"
#include "my/strings.h"
#include <unistd.h>

int my_putstr(const char *str)
{
    write(1, str, my_strlen(str));
    return SUCCESS;
}
