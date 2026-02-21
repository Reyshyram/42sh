/*
** EPITECH PROJECT, 2026
** execute_cmd.c
** File description:
** Execute a command
*/

#include <stddef.h>

#include "my/misc.h"
#include "my/strings.h"

#include "ast.h"
#include "builtins.h"
#include "shell.h"

int execute_cmd(shell_t *shell, ast_node_t *ast)
{
    for (size_t i = 0; BUILTINS[i].name; i++)
        if (!my_strcmp(ast->data.cmd.argv[0], BUILTINS[i].name))
            return BUILTINS[i].func(shell, ast->data.cmd.argc,
                ast->data.cmd.argv);
    return SUCCESS;
}
