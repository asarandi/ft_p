/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cwd_cdup_mkd_rmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:59:10 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 18:59:59 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int cmd_rmd(t_ftp *f) {
    if (rmdir(word(f->buf, 1)) == 0) {
        (void)ftp_send_text(f, 250, "Directory removed successfully.");
        return (1);
    } else
        (void)ftp_send_text(f, 550, "Failed to remove directory.");
    return (0);
}

int cmd_mkd(t_ftp *f) {
    if (mkdir(word(f->buf, 1), 0755) == 0) {
        (void)ftp_send_text(f, 250, "Directory created successfully.");
        return (1);
    } else
        (void)ftp_send_text(f, 550, "Failed to create directory.");
    return (0);
}

int cmd_cwd(t_ftp *f) {
    if (chdir(word(f->buf, 1)) == 0) {
        (void)ftp_send_text(f, 250, "Directory successfully changed.");
        return (1);
    } else
        (void)ftp_send_text(f, 550, "Failed to change directory.");
    return (0);
}

int cmd_cdup(t_ftp *f) {
    if (chdir("..") == 0) {
        (void)ftp_send_text(f, 250, "Directory successfully changed.");
        return (1);
    } else
        (void)ftp_send_text(f, 550, "Failed to change directory.");
    return (0);
}

int cmd_pwd(t_ftp *f) {
    char buf[1024];

    snprintf(buf, 1024, "\"%s\"", getcwd(NULL, 0));
    (void)ftp_send_text(f, 257, buf);
    return (1);
}
