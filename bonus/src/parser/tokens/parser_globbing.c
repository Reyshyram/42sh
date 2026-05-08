/*
** EPITECH PROJECT, 2026
** parser_globbing.c
** File description:
** Add globbing for parser
*/

#include <glob.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

static bool append_cmd_arg(char ***argv, size_t *argc, char *value)
{
    char **new_argv = realloc(*argv, sizeof(char *) * (*argc + 2));

    if (!new_argv)
        return false;
    *argv = new_argv;
    (*argv)[*argc] = strdup(value);
    if (!(*argv)[*argc])
        return false;
    (*argv)[*argc + 1] = nullptr;
    (*argc)++;
    return true;
}

static bool add_glob_paths(char ***argv, size_t *argc, glob_t *paths)
{
    for (size_t i = 0; i < paths->gl_pathc; i++)
        if (!append_cmd_arg(argv, argc, paths->gl_pathv[i]))
            return false;
    return true;
}

static bool get_glob_paths(char *glob_pattern, glob_t *paths, parser_t *ps)
{
    int glob_status = 0;

    glob_status = glob(glob_pattern, 0, nullptr, paths);
    if (glob_status == GLOB_NOMATCH) {
        parser_set_error(ps, "No match.");
        ps->error_message_prefix = strdup(glob_pattern);
        return false;
    }
    if (glob_status != 0) {
        parser_set_error(ps, "Error while globbing.");
        return false;
    }
    return true;
}

bool parser_glob(parser_t *ps, char ***argv, size_t *argc)
{
    glob_t paths = {0};

    if (strcspn(ps->current_token->value, "*?[]")
        == strlen(ps->current_token->value))
        return append_cmd_arg(argv, argc, ps->current_token->value);
    if (!get_glob_paths(ps->current_token->value, &paths, ps))
        return false;
    if (!add_glob_paths(argv, argc, &paths)) {
        globfree(&paths);
        return false;
    }
    globfree(&paths);
    return true;
}
