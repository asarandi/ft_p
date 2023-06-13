/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dele_size_help_type_quit.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:02:20 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:03:16 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int cmd_dele(t_ftp *f) {
    if (unlink(word(f->buf, 1)) == 0) {
        (void)ftp_send_text(f, 250, "File deleted successfully.");
        return (1);
    } else
        (void)ftp_send_text(f, 550, "Failed to delete file.");
    return (0);
}

int cmd_size(t_ftp *f) {
    ssize_t size;

    size = file_get_size(word(f->buf, 1));
    if (size == -1) {
        ftp_send_text(f, 550, "Could not get file size.");
        return (0);
    } else {
        printf(COLOR_BLUE "[%s:%d] send: " END_OF_COLOR, f->client_addr,
               f->client_port);
        printf("213 %ld\r\n", size);
        dprintf(f->client, "213 %ld\r\n", size);
    }
    return (1);
}

int cmd_help(t_ftp *f) {
    int i;

    printf(COLOR_BLUE "[%s:%d] send: " END_OF_COLOR, f->client_addr,
           f->client_port);
    printf("214-The following commands are recognized.\r\n");
    dprintf(f->client, "214-The following commands are recognized.\r\n");
    i = 0;
    while (i < CMD_COUNT) {
        printf(g_cmds[i]);
        dprintf(f->client, g_cmds[i]);
        if ((++i % 3 == 0) || (i >= CMD_COUNT)) {
            printf("\r\n");
            dprintf(f->client, "\r\n");
        } else {
            printf(" ");
            dprintf(f->client, " ");
        }
    }
    ftp_send_text(f, 214, "Help OK.");
    return (1);
}

int cmd_type(t_ftp *f) {
    ftp_send_text(f, 200, "OK.");
    return (1);
}

int cmd_quit(t_ftp *f) {
    (void)ftp_send_text(f, 221, "Goodbye.");
    close(f->client);
    return (0);
}
