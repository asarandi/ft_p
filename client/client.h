/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:07:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:51:47 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
#define CLIENT_H

#include "functions.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CLIENT_PROMPT "ftp >>"
#define CONNECT_PORT "4242"
#define PORT_21 "21"
#define CONNECT_ADDR "127.0.0.1"
#define FTP_CLIENT_NAME "(ftp-client@42 v0.1b)"
#define E_SOCKET "error: socket() failed\n"
#define E_SETSOCKOPT "error: setsockopt() failed\n"
#define E_BIND "error: bind() failed\n"
#define E_LISTEN "error: listen() failed\n"
#define E_ACCEPT "error: accept() failed\n"
#define E_FORK "error: fork() failed\n"
#define E_GETADDRINFO "error: getaddrinfo() failed\n"
#define E_CONNECT "error: failed to connect\n"
#define CMD_COUNT 8
#define BIN_LS "/bin/ls"

#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN "\033[1;36m"
#define END_OF_COLOR "\033[0;00m"

typedef struct s_ftp {
    int argc;
    char **argv;
    char **envp;
    char *home;
    char *bin_ls;
    char *connect_addr;
    char *connect_port;
    int socket;
    int opt;
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *res0;
    socklen_t addr_len;
    struct sockaddr_in address;
    int client;
    char *print_addr;
    int print_port;
    char *error;
    int status;
    char *input;
    char *input_copy;
    char buf[1024];
    ssize_t buf_len;
    char **req;
    int response_code;
    int use_passive;
    int running;
    int passive_cmd;
    char *passive_file;
    char *passive_ip;
    char *passive_port;
    int passive_output_fd;
    struct s_ftp *passive;

} t_ftp;

extern const char *g_cmds[];
extern t_ftp *g_ftp;

#endif
