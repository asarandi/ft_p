/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:33:16 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 07:45:26 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int cmd_get(t_ftp *f) {
    if (word(f->input, 1) == NULL) {
        printf("Command is incomplete.\n");
        return (client_read_from_user(f));
    }
    if (f->input_copy != NULL) {
        free(f->input_copy);
    }
    f->input_copy = strdup(f->input);
    write(f->socket, "PASV\r\n", 6);
    f->passive_cmd = 2;
    return (1);
}

int cmd_get_2(t_ftp *f) {
    char *str1;
    char *str2;

    str1 = str_join("RETR ", word(f->input_copy, 1));
    str2 = str_join(str1, "\r\n");
    free(str1);
    write(f->socket, str2, strlen(str2));
    free(str2);
    f->passive_file = strdup(word(f->input_copy, 1));
    free(f->input_copy);
    f->input_copy = NULL;
    return (1);
}

int cmd_get_3(t_ftp *f) {
    if ((f->passive->passive_output_fd =
             open(f->passive_file, O_CREAT | O_TRUNC | O_WRONLY, 0644)) > 0) {
        printf(COLOR_GREEN
               "downloading file to local folder ... " END_OF_COLOR);
        client_read_passive(f->passive);
        close(f->passive->passive_output_fd);
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
