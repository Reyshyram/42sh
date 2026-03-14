/*
** EPITECH PROJECT, 2026
** lexer_is_word_separator.c
** File description:
** Whether the current char is a separator
*/

bool lexer_is_word_separator(char c)
{
    if (!c || c == ' ' || c == '\t' || c == '\n')
        return true;
    if (c == '(' || c == ')' || c == ';' || c == '&' || c == '|' || c == '<'
        || c == '>')
        return true;
    return false;
}
