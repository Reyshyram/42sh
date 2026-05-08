/*
** EPITECH PROJECT, 2026
** if.c
** File description:
** if builtin
*/

#include <stdio.h>
#include <string.h>

#include "my/misc.h"

#include "ast.h"
#include "executer.h"
#include "shell.h"

/*************************************
* The if_error function verifies if there are errors for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> const char *msg, a string of the error message
*   @return -> an integer, an error or a success
*************************************/
static int if_error(const char *msg)
{
    fprintf(stderr, "if: %s\n", msg);
    return ERROR;
}

/*************************************
* The is_comparison_valid function checks the comparisons for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *cmp, a string of the comparison
*   @return -> a boolean, either true or false
*************************************/
static bool is_comparison_valid(char *cmp)
{
    return !strcmp(cmp, "==") || !strcmp(cmp, "!=");
}

/*************************************
* The execute_if_condition function executes the if for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the args
*   @return -> an integer, an error or a success
*************************************/
static int execute_if_condition(shell_t *shell, size_t argc, char **argv)
{
    bool is_correct = strcmp(argv[1], argv[3]) == 0;
    ast_node_t cmd_ast = {0};

    if (!strcmp(argv[2], "!="))
        is_correct = !is_correct;
    if (!is_correct)
        return SUCCESS;
    cmd_ast.type = AST_CMD;
    cmd_ast.data.cmd.argv = argv + 4;
    cmd_ast.data.cmd.argc = argc - 4;
    return execute_cmd(shell, &cmd_ast);
}

/*************************************
* The builtin_if function handles the builtin if for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the args
*   @return -> an integer, an error or a success
*************************************/
int builtin_if(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1)
        return if_error("Too few arguments.");
    if (argc < 4 || !is_comparison_valid(argv[2]))
        return if_error("Expression Syntax.");
    if (argc == 4)
        return if_error("Empty if.");
    return execute_if_condition(shell, argc, argv);
}
