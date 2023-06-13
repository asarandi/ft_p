/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:04:37 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:05:01 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int count_char_array(char **array) {
    int i;

    i = 0;
    if (array == NULL)
        return (0);
    while (array[i] != NULL)
        i++;
    return (i);
}

void destroy_char_array(char **array) {
    int count;
    int i;

    if (array != NULL) {
        count = count_char_array(array);
        i = 0;
        while (i < count) {
            free(array[i]);
            i++;
        }
        free(array);
    }
    return;
}

char *word(char *str, int index) {
    int i;
    int word;

    if (str == NULL)
        return (NULL);
    i = 0;
    word = 0;
    while (str[i]) {
        while ((str[i]) && (isspace(str[i])))
            i++;
        if ((str[i]) && (word == index))
            return (&str[i]);
        if (str[i] == 0)
            return (NULL);
        word++;
        while ((str[i]) && (!isspace(str[i])))
            i++;
    }
    return (NULL);
}

char **request_split(char *str) {
    int i;

    i = strlen(str);
    if ((i >= 2) && (str[i - 1] == '\n') && (str[i - 2] == '\r')) {
        str[i - 1] = 0;
        str[i - 2] = 0;
    } else if ((i >= 1) && (str[i - 1] == '\n')) {
        str[i - 1] = 0;
    }
    return (str_split(str, ' '));
}

int count_words(char *s, int delim) {
    int n;

    n = 0;
    while (*s) {
        while ((*s) && (*s == delim))
            s++;
        n += (int)(*s != 0);
        while ((*s) && (*s != delim))
            s++;
    }
    return n;
}

char **str_split(char *s, int delim) {
    char **arr, *p;
    int i;

    i = count_words(s, delim);
    if (!(arr = calloc(1, (1 + i) * sizeof(char *))))
        return NULL;
    i = 0;
    while (*s) {
        while ((*s) && (*s == delim))
            s++;
        p = s;
        while ((*s) && (*s != delim))
            s++;
        if (!(s - p))
            break;
        arr[i] = calloc(1, 1 + (s - p));
        memcpy(arr[i++], p, s - p);
    }
    return arr;
}
