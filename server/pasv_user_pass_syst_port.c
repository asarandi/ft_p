/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasv_user_pass_syst_port.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:00:54 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:16:14 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int cmd_pasv(t_ftp *f) {
    t_ftp *c;
    unsigned int a;
    unsigned short p;

    c = calloc(1, sizeof(t_ftp));
    c->listen_addr = f->listen_addr;

    int success = 0;
    for (int attempts = 8; attempts > 0; --attempts) {
        c->listen_port = random_in_range(f, RND_PORT_MIN, RND_PORT_MAX);
        success = incoming_create(c);
        if (success)
            break;
        printf(COLOR_RED "incoming_create() failed, port = %d\n" END_OF_COLOR,
               c->listen_port);
    }

    if (!success) {
        printf("450 Command failed.\r\n");
        dprintf(f->client, "450 Command failed.\r\n");
        free(c);
        return 0;
    }

    a = c->address.sin_addr.s_addr;
    p = c->address.sin_port;
    printf(COLOR_BLUE "[%s:%d] send: " END_OF_COLOR, f->client_addr,
           f->client_port);
    printf("227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", a & 255,
           a >> 8 & 255, a >> 16 & 255, a >> 24 & 255, p & 255, p >> 8 & 255);
    dprintf(f->client, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
            a & 255, a >> 8 & 255, a >> 16 & 255, a >> 24 & 255, p & 255,
            p >> 8 & 255);
    f->use_passive = 1;
    f->passive = c;
    return (1);
}

int cmd_user(t_ftp *f) {
    (void)ftp_send_text(f, 200, "OK");
    return (1);
}

int cmd_pass(t_ftp *f) {
    (void)ftp_send_text(f, 200, "OK");
    return (1);
}

int cmd_syst(t_ftp *f) {
    (void)ftp_send_text(f, 215, "UNIX Type: L8");
    return (1);
}

int cmd_port(t_ftp *f) {
    (void)ftp_send_text(f, 502, "PORT is not yet implemented, use PASV");
    return (1);
}
