/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:07:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 00:47:58 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft.h"
# include "libftprintf.h"
# include "functions.h"
/*
	socket(2), 
	open(2), 
	close(2), 
	setsockopt(2), 
	getsockname(2)
	getprotobyname(3)
	bind(2), 
	connect(2), 
	listen(2), 
	accept(2)
	htons(3), 
	htonl(3), 
	ntohs(3), 
	ntohl(3)
	inet_addr(3), 
	inet_ntoa(3)
	send(2), 
	recv(2), 
	execv(2), 
	execl(2), 
	dup2(2), 
	wait4(2)
	fork(2), 
	getcwd(3), 
	exit(3), 
	printf(3), 
	signal(3)
	mmap(2), 
	munmap(2), 
	lseek(2),
	fstat(2)
	opendir(3), 
	readdir(3), 
	closedir(3)
	chdir(2), 
	mkdir(2), 
	unlink(2)
	read(2), 
	write(2), 
	malloc(3),
	free(3),
*/

#define LISTEN_PORT		2229
#define LISTEN_ADDR		"127.0.0.1"
//"10.114.9.26"
//"127.0.0.1"
#define FTP_SERVER_NAME	"(ftp@42 v0.1a)"
#define E_SOCKET		"error: socket() failed\n"
#define E_SETSOCKOPT	"error: setsockopt() failed\n"
#define E_BIND			"error: bind() failed\n"
#define	E_LISTEN		"error: listen() failed\n"
#define E_ACCEPT		"error: accept() failed\n"
#define E_FORK			"error: fork() failed\n"

typedef struct			s_ftp
{
	int					argc;
	char				**argv;
	char				**envp;
	char				*home;
	char				*ft_ls;
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

#endif
