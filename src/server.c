/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 02:02:26 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 10:20:41 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	server_show_usage(t_ftp *f)
{
	ft_printf("welcome to %s\n", FTP_SERVER_NAME);
	ft_printf("usage:\t%s <ip.ad.dr.es> <port>\n", f->argv[0]);
	ft_printf(" or\t%s <port>\n", f->argv[0]);
	ft_printf(" or\t%s\n", f->argv[0]);
	server_exit(f, "", 0);
}

void	server_parse(t_ftp *f, int argc, char **argv, char **envp)
{
	int	i;

	f->argc = argc;
	f->argv = argv;
	f->envp = envp;
	if (f->argc > 3)
		server_show_usage(f);
	i = 1;
	while (i < f->argc)
	{
		if ((ft_strcmp(f->argv[i], "-h") == 0) ||
				(ft_strcmp(f->argv[i], "--help") == 0))
			server_show_usage(f);
		i++;
	}
	f->listen_addr = LISTEN_ADDR;
	f->listen_port = LISTEN_PORT;
	if (f->argc == 2)
		f->listen_port = ft_atoi(f->argv[1]);
	if (f->argc == 3)
	{
		if (ft_strcmp(f->argv[1], "localhost") != 0)
			f->listen_addr = f->argv[1];
		f->listen_port = ft_atoi(f->argv[2]);
	}
}

void	server_start(int argc, char **argv, char **envp)
{
	t_ftp	*f;

	f = ft_memalloc(sizeof(t_ftp));
	f->running = 1;
	server_parse(f, argc, argv, envp);
	server_init(f);
	server_accept(f);
	server_fork(f);
	while (f->running == 1)
	{
		if (server_loop(f) == 0)
		{
			ft_printf("{red}closed connection to: %s:%d{eoc}\n",
			f->client_addr, f->client_port);
			close(f->client);
			server_accept(f);
		}
	}
	close(f->client);
	close(f->socket);
	server_cleanup(f);
}

int		main(int argc, char **argv, char **envp)
{
	server_start(argc, argv, envp);
	return (0);
}
