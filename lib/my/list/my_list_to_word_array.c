/*
** EPITECH PROJECT, 2026
** my_list_to_word_array.c
** File description:
** Transform a linked list into a word array
*/

#include <stdlib.h>
#include <sys/types.h>

#include "my/list.h"
#include "my/misc.h"
#include "my/strings.h"

char **my_list_to_word_array(linked_list_t *head)
{
    size_t length = my_list_length(head);
    char **array = malloc(sizeof(char *) * (length + 1));

    if (!array)
        return nullptr;
    for (ssize_t i = (ssize_t) length; i >= 0; i--) {
        array[i] = my_strdup(head->data);
        if (!array[i]) {
            my_free_word_array(array);
            return nullptr;
        }
        head = head->next;
    }
    return array;
}
