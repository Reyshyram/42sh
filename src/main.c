/*
** EPITECH PROJECT, 2025
** main
** File description:
** Main file for the program
*/

#include <stdio.h>

#include "my/misc.h"

#include "shell.h"

int main(int ac, char **av, char **env)
{
    (void) av;
    if (ac != 1) {
        fprintf(stderr,
            "Too many options. The shell doesn't accept arguments.\n");
        return ERROR;
    }
    return shell_run(env);
}
