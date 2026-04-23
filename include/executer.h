/*
** EPITECH PROJECT, 2025
** executer.h
** File description:
** Command execution
*/

#ifndef EXECUTER_H
// clang-format off
    #define EXECUTER_H

    #include "ast.h"
    #include "shell.h"

    #include <sys/types.h>
// clang-format on

int execute_ast(shell_t *shell, ast_node_t *ast);

int execute_cmd(shell_t *shell, ast_node_t *ast);
int execute_sequence(shell_t *shell, ast_node_t *ast);
int execute_logical_and(shell_t *shell, ast_node_t *ast);
int execute_logical_or(shell_t *shell, ast_node_t *ast);
int execute_repeat(shell_t *shell, ast_node_t *ast);
int execute_pipe(shell_t *shell, ast_node_t *ast);
int execute_subshell(shell_t *shell, ast_node_t *ast);
int execute_redirect(shell_t *shell, ast_node_t *ast);
char *execute_command_substitution(shell_t *shell, char *command);

int wait_for_subprocess(pid_t pid);

bool expand_alias(shell_t *shell, ast_node_t *ast);

#endif /* EXECUTER_H */
