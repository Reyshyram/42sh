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
#include "my/strings.h"
#include "shell.h"

static void print_all_aliases(shell_t *shell)
{
    variable_t *alias = nullptr;

    for (linked_list_t *node = shell->aliases; node; node = node->next) {
        alias = node->data;
        printf("%s\t%s\n", alias->key, alias->value);
    }
}

static int print_one_alias(shell_t *shell, char *name)
{
    variable_t *alias = get_variable(shell->aliases, name);

    if (!alias)
        return SUCCESS;
    printf("%s\t%s\n", alias->key, alias->value);
    return SUCCESS;
}

static char *join_args(size_t argc, char **argv)
{
    char *value = nullptr;
    size_t size = 0;

    for (size_t i = 2; i < argc; i++) {
        if (i > 2)
            value = append_to_buffer(value, &size, " ", 1);
        value = append_to_buffer(value, &size, argv[i], strlen(argv[i]));
        if (!value)
            return nullptr;
    }
    return value;
}

static int set_alias(shell_t *shell, size_t argc, char **argv)
{
    char *value = join_args(argc, argv);
    int status = SUCCESS;

    if (!value) {
        fprintf(stderr, "alias: Couldn't allocate memory.\n");
        return ERROR;
    }
    if (!set_variable(&shell->aliases, argv[1], value)) {
        fprintf(stderr, "alias: Couldn't allocate memory.\n");
        status = ERROR;
    }
    free(value);
    return status;
}

int builtin_alias(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_all_aliases(shell);
        return SUCCESS;
    }
    if (argc == 2)
        return print_one_alias(shell, argv[1]);
    return set_alias(shell, argc, argv);
}
