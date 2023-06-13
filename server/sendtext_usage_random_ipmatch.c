/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendtext_usage_random_ipmatch.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:11:30 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:17:34 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int ftp_send_text(t_ftp *f, int code, char *str) {
    printf(COLOR_BLUE "[%s:%d] send: " END_OF_COLOR, f->client_addr,
           f->client_port);
    printf("%d %s\r\n", code, str);
    return (dprintf(f->client, "%d %s\r\n", code, str));
}

int server_show_usage(t_ftp *f) {
    printf("welcome to %s\n", FTP_SERVER_NAME);
    printf("usage:\t%s <ip.ad.dr.es> <port>\n", f->argv[0]);
    printf(" or\t%s <port>\n", f->argv[0]);
    printf(" or\t%s\n", f->argv[0]);
    return (0);
}

int random_in_range(t_ftp *f, int min, int max) {
    srand(f->pid + f->rnd);
    f->rnd = rand() % (max + 1 - min) + min;
    return (f->rnd);
}

int ip_matches(t_ftp *f) {
    unsigned long long a;
    unsigned long long b;

    a = f->address.sin_addr.s_addr;
    b = f->passive->address.sin_addr.s_addr;
    if (a == b)
        return (1);
    (void)ftp_send_text(f, 425, "Security: Bad IP connecting.");
    return (0);
}
