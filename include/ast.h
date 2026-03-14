/*
** EPITECH PROJECT, 2025
** ast.h
** File description:
** Abstract syntax tree for the shell
*/

#ifndef AST_H
// clang-format off
    #define AST_H

    #include <stddef.h>
// clang-format on

typedef enum {
    AST_CMD,
    AST_SEQUENCE,
    AST_LOGICAL_AND,
    AST_LOGICAL_OR,
    AST_SUBSHELL,
    AST_PIPE,
    AST_REDIRECT,
} ast_type_t;

typedef struct ast_node ast_node_t;

typedef struct {
    char **argv;
    size_t argc;
} ast_cmd_t;

typedef struct {
    ast_node_t *left;
    ast_node_t *right;
} ast_binary_t;

typedef struct {
    ast_node_t *node;
} ast_subshell_t;

typedef struct {
    ast_node_t *node;
    char *file;
    int fd;
    bool append;
} ast_redirect_t;

struct ast_node {
    ast_type_t type;
    union {
        ast_cmd_t cmd;
        ast_binary_t binary;
        ast_subshell_t subshell;
        ast_redirect_t redirect;
    } data;
};

void ast_destroy(ast_node_t *ast);

ast_node_t *ast_new_cmd(char **argv, size_t argc);
ast_node_t *ast_new_binary(ast_type_t type, ast_node_t *left,
    ast_node_t *right);
ast_node_t *ast_new_subshell(ast_node_t *subshell);
ast_node_t *ast_new_redirect(ast_node_t *node, char *file, int fd,
    bool append);

#endif /* AST_H */
