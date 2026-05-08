/*
** EPITECH PROJECT, 2025
** my_is_char_in_str
** File description:
** Check whether a char is present in the given string or not
*/

bool my_is_char_in_str(const char *str, char c)
{
    while (*str) {
        if (c == *str)
            return true;
        str++;
    }
    return false;
}
