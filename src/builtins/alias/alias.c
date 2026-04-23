/*
** EPITECH PROJECT, 2026
** alias.c
** File description:
** alias builtin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "my/list.h"
#include "my/misc.h"
#include "shell.h"

static void print_all_aliases(shell_t *shell)
{
    variable_t *alias = nullptr;

    for (linked_list_t *node = shell->aliases; node; node = node->next) {
        alias = node->data;
        printf("alias %s\t(%s)\n", alias->key, alias->value);
    }
}

static int print_one_alias(shell_t *shell, char *name)
{
    variable_t *alias = get_variable(shell->aliases, name);

    if (!alias) {
        fprintf(stderr, "alias: %s: Not found.\n", name);
        return ERROR;
    }
    printf("alias %s\t(%s)\n", alias->key, alias->value);
    return SUCCESS;
}

static int set_alias(shell_t *shell, char *name, char *value)
{
    if (!set_variable(&shell->aliases, name, value)) {
        fprintf(stderr, "alias: Couldn't allocate memory.\n");
        return ERROR;
    }
    return SUCCESS;
}

int builtin_alias(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_all_aliases(shell);
        return SUCCESS;
    }
    if (argc == 2)
        return print_one_alias(shell, argv[1]);
    return set_alias(shell, argv[1], argv[2]);
}
