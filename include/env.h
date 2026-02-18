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
// clang-format on

char *env_get_value(linked_list_t *env, char *key);

#endif /* ENV_H */
