/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 02:02:26 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 10:23:24 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_ftp	*g_ftp;

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_fprintf(STDERR_FILENO, "Terminating client...\n");
		g_ftp->running = 0;
		close(g_ftp->socket);
	}
}


void	client_cleanup(t_ftp *f)
{
	if (f->home != NULL)
		free(f->home);
	if (f->res0 != NULL)
		freeaddrinfo(f->res0);
	free(f);
	return ;
}

void	client_exit(t_ftp *f, char *msg, int exit_code)
{
	if (f->running)
		ft_printf(msg);
	(void)client_cleanup(f);
	exit(exit_code);
}

int	socket_connect(t_ftp *f)
{
	struct	sockaddr_in	*in;

	f->hints.ai_family = PF_UNSPEC;
	f->hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(f->connect_addr, f->connect_port, &f->hints, &f->res0) != 0)
	{
		f->error = E_GETADDRINFO;
		return (0);
	}
	f->res = f->res0;
	while (f->res != NULL)
	{
		f->socket = socket(f->res->ai_family,
				f->res->ai_socktype, f->res->ai_protocol);
		if (f->socket != -1)
		{


			in = (struct sockaddr_in *)f->res->ai_addr;
			f->print_addr = inet_ntoa(in->sin_addr);
			f->print_port = ntohs(in->sin_port);
			ft_printf("attempting connection to %s:%d\n", f->print_addr, f->print_port);


			if (connect(f->socket, f->res->ai_addr, f->res->ai_addrlen) != -1)
				return (1);
			close(f->socket);
		}
		f->res = f->res->ai_next;
	}
	freeaddrinfo(f->res0);
	f->res0 = NULL;
	f->error = E_CONNECT;
	return (0);
}

void	client_connect(t_ftp *f)
{
	struct	sockaddr_in	*in;

	f->home = getcwd(NULL, 0);
	f->bin_ls = BIN_LS;
	if (socket_connect(f) != 1)
		client_exit(f, f->error, EXIT_FAILURE);
	in = (struct sockaddr_in *)f->res->ai_addr;
	f->print_addr = inet_ntoa(in->sin_addr);
	f->print_port = ntohs(in->sin_port);
	ft_printf("{yellow}connected to %s:%d{eoc}\n", f->print_addr, f->print_port);
	(void)signal(SIGINT, sigint_handler);
	g_ftp = f;
	return ;
}


void	client_show_usage(t_ftp *f)
{
	ft_printf("welcome to %s\n", FTP_CLIENT_NAME);
	ft_printf("usage:\t%s <ip.ad.dr.es> <port>\n", f->argv[0]);
	ft_printf(" or\t%s <port>\n", f->argv[0]);
	ft_printf(" or\t%s\n", f->argv[0]);
	client_exit(f, "", 0);
}

void	client_parse(t_ftp *f, int argc, char **argv, char **envp)
{
	int	i;

	f->argc = argc;
	f->argv = argv;
	f->envp = envp;
	if (f->argc > 3)
		client_show_usage(f);
	i = 1;
	while (i < f->argc)
	{
		if ((ft_strcmp(f->argv[i], "-h") == 0) ||
				(ft_strcmp(f->argv[i], "--help") == 0))
			client_show_usage(f);
		i++;
	}
	f->connect_addr = CONNECT_ADDR;
	f->connect_port = CONNECT_PORT;
	if (f->argc == 2)
	{
		f->connect_port = PORT_21;
		f->connect_addr = f->argv[1];
	}
	if (f->argc == 3)
	{
		f->connect_addr = f->argv[1];
		f->connect_port = f->argv[2];
	}
}

int	client_read_from_server(t_ftp *f)
{
	int	flag;
	int	i;
	int	r;

	(void)ft_printf("{cyan}[%s:%d]: {eoc}",
			f->print_addr, f->print_port);
	flag = 0;
	i = 0;
	(void)ft_bzero(f->buf, sizeof(f->buf));
	while (flag != 5)
	{
		r = recv(f->socket, &f->buf[i], 1, 0);
		if (r <= 0)
			return (0);
		write(STDOUT_FILENO, &f->buf[i], 1);
		if ((i < 3) && (ft_isdigit(f->buf[i])))
			flag++;
		if ((i == 3) && (flag == 3))
		{
			if (ft_isspace(f->buf[i]))
				flag++;
			else
				flag = 0;
		}
		if (f->buf[i] == '\n')
		{
			if (flag == 4)
				flag++;
			else
			{
				flag = 0;
				i = -1;
				(void)ft_bzero(f->buf, sizeof(f->buf));
			}
		}
		i++;
	}
	return (1);
}

int	client_read_from_user(t_ftp *f)
{
	char	*input;
	char	*cmd;

	(void)ft_printf("{magenta}%s {eoc}", CLIENT_PROMPT);
	while (get_next_line(STDIN_FILENO, &input) > 0)
	{
		if (ft_strlen(input) > 0)
		{
			cmd = ft_strjoin(input, "\r\n");
			write(f->socket, cmd, ft_strlen(cmd));
			free(cmd);
			free(input);
			return (1);
		}
		free(input);
		continue ;
	}
	return (0);
}

int	client_loop(t_ftp *f)
{
	if (client_read_from_user(f) != 1)
		return (0);
	return (client_read_from_server(f));
}

void	client_start(int argc, char **argv, char **envp)
{
	t_ftp	*f;

	f = ft_memalloc(sizeof(t_ftp));
	f->running = 1;
	g_ftp = f;
	client_parse(f, argc, argv, envp);
	client_connect(f);
	(void)client_read_from_server(f);
	while (f->running == 1)
	{
		if (client_loop(f) == 0)
		{
			ft_printf("{red}closed connection to: %s:%d{eoc}\n",
			f->print_addr, f->print_port);
			break ;
		}
	}
	close(f->client);
	close(f->socket);
	client_cleanup(f);
}

int		main(int argc, char **argv, char **envp)
{
	client_start(argc, argv, envp);
	return (0);
}
