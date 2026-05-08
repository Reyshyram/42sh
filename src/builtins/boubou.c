/*
** EPITECH PROJECT, 2026
** boubou.c
** File description:
** The boubou builtin, which shows you the answer to the universe
*/

#include <stdio.h>

#include "shell.h"

/*************************************
* The builtin_boubou function prints a pretty pokemon for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the arg
*   @return -> an integer, an error or a success
*************************************/
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
