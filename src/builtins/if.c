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

static int if_error(const char *msg)
{
    fprintf(stderr, "if: %s\n", msg);
    return ERROR;
}

static bool is_comparison_valid(char *cmp)
{
    return !strcmp(cmp, "==") || !strcmp(cmp, "!=");
}

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
