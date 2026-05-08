/*
** EPITECH PROJECT, 2025
** my_add_to_list.c
** File description:
** Add element to a linked list
*/

#include <stdlib.h>

#include "my/list.h"

bool my_add_to_list(linked_list_t **head, void *data)
{
    linked_list_t *node = malloc(sizeof(*node));

    if (!node)
        return false;
    node->data = data;
    node->next = *head;
    *head = node;
    return true;
}
