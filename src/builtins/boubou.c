/*
** EPITECH PROJECT, 2026
** boubou.c
** File description:
** The boubou builtin, which shows you the answer to the universe
*/

#include <stdio.h>

#include "shell.h"

int builtin_boubou([[maybe_unused]] shell_t *shell, size_t argc,
    [[maybe_unused]] char **argv)
{
    char boubou_buffer[] = {
#embed "../../assets/boubou.txt"
    };

    if (argc != 1)
        return 1;
    printf("%s", boubou_buffer);
    return 0;
}
