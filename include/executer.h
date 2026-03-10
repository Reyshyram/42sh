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
int execute_pipe(shell_t *shell, ast_node_t *ast);
int execute_subshell(shell_t *shell, ast_node_t *ast);

int wait_for_subprocess(pid_t pid);

#endif /* EXECUTER_H */
