/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:55:35 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 18:56:24 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int cmd_list_fork(t_ftp *f) {
    pid_t pid;

    if ((pid = fork()) == -1) {
        printf(E_FORK);
        return (0);
    } else if (pid == 0) {
        dup2(f->passive->client, STDOUT_FILENO);
        close(f->passive->client);
        close(STDIN_FILENO);
        close(STDERR_FILENO);
        execl(f->bin_ls, f->bin_ls, "-la", word(f->buf, 1), NULL);
        exit(0);
    } else
        wait4(pid, NULL, 0, NULL);
    return (1);
}

int cmd_list(t_ftp *f) {
    if (f->use_passive == 1) {
        if (incoming_accept(f->passive) == 1) {
            if (ip_matches(f) == 1) {
                (void)ftp_send_text(f, 150,
                                    "Here comes the directory listing.");
                (void)cmd_list_fork(f);
                (void)ftp_send_text(f, 226, "Directory send OK.");
            }
        } else
            (void)ftp_send_text(f, 450, "Directory send error.");
        passive_cleanup(f);
        return (1);
    } else
        (void)ftp_send_text(f, 425, "Use PORT or PASV first.");
    return (0);
}
