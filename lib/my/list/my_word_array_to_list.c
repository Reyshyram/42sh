/*
** EPITECH PROJECT, 2026
** my_word_array_to_list.c
** File description:
** Transform a word array into a linked list
*/

#include <stdlib.h>

#include "my/list.h"
#include "my/strings.h"

linked_list_t *my_word_array_to_list(char **array)
{
    linked_list_t *head = nullptr;
    char *temp = nullptr;

    for (size_t i = 0; array[i]; i++) {
        temp = my_strdup(array[i]);
        if (!temp) {
            my_free_list(head, free);
            return nullptr;
        }
        if (!my_add_to_list(&head, temp)) {
            my_free_list(head, free);
            return nullptr;
        }
    }
    return head;
}
