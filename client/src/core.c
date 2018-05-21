/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:44:55 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:53:36 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_connect(t_ftp *f)
{
	struct sockaddr_in	*in;

	f->home = getcwd(NULL, 0);
	f->bin_ls = BIN_LS;
	ft_printf("{yellow}attempting connection to [%s:%s]... {eoc}",
			f->connect_addr, f->connect_port);
	if (socket_connect(f) != 1)
		client_exit(f, f->error, EXIT_FAILURE);
	in = (struct sockaddr_in *)f->res->ai_addr;
	f->print_addr = inet_ntoa(in->sin_addr);
	f->print_port = ntohs(in->sin_port);
	ft_printf("{yellow}connected to %s:%d{eoc}\n",
			f->print_addr, f->print_port);
	(void)signal(SIGINT, sigint_handler);
	g_ftp = f;
	return ;
}

int		client_loop(t_ftp *f)
{
	if (client_read_from_user(f) != 1)
		return (0);
	if (client_read_from_server(f) != 1)
		return (0);
	if (f->response_code == 227)
		(void)client_init_passive(f);
	if (f->response_code == 150)
	{
		(void)client_passive_data(f);
		free(f->passive);
		f->passive = NULL;
	}
	return (1);
}

void	client_start(int argc, char **argv, char **envp)
{
	t_ftp	*f;

	f = ft_memalloc(sizeof(t_ftp));
	f->argc = argc;
	f->argv = argv;
	f->envp = envp;
	f->running = 1;
	g_ftp = f;
	client_parse(f);
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
	client_exit(f, "", EXIT_SUCCESS);
}
