/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:48:07 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/24 09:31:31 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void server_fork(t_ftp *f) {
    pid_t pid;

    if ((pid = fork()) == -1)
        printf(E_FORK);
    else if (pid == 0) {
        close(f->socket);
        f->pid = getpid();
        g_ftp = f;
        (void)signal(SIGINT, worker_sigint_handler);
        (void)signal(SIGCHLD, worker_sigchld_handler);
        printf(COLOR_CYAN
               "[listener] spawning new worker process, " END_OF_COLOR);
        printf(COLOR_CYAN "pid %u" END_OF_COLOR "\n", f->pid);
        ftp_send_text(f, 220, FTP_SERVER_NAME);
        worker_routine(f);
        exit(0);
    }
    close(f->client);
    return;
}

void server_start(int argc, char **argv, char **envp) {
    t_ftp *f;

    f = calloc(1, sizeof(t_ftp));
    f->running = 1;
    f->argc = argc;
    f->argv = argv;
    f->envp = envp;
    if (server_parse(f) != 1)
        return (server_cleanup(f));
    if (server_init(f) != 1)
        return (server_cleanup(f));
    while ((f->running == 1) && (server_accept(f) == 1)) {
        server_fork(f);
    }
    server_cleanup(f);
    return;
}

int main(int argc, char **argv, char **envp) {
    server_start(argc, argv, envp);
    return (0);
}
