/*
** EPITECH PROJECT, 2026
** expand_alias.c
** File description:
** Expand an alias before executing a command
*/

#include <stdlib.h>
#include <string.h>

#include "my/misc.h"

#include "executer.h"
#include "shell.h"

static bool append_word(char ***words, size_t *count, char *token)
{
    char **tmp = realloc(*words, sizeof(char *) * (*count + 1));

    if (!tmp)
        return false;
    *words = tmp;
    (*words)[*count] = strdup(token);
    if (!(*words)[*count])
        return false;
    (*count)++;
    return true;
}

static char **alias_split_value(const char *value, size_t *out_count)
{
    char *copy = strdup(value);
    char **words = nullptr;
    char *token = nullptr;

    if (!copy)
        return nullptr;
    token = strtok(copy, " \t");
    while (token) {
        if (!append_word(&words, out_count, token)) {
            free(copy);
            my_free_word_array(words);
            return nullptr;
        }
        token = strtok(nullptr, " \t");
    }
    free(copy);
    return words;
}

static bool fill_alias_words(char **result, char **alias_words, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        result[i] = strdup(alias_words[i]);
        if (!result[i])
            return false;
    }
    return true;
}

static bool fill_extra_args(char **result, char **original_argv,
    size_t alias_count, size_t extra)
{
    for (size_t i = 0; i < extra; i++) {
        result[alias_count + i] = strdup(original_argv[1 + i]);
        if (!result[alias_count + i])
            return false;
    }
    return true;
}

static char **build_expanded_argv(char **alias_words, size_t alias_word_count,
    ast_cmd_t *cmd, size_t *new_argc)
{
    size_t extra = cmd->argc > 0 ? cmd->argc - 1 : 0;
    size_t total = alias_word_count + extra;
    char **result = malloc(sizeof(char *) * (total + 1));

    if (!result)
        return nullptr;
    if (!fill_alias_words(result, alias_words, alias_word_count)
        || !fill_extra_args(result, cmd->argv, alias_word_count, extra)) {
        my_free_word_array(result);
        return nullptr;
    }
    result[total] = nullptr;
    *new_argc = total;
    return result;
}

static bool apply_expansion(ast_cmd_t *cmd, char **alias_words,
    size_t alias_word_count)
{
    char **new_argv = nullptr;
    size_t new_argc = 0;

    new_argv = build_expanded_argv(alias_words, alias_word_count,
        cmd, &new_argc);
    if (!new_argv)
        return false;
    my_free_word_array(cmd->argv);
    cmd->argv = new_argv;
    cmd->argc = new_argc;
    return true;
}

static char **get_alias_words(shell_t *shell, char *name,
    size_t *alias_word_count)
{
    variable_t *alias = get_variable(shell->aliases, name);
    char **words = nullptr;

    if (!alias)
        return nullptr;
    words = alias_split_value(alias->value, alias_word_count);
    if (!words || *alias_word_count == 0) {
        my_free_word_array(words);
        return nullptr;
    }
    return words;
}

bool expand_alias(shell_t *shell, ast_node_t *ast)
{
    char **alias_words = nullptr;
    size_t alias_word_count = 0;
    bool result = false;

    if (!shell->aliases)
        return false;
    alias_words = get_alias_words(shell, ast->data.cmd.argv[0],
        &alias_word_count);
    if (!alias_words)
        return false;
    result = apply_expansion(&ast->data.cmd, alias_words, alias_word_count);
    my_free_word_array(alias_words);
    return result;
}
