/*
** EPITECH PROJECT, 2025
** my_compute_square_root
** File description:
** Compute a whole square root
*/

#include "my/misc.h"

int my_compute_square_root(int nb)
{
    for (int result = 0; result * result <= nb; result++)
        if (result * result == nb)
            return result;
    return SUCCESS;
}
