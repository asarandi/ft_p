/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_passive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:35:32 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:55:06 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int client_parse_passive(t_ftp *f) {
    char buf[256];
    char *port;
    int p;

    if ((f->passive_ip = strrchr(f->buf, '(')) == NULL)
        return (0);
    f->passive_ip++;
    if (strchr(f->passive_ip, ')') != NULL) {
        strchr(f->passive_ip, ')')[0] = 0;
        if (str_char_count(f->passive_ip, ',') == 5) {
            str_char_replace(f->passive_ip, ',', '.');
            port = &str_char_index(f->passive_ip, '.', 3)[1];
            port[-1] = 0;
            p = atoi(port) * 256 + atoi(&strchr(port, '.')[1]);
            sprintf(buf, "%d", p);
            f->passive_port = strdup(buf);
            f->passive_ip = strdup(f->passive_ip);
            return (1);
        }
    }
    return (0);
}

int client_read_passive(t_ftp *p) {
    while (g_ftp->running == 1) {
        memset(p->buf, 0, sizeof(p->buf));
        p->buf_len = read(p->socket, p->buf, sizeof(p->buf) - 1);
        if (p->buf_len <= 0)
            break;
        write(p->passive_output_fd, p->buf, p->buf_len);
    }
    if (g_ftp->running == 0)
        printf(COLOR_RED "aborted" END_OF_COLOR "\n");
    return (1);
}

int client_init_passive(t_ftp *f) {
    if (client_parse_passive(f) != 1)
        return (0);
    f->passive = calloc(1, sizeof(struct s_ftp));
    f->passive->connect_addr = f->passive_ip;
    f->passive->connect_port = f->passive_port;
    if (socket_connect(f->passive) != 1) {
        free(f->passive);
        f->passive = NULL;
        return (0);
    }
    f->use_passive = 1;
    if (f->passive_cmd == 1)
        (void)cmd_ls_2(f);
    else if (f->passive_cmd == 2)
        (void)cmd_get_2(f);
    else if (f->passive_cmd == 3)
        (void)cmd_put_2(f);
    else
        (void)client_read_from_user(f);
    (void)client_read_from_server(f);
    return (1);
}

int client_passive_data(t_ftp *f) {
    if (f->passive_cmd == 1)
        cmd_ls_3(f);
    else if (f->passive_cmd == 2)
        cmd_get_3(f);
    else if (f->passive_cmd == 3)
        cmd_put_3(f);
    else
        (void)client_read_from_user(f);
    return (client_read_from_server(f));
}
