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

/*************************************
* The open_file function opens a file for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *filepath, a string of the filepath
*   @param -> a boolean, either true or false
*************************************/
static bool open_file(char *filepath)
{
    FILE *script_file = freopen(filepath, "r", stdin);

    if (!script_file) {
        fprintf(stderr, "%s: %s\n", filepath, strerror(errno));
        return false;
    }
    return true;
}

/*************************************
* The main function executes 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> int ac, the number of arguments
*   @param -> char **av, the array of the arguments
*   @param -> char **env, an array for the env
*   @return -> an integer, either an error or a success
*************************************/
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
