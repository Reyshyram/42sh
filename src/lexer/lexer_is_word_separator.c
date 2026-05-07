/*
** EPITECH PROJECT, 2026
** lexer_is_word_separator.c
** File description:
** Whether the current char is a separator
*/

/*************************************
* The lexer_is_word_separator function verifies if character
* is a word separator in the lexer for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char c, a character given
*   @return -> a boolean, either true or false
*************************************/
bool lexer_is_word_separator(char c)
{
    if (!c || c == ' ' || c == '\t' || c == '\n')
        return true;
    if (c == '(' || c == ')' || c == ';' || c == '&' || c == '|' || c == '<'
        || c == '>')
        return true;
    return false;
}
