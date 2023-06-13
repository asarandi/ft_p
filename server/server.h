/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:07:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 18:45:03 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
#define SERVER_H

#include "functions.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LISTEN_PORT 4242
#define LISTEN_ADDR "0.0.0.0"
#define FTP_SERVER_NAME "(ftp-server@42 v0.1b)"
#define E_SOCKET "error: socket() failed\n"
#define E_SETSOCKOPT "error: setsockopt() failed\n"
#define E_BIND "error: bind() failed\n"
#define E_LISTEN "error: listen() failed\n"
#define E_ACCEPT "error: accept() failed\n"
#define E_FORK "error: fork() failed\n"
#define CMD_COUNT 18
#define BIN_LS "/bin/ls"
#define RND_PORT_MIN 49152
#define RND_PORT_MAX 65535
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_CYAN "\033[1;36m"
#define END_OF_COLOR "\033[0;00m"

typedef struct s_ftp {
    pid_t pid;
    int rnd;
    int argc;
    char **argv;
    char **envp;
    char *bin_ls;
    char *listen_addr;
    int listen_port;
    int socket;
    int opt;
    socklen_t addr_len;
    struct sockaddr_in address;
    int client;
    char *client_addr;
    int client_port;
    char *error;
    char buf[1024];
    ssize_t buf_len;
    char **req;
    int use_passive;
    int running;
    struct s_ftp *passive;

} t_ftp;

extern const char *g_cmds[];
extern t_ftp *g_ftp;

#endif
