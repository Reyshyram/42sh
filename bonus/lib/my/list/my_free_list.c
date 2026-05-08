/*
** EPITECH PROJECT, 2025
** my_free_list.c
** File description:
** Free the entier linked list
*/

#include <stdlib.h>

#include "my/list.h"

void my_free_list(linked_list_t *head, void (*free_data)(void *))
{
    linked_list_t *to_delete = nullptr;

    while (head) {
        to_delete = head;
        head = head->next;
        if (free_data)
            free_data(to_delete->data);
        free(to_delete);
    }
}
