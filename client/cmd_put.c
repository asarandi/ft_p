/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:33:45 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 07:46:10 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int cmd_put(t_ftp *f) {
    if (word(f->input, 1) == NULL) {
        printf("Command is incomplete.\n");
        return (client_read_from_user(f));
    }
    if (f->input_copy != NULL) {
        free(f->input_copy);
    }
    f->input_copy = strdup(f->input);
    write(f->socket, "PASV\r\n", 6);
    f->passive_cmd = 3;
    return (1);
}

int cmd_put_2(t_ftp *f) {
    char *str1;
    char *str2;

    str1 = str_join("STOR ", word(f->input_copy, 1));
    str2 = str_join(str1, "\r\n");
    free(str1);
    write(f->socket, str2, strlen(str2));
    free(str2);
    f->passive_file = strdup(word(f->input_copy, 1));
    free(f->input_copy);
    f->input_copy = NULL;
    return (1);
}

int cmd_put_3(t_ftp *f) {
    int fd;
    char c;

    if ((fd = open(f->passive_file, O_RDONLY)) > 0) {
        printf(COLOR_GREEN
               "{uploading file to remote folder ... " END_OF_COLOR);
        while ((read(fd, &c, 1) > 0) && (f->running == 1))
            write(f->passive->socket, &c, 1);
        close(fd);
        if (f->running == 0)
            printf(COLOR_RED "aborted" END_OF_COLOR "\n");
        else
            printf(COLOR_GREEN "done" END_OF_COLOR "\n");
    } else
        printf(COLOR_RED "error opening file .." END_OF_COLOR "\n");
    close(f->passive->socket);
    if (f->passive_file != NULL)
        free(f->passive_file);
    f->passive_file = NULL;
    f->passive_cmd = 0;
    return (1);
}
