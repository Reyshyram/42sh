/*
** EPITECH PROJECT, 2026
** env.c
** File description:
** Env builtin
*/

#include <stdio.h>

#include "my/list.h"
#include "my/misc.h"

#include "shell.h"

/*************************************
* The print_in_reverse function prints in reverse for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
* (Print in reverse because the order in which the variables
* are stored is inversed for performance reasons)
*
*   @param -> linked_list_t *node, a struct found in include/my/list.h
*************************************/
static void print_in_reverse(linked_list_t *node)
{
    if (!node)
        return;
    print_in_reverse(node->next);
    printf("%s=%s\n", ((variable_t *) node->data)->key,
        ((variable_t *) node->data)->value);
}

/*************************************
* The builtin_env function handles env builtin for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the args
*   @return -> an integer, an error or a success
*************************************/
int builtin_env(shell_t *shell, size_t argc, [[maybe_unused]] char **argv)
{
    if (argc != 1) {
        fprintf(stderr, "env: Too many arguments.\n");
        return ERROR;
    }
    print_in_reverse(shell->env);
    return SUCCESS;
}
