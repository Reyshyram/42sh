/*
** EPITECH PROJECT, 2025
** my_add_to_list_end.c
** File description:
** Add element to the end of a linked list
*/

#include <stdlib.h>

#include "my/list.h"

bool my_add_to_list_end(linked_list_t **head, void *data)
{
    linked_list_t *node = malloc(sizeof(*node));
    linked_list_t *current = nullptr;

    if (!node)
        return false;
    node->data = data;
    node->next = nullptr;
    if (!*head) {
        *head = node;
        return true;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = node;
    return true;
}
