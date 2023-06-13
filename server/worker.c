/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:08:43 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:20:52 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

const char *g_cmds[] = {"SYST", "PASV", "PORT", "PWD",  "CWD",  "LIST",
                        "STOR", "RETR", "USER", "PASS", "HELP", "MKD",
                        "QUIT", "SIZE", "TYPE", "CDUP", "DELE", "RMD"};

static int (*g_functions[])(t_ftp *) = {
    &cmd_syst, &cmd_pasv, &cmd_port, &cmd_pwd,  &cmd_cwd,  &cmd_list,
    &cmd_stor, &cmd_retr, &cmd_user, &cmd_pass, &cmd_help, &cmd_mkd,
    &cmd_quit, &cmd_size, &cmd_type, &cmd_cdup, &cmd_dele, &cmd_rmd};

int server_loop(t_ftp *f) {
    int i;

    if ((f->buf_len = recv(f->client, f->buf, sizeof(f->buf), 0)) <= 0)
        return (0);
    f->buf[f->buf_len] = '\0';
    (void)printf(COLOR_GREEN "[%s:%d] recv:" END_OF_COLOR " %s", f->client_addr,
                 f->client_port, f->buf);
    if (((f->req = request_split(f->buf)) == NULL) || (f->req[0] == NULL))
        i = CMD_COUNT;
    else
        i = 0;
    while (i < CMD_COUNT) {
        if (strcmp(f->req[0], g_cmds[i]) == 0) {
            (void)g_functions[i](f);
            break;
        }
        i++;
    }
    if (i == CMD_COUNT)
        (void)ftp_send_text(f, 502, "Command not implemented.");
    (void)destroy_char_array(f->req);
    f->req = NULL;
    return (1);
}

void worker_routine(t_ftp *f) {
    while (f->running == 1) {
        (void)memset(f->buf, 0, sizeof(f->buf));
        if (server_loop(f) != 1)
            break;
    }
    printf(COLOR_RED "closed connection to: %s:%d" END_OF_COLOR "\n",
           f->client_addr, f->client_port);
    server_exit(f, "", 0);
    return;
}
