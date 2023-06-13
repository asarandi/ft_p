/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:32:47 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 07:47:01 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int cmd_ls(t_ftp *f) {
    if (f->input_copy != NULL) {
        free(f->input_copy);
    }
    f->input_copy = strdup(f->input);
    write(f->socket, "PASV\r\n", 6);
    f->passive_cmd = 1;
    return (1);
}

int cmd_ls_2(t_ftp *f) {
    char *str1;
    char *str2;

    if ((f->input_copy != NULL) && (word(f->input_copy, 1) != NULL)) {
        str1 = str_join("LIST ", word(f->input_copy, 1));
        free(f->input_copy);
        f->input_copy = NULL;
    } else
        str1 = strdup("LIST");
    str2 = str_join(str1, "\r\n");
    free(str1);
    write(f->socket, str2, strlen(str2));
    free(str2);
    return (1);
}

int cmd_ls_3(t_ftp *f) {
    f->passive->passive_output_fd = STDOUT_FILENO;
    client_read_passive(f->passive);
    close(f->passive->socket);
    f->passive_cmd = 0;
    return (1);
}
