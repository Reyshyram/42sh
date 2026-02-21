/*
** EPITECH PROJECT, 2026
** env_to_word_array.c
** File description:
** Transform a linked list into a word array
*/

#include <stdlib.h>
#include <sys/types.h>

#include "my/io.h"
#include "my/list.h"
#include "my/misc.h"

#include "shell.h"

char **env_to_word_array(linked_list_t *head)
{
    size_t length = my_list_length(head);
    char **array = malloc(sizeof(char *) * (length + 1));
    variable_t *data = nullptr;

    if (!array)
        return nullptr;
    for (ssize_t i = (ssize_t) length - 1; i >= 0; i--) {
        data = head->data;
        my_asprintf(&array[i], "%s=%s", data->key, data->value);
        if (!array[i]) {
            my_free_word_array(array);
            return nullptr;
        }
        head = head->next;
    }
    array[length] = nullptr;
    return array;
}
