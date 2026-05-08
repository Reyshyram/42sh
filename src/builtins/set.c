/*
** EPITECH PROJECT, 2026
** set.c
** File description:
** set builtin
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "my/list.h"
#include "my/misc.h"
#include "my/strings.h"

#include "builtins.h"
#include "shell.h"

/*************************************
* The compare_variable function compares the variables for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> variable_t *a, the first variable
*   @param -> variable_t *b, the second variable
*   @return -> an integer, the result
*************************************/
static int compare_variable(variable_t *a, variable_t *b)
{
    return strcmp(a->key, b->key);
}

/*************************************
* The print_variables function prints the variables for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*************************************/
static void print_variables(shell_t *shell)
{
    variable_t *data = nullptr;

    shell->variables =
        my_sort_list(shell->variables, (void *) compare_variable);
    for (linked_list_t *node = shell->variables; node; node = node->next) {
        data = node->data;
        printf("%s\t%s\n", data->key, data->value);
    }
}

/*************************************
* The is_valid_name function verifies if the name is valid for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *str, a string of the name
*   @return -> a boolean, either true or false
*************************************/
static bool is_valid_name(char *str)
{
    if (!str || !(isupper(str[0]) || islower(str[0]) || str[0] == '_')) {
        fprintf(stderr, "set: Variable name must begin with a letter.\n");
        return false;
    }
    for (size_t i = 1; str[i]; i++) {
        if (!(isupper(str[i]) || islower(str[i]) || my_isnumber(str[i])
                || str[i] == '_')) {
            fprintf(stderr,
                "set: Variable name must contain alphanumeric "
                "characters.\n");
            return false;
        }
    }
    return true;
}

/*************************************
* The set_single_var function sets a single variable for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> char *str, a string of the variable
*   @return -> a boolean, either true or false
*************************************/
static bool set_single_var(shell_t *shell, char *str)
{
    char *key = strtok(str, "=");
    char *value = strtok(nullptr, "=");

    if (!is_valid_name(key))
        return false;
    if (!value) {
        if (!set_variable(&shell->variables, key, "")) {
            fprintf(stderr,
                "setenv: Couldn't allocate memory for variable.\n");
            return false;
        }
        return true;
    }
    if (!set_variable(&shell->variables, key, value)) {
        fprintf(stderr, "setenv: Couldn't allocate memory for variable.\n");
        return false;
    }
    return true;
}

/*************************************
* The set_single_var_spaced function sets a spaced var for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> char *key, a string of the key
*   @param -> char *value, a string of the value
*   @return -> a boolean, either true or false
*************************************/
static bool set_single_var_spaced(shell_t *shell, char *key, char *value)
{
    char *used_value = value ? value : "";

    if (!is_valid_name(key))
        return false;
    if (!set_variable(&shell->variables, key, used_value)) {
        fprintf(stderr, "setenv: Couldn't allocate memory for variable.\n");
        return false;
    }
    return true;
}

/*************************************
* The builtin_set function handles the builtin set 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the args
*   @return -> an integer, an error or a success
*************************************/
int builtin_set(shell_t *shell, size_t argc, char **argv)
{
    bool success = true;

    if (argc == 1) {
        print_variables(shell);
        return SUCCESS;
    }
    for (size_t i = 1; i < argc && success; i++) {
        if (argv[i][0] == '=') {
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
            return ERROR;
        }
        if (!strchr(argv[i], '=') && i < argc - 1
            && !strcmp(argv[i + 1], "=")) {
            success = set_single_var_spaced(shell, argv[i], argv[i + 2]);
            i += 2;
            continue;
        }
        success = set_single_var(shell, argv[i]);
    }
    return success ? SUCCESS : ERROR;
}
