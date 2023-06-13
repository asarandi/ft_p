/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:09:49 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:10:07 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void passive_cleanup(t_ftp *f) {
    if (f->passive != NULL) {
        close(f->passive->client);
        close(f->passive->socket);
        free(f->passive);
        f->use_passive = 0;
        f->passive = NULL;
    }
    return;
}

void server_cleanup(t_ftp *f) {
    passive_cleanup(f);
    if (f->req != NULL)
        destroy_char_array(f->req);
    close(f->client);
    close(f->socket);
    free(f);
    return;
}

void server_exit(t_ftp *f, char *msg, int exit_code) {
    if (f->running)
        printf(msg);
    (void)server_cleanup(f);
    exit(exit_code);
}
