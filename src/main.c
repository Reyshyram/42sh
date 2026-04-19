/*
** EPITECH PROJECT, 2025
** main
** File description:
** Main file for the program
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "my/misc.h"

#include "shell.h"

static bool open_file(char *filepath)
{
    FILE *script_file = freopen(filepath, "r", stdin);

    if (!script_file) {
        fprintf(stderr, "%s: %s\n", filepath, strerror(errno));
        return false;
    }
    return true;
}

int main(int ac, char **av, char **env)
{
    if (ac > 2) {
        fprintf(stderr, "Usage: %s [script]\n", av[0]);
        return ERROR;
    }
    if (ac == 2) {
        if (!strcmp(av[1], "-h") || !strcmp(av[1], "--help")) {
            printf("Usage: %s [script]\n", av[0]);
            return SUCCESS;
        }
        return open_file(av[1]) ? shell_run(env) : ERROR;
    }
    return shell_run(env);
}
