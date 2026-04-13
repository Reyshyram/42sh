/*
** EPITECH PROJECT, 2025
** env.h
** File description:
** Env related things
*/

#ifndef ENV_H
// clang-format off
    #define ENV_H

    #include "my/list.h"

    #define DEFAULT_PATH "/bin:/usr/bin"
// clang-format on

linked_list_t *env_to_list(char **env);
char **env_to_word_array(linked_list_t *head);

#endif /* ENV_H */
