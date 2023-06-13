/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:39:45 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 07:47:12 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int cmd_cd_local(t_ftp *f) {
    if (word(f->input, 1) == NULL) {
        printf("Command is incomplete.\n");
        return (client_read_from_user(f));
    }
    if (chdir(word(f->input, 1)) == 0)
        (void)printf("Directory successfully changed.\n");
    else
        (void)printf("Failed to change directory.\n");
    free(f->input);
    f->input = NULL;
    return (client_read_from_user(f));
}

int cmd_cd(t_ftp *f) {
    char *str1;
    char *str2;

    if (word(f->input, 1) == NULL) {
        printf("Command is incomplete.\n");
        return (client_read_from_user(f));
    }
    str1 = str_join("CWD ", word(f->input, 1));
    str2 = str_join(str1, "\r\n");
    free(str1);
    write(f->socket, str2, strlen(str2));
    free(str2);
    return (1);
}

int cmd_pwd(t_ftp *f) {
    write(f->socket, "PWD\r\n", 5);
    return (1);
}

int cmd_quit(t_ftp *f) {
    write(f->socket, "QUIT\r\n", 6);
    close(f->socket);
    client_exit(f, "bye!\n", EXIT_SUCCESS);
    return (0);
}

int cmd_help(t_ftp *f) {
    printf("the following commands are recognized by the client:\n");
    printf(" ls <arg>        - list remote directory contents\n");
    printf(" ls -a <arg>     - show hidden files\n");
    printf(" cd <arg>        - change directory\n");
    printf(" get <arg>       - download a remote file to client\n");
    printf(" put <arg>       - upload a local file to server\n");
    printf(" pwd             - print working directory\n");
    printf(" quit            - close connection and quit\n");
    printf(" !<cmd> <args..> - execute a shell command\n");
    printf(" @<cmd> <arg>    - execute a raw server command\n");
    printf(" @help           - list available server commands\n");
    return (client_read_from_user(f));
}
