/*
** EPITECH PROJECT, 2025
** my_puterr
** File description:
** Print a string in error output
*/

#include "my/misc.h"
#include "my/strings.h"
#include <unistd.h>

int my_puterr(const char *str)
{
    write(2, str, my_strlen(str));
    return SUCCESS;
}
