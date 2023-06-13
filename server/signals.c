/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:52:22 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:21:48 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_ftp *g_ftp;

void listener_sigint_handler(int signo) {
    if (signo == SIGINT) {
        dprintf(STDERR_FILENO, "Terminating listener process...\n");
        g_ftp->running = 0;
        server_exit(g_ftp, "", 130);
    }
}

void listener_sigchld_handler(int signo) {
    pid_t pid;

    if (signo == SIGCHLD) {
        pid = 0;
        pid = wait4(pid, NULL, 0, NULL);
        printf(COLOR_CYAN "[listener] worker process exits, " END_OF_COLOR);
        printf(COLOR_CYAN "pid %u" END_OF_COLOR "\n\n", pid);
    }
}

void worker_sigint_handler(int signo) {
    if (signo == SIGINT) {
        dprintf(STDERR_FILENO, "Terminating worker process...\n");
        g_ftp->running = 0;
        server_exit(g_ftp, "", 130);
    }
}

void worker_sigchld_handler(int signo) {
    pid_t pid;

    if (signo == SIGCHLD) {
        pid = 0;
        pid = wait4(pid, NULL, 0, NULL);
    }
}
