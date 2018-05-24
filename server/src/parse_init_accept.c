/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_accept.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:07:40 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:08:05 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	server_parse(t_ftp *f)
{
	int	i;

	if (f->argc > 3)
		return (server_show_usage(f));
	i = 1;
	while (i < f->argc)
	{
		if ((ft_strcmp(f->argv[i], "-h") == 0) ||
				(ft_strcmp(f->argv[i], "--help") == 0))
			return (server_show_usage(f));
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
	return (1);
}

int	server_init(t_ftp *f)
{
	f->bin_ls = BIN_LS;
	if (incoming_create(f) != 1)
		return (0);
	ft_printf("server started, listening on %s:%d\n",
			inet_ntoa(f->address.sin_addr),
			ntohs(f->address.sin_port));
	(void)signal(SIGINT, listener_sigint_handler);
	(void)signal(SIGCHLD, listener_sigchld_handler);
	g_ftp = f;
	return (1);
}

int	server_accept(t_ftp *f)
{
	if (incoming_accept(f) != 1)
		return (0);
	f->client_addr = inet_ntoa(f->address.sin_addr);
	f->client_port = ntohs(f->address.sin_port);
	ft_printf("{cyan}[listener] incoming connection from: %s:%d{eoc}\n",
			f->client_addr, f->client_port);
	return (1);
}
