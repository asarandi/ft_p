/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:07:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 07:34:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft.h"
# include "libftprintf.h"
# include "functions.h"

# define LISTEN_PORT		4242
# define LISTEN_ADDR		"127.0.0.1"
# define FTP_SERVER_NAME	"(ftp-server@42 v0.1a)"
# define E_SOCKET			"error: socket() failed\n"
# define E_SETSOCKOPT		"error: setsockopt() failed\n"
# define E_BIND				"error: bind() failed\n"
# define E_LISTEN			"error: listen() failed\n"
# define E_ACCEPT			"error: accept() failed\n"
# define E_FORK				"error: fork() failed\n"
# define CMD_COUNT			18
# define BIN_LS				"/bin/ls"

typedef struct			s_ftp
{
	int					argc;
	char				**argv;
	char				**envp;
	char				*home;
	char				*bin_ls;
	char				*listen_addr;
	int					listen_port;
	int					socket;
	int					opt;
	socklen_t			addr_len;
	struct sockaddr_in	address;
	int					client;
	char				*client_addr;
	int					client_port;
	char				*error;
	int					status;
	char				buf[1024];
	ssize_t				buf_len;
	char				**req;
	int					use_passive;
	int					running;
	struct s_ftp		*passive;

}						t_ftp;

extern const char		*g_cmds[];
extern t_ftp			*g_ftp;

#endif
