/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:28:39 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 08:30:26 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int client_read_flag_util(t_ftp *f, int *i, int *flag) {
    if ((*i < 3) && (isdigit(f->buf[*i])))
        (*flag)++;
    if ((*i == 3) && (*flag == 3)) {
        if (isspace(f->buf[*i]))
            (*flag)++;
        else
            (*flag) = 0;
    }
    if (f->buf[*i] == '\n') {
        if (*flag == 4)
            (*flag)++;
        else {
            (*flag) = 0;
            (*i) = -1;
            (void)memset(f->buf, 0, sizeof(f->buf));
        }
    }
    return (1);
}

int client_read_from_server(t_ftp *f) {
    int flag;
    int i;

    (void)printf(COLOR_CYAN "[%s:%d]: " END_OF_COLOR, f->print_addr,
                 f->print_port);
    flag = 0;
    i = 0;
    (void)memset(f->buf, 0, sizeof(f->buf));
    while (flag != 5) {
        if (recv(f->socket, &f->buf[i], 1, 0) <= 0)
            return (0);
        write(STDOUT_FILENO, &f->buf[i], 1);
        (void)client_read_flag_util(f, &i, &flag);
        i++;
    }
    f->response_code = atoi(word(f->buf, 0));
    return (1);
}

int client_free_read_buffer(t_ftp *f, int retval) {
    if (f->input != NULL)
        free(f->input);
    f->input = NULL;
    return (retval);
}

int client_read_from_user(t_ftp *f) {
    ssize_t num_read;
    size_t len;
    int retval;

    while (f->running == 1) {
        (void)printf(COLOR_MAGENTA "%s " END_OF_COLOR, CLIENT_PROMPT);

        if ((num_read = getline(&f->input, &len, stdin)) == -1)
            break;

        while ((num_read > 0) && (f->input[num_read - 1] == '\n'))
            f->input[--num_read] = '\0';

        if (num_read == 0) {
            free(f->input);
            f->input = NULL;
            continue;
        }

        retval = client_execute_command(f) != 0;
        break;
    }

    return (client_free_read_buffer(f, retval));
}
