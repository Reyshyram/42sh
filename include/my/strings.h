/*
** EPITECH PROJECT, 2025
** my/strings.h
** File description:
** Functions related to strings
*/

#ifndef MY_STRINGS_H
// clang-format off
    #define MY_STRINGS_H

    #include <stddef.h>
// clang-format on

size_t my_strlen(const char *str);

int my_getindex(char c, const char *str);
char *my_getstr(__int128_t nb);
char *my_getstr_base(__int128_t nb, const char *base);

bool my_isupper(char c);
bool my_islower(char c);
bool my_isnumber(char c);
bool my_isprintable(char c);

bool my_str_isalpha(const char *str);
bool my_str_islower(const char *str);
bool my_str_isnum(const char *str);
bool my_str_isprintable(const char *str);
bool my_str_isupper(const char *str);

char *my_strcapitalize(char *str);
char *my_strlowcase(char *str);
char *my_strupcase(char *str);
char *my_revstr(char *str);

char *my_strdup(const char *src);
char *my_strndup(const char *src, size_t nb_chars);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, size_t n);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, size_t nb);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, size_t n);
int my_strcasecmp(const char *s1, const char *s2);
int my_strncasecmp(const char *s1, const char *s2, size_t n);
char *my_strstr(char *str, const char *to_find);
bool my_is_char_in_str(const char *str, char c);

char *my_strtok_r(char *str, const char *delim, char **saveptr);
char **my_str_to_word_array(char *str, const char *delims);

#endif /* MY_STRINGS_H */
