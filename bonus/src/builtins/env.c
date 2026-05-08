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

// Print in reverse because the order in which the variables are stored
// is inversed for performance reasons.
static void print_in_reverse(linked_list_t *node)
{
    if (!node)
        return;
    print_in_reverse(node->next);
    printf("%s=%s\n", ((variable_t *) node->data)->key,
        ((variable_t *) node->data)->value);
}

int builtin_env(shell_t *shell, size_t argc, [[maybe_unused]] char **argv)
{
    if (argc != 1) {
        fprintf(stderr, "env: Too many arguments.\n");
        return ERROR;
    }
    print_in_reverse(shell->env);
    return SUCCESS;
}
