/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:07:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 20:12:48 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include "libft.h"
# include "libftprintf.h"
# include "functions.h"

# define CLIENT_PROMPT		"ftp >>"
# define CONNECT_PORT		"4242"
# define PORT_21			"21"
# define CONNECT_ADDR		"127.0.0.1"
# define FTP_CLIENT_NAME	"(ftp-client@42 v0.1a)"
# define E_SOCKET			"error: socket() failed\n"
# define E_SETSOCKOPT		"error: setsockopt() failed\n"
# define E_BIND				"error: bind() failed\n"
# define E_LISTEN			"error: listen() failed\n"
# define E_ACCEPT			"error: accept() failed\n"
# define E_FORK				"error: fork() failed\n"
# define E_GETADDRINFO		"error: getaddrinfo() failed\n"
# define E_CONNECT			"error: failed to connect\n"
# define CMD_COUNT			7
# define BIN_LS				"/bin/ls"

typedef struct			s_ftp
{
	int					argc;
	char				**argv;
	char				**envp;
	char				*home;
	char				*bin_ls;
	char				*connect_addr;
	char				*connect_port;
	int					socket;
	int					opt;
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct addrinfo		*res0;


	
	socklen_t			addr_len;
	struct sockaddr_in	address;
	int					client;
	char				*print_addr;
	int					print_port;
	char				*error;
	int					status;
	char				*input;
	char				buf[1024];
	ssize_t				buf_len;
	char				**req;
	int					use_passive;
	int					running;
	int					passive_cmd;	//ls - 1,  get - 2,  put - 3
	char				*passive_file;
	char				*passive_ip;
	char				*passive_port;
	int					passive_output_fd;
	struct s_ftp		*passive;

}						t_ftp;

extern const char		*g_cmds[];
extern t_ftp			*g_ftp;

#endif
