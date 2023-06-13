/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:57:08 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 18:57:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int cmd_retr(t_ftp *f) {
    unsigned char buf[65536];
    ssize_t num_read, num_write;
    int fd;

    if (!(f->use_passive == 1)) {
        (void)ftp_send_text(f, 425, "Use PORT or PASV first.");
        return (0);
    }

    if (!(incoming_accept(f->passive) == 1)) {
        (void)ftp_send_text(f, 450, "File send error.");
        passive_cleanup(f);
        return 1;
    }

    if (!(ip_matches(f) == 1)) {
        passive_cleanup(f);
        return 1;
    }

    if ((fd = open(word(f->buf, 1), O_RDONLY)) < 0) {
        ftp_send_text(f, 550, "Failed to open file.");
        passive_cleanup(f);
        return 1;
    }

    (void)ftp_send_text(f, 150, "Sending over file");

    num_read = num_write = 0;
    for (;;) {
        num_read = read(fd, buf, 65536);
        if (num_read <= 0)
            break;
        num_write = write(f->passive->client, buf, num_read);
        if (num_write <= 0)
            break;
        if (num_read != num_write)
            break;
    }

    if (num_read == 0) {
        (void)ftp_send_text(f, 226, "File sent successfully.");
    } else {
        if (num_read < 0 || num_write < 0) {
            perror(__func__);
        }
        (void)ftp_send_text(f, 450, "File send error.");
    }

    passive_cleanup(f);
    return (1);
}
