/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:29:58 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:32:13 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

int str_char_count(char *str, char c) {
    int i;
    int count;

    if (!str)
        return (0);
    i = 0;
    count = 0;
    while (str[i]) {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

int str_char_replace(char *str, char a, char b) {
    int i;

    if (!str)
        return (0);
    i = 0;
    while (str[i]) {
        if (str[i] == a)
            str[i] = b;
        i++;
    }
    return (1);
}

char *str_char_index(char *str, char c, int index) {
    int i;
    int k;

    if (!str)
        return (NULL);
    i = 0;
    k = 0;
    while (str[i]) {
        if (str[i] == c) {
            if (k == index)
                return (&str[i]);
            k++;
        }
        i++;
    }
    return (NULL);
}

char *str_join(char *s1, char *s2) {
    size_t n1, n2;
    char *buf;

    n1 = strlen(s1);
    n2 = strlen(s2);

    buf = malloc(n1 + n2 + 1);
    if (!buf)
        return NULL;

    memcpy(buf, s1, n1);
    memcpy(buf + n1, s2, n2);

    buf[n1 + n2] = '\0';
    return buf;
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
