/*
** EPITECH PROJECT, 2025
** my_delete_node.c
** File description:
** Delete a node in the linked list
*/

#include <stdlib.h>

#include "my/list.h"

linked_list_t *my_delete_node(linked_list_t **head, linked_list_t *to_delete,
    linked_list_t *prev, void (*free_data)(void *))
{
    linked_list_t *next = to_delete->next;

    if (!prev)
        *head = next;
    else
        prev->next = next;
    free_data(to_delete->data);
    free(to_delete);
    return next;
}
