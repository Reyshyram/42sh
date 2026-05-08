/*
** EPITECH PROJECT, 2026
** alias.c
** File description:
** alias builtin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "my/list.h"
#include "my/misc.h"
#include "my/strings.h"

#include "builtins.h"
#include "shell.h"

/*************************************
* The print_all_aliases function prints all the aliases for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*************************************/
static void print_all_aliases(shell_t *shell)
{
    variable_t *alias = nullptr;

    for (linked_list_t *node = shell->aliases; node; node = node->next) {
        alias = node->data;
        printf("%s\t%s\n", alias->key, alias->value);
    }
}

/*************************************
* The print_one_aliases function prints one aliases for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> char *name, a string of the name
*   @return -> an integer, either success or an error
*************************************/
static int print_one_alias(shell_t *shell, char *name)
{
    variable_t *alias = get_variable(shell->aliases, name);

    if (!alias)
        return SUCCESS;
    printf("%s\n", alias->value);
    return SUCCESS;
}

/*************************************
* The join_args function joins the arguments for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> size_t argc, the size of the arg
*   @param -> char **argv, an array of the args
*   @return -> a string of the value
*************************************/
static char *join_args(size_t argc, char **argv)
{
    char *value = nullptr;
    size_t size = 0;

    for (size_t i = 2; i < argc; i++) {
        if (i > 2)
            value = append_to_buffer(value, &size, " ", 1);
        value =
            append_to_buffer(value, &size, argv[i], (ssize_t) strlen(argv[i]));
        if (!value)
            return nullptr;
    }
    return value;
}

/*************************************
* The set_alias function sets all the aliases for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the arg
*   @return -> an integer, an error or the status
*************************************/
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

/*************************************
* The builtin_alias function prints all the aliases for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the arg
*   @return -> an integer, an error or a success
*************************************/
int builtin_alias(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_all_aliases(shell);
        return SUCCESS;
    }
    if (argc == 2)
        return print_one_alias(shell, argv[1]);
    if (!strcmp(argv[1], "alias")) {
        fprintf(stderr, "alias: Too dangerous to alias that.\n");
        return ERROR;
    }
    return set_alias(shell, argc, argv);
}
