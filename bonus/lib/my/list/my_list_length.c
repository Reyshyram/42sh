/*
** EPITECH PROJECT, 2026
** my_list_length
** File description:
** Returns the length of a linked list
*/

#include <stddef.h>

#include "my/list.h"

size_t my_list_length(linked_list_t *head)
{
    size_t i = 0;
    linked_list_t *node = head;

    if (!head)
        return 0;
    while (node) {
        node = node->next;
        i++;
    }
    return i;
}
