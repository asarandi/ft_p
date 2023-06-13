/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:27:50 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:28:07 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void client_cleanup(t_ftp *f) {
    close(f->socket);
    (void)client_passive_cleanup(f);
    if (f->passive_ip != NULL)
        free(f->passive_ip);
    if (f->passive_port != NULL)
        free(f->passive_port);
    if (f->passive != NULL)
        free(f->passive);
    if (f->input != NULL)
        free(f->input);
    if (f->input_copy != NULL)
        free(f->input_copy);
    if (f->req != NULL)
        destroy_char_array(f->req);
    if (f->home != NULL)
        free(f->home);
    if (f->res0 != NULL)
        freeaddrinfo(f->res0);
    free(f);
    return;
}

void client_exit(t_ftp *f, char *msg, int exit_code) {
    if (f->running)
        printf("%s", msg);
    (void)client_cleanup(f);
    exit(exit_code);
}
