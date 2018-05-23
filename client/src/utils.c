/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:46:46 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 08:49:40 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_ftp	*g_ftp;

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_fprintf(STDERR_FILENO, "Terminating client...\n");
		client_exit(g_ftp, "", 130);
	}
	return ;
}

void	client_show_usage(t_ftp *f)
{
	ft_printf("welcome to %s\n", FTP_CLIENT_NAME);
	ft_printf("usage:\t%s <ip.ad.dr.es> <port>\n", f->argv[0]);
	ft_printf(" or\t%s <ip.ad.dr.es>\n", f->argv[0]);
	ft_printf(" or\t%s\n", f->argv[0]);
	client_exit(f, "", 0);
}

void	client_parse(t_ftp *f)
{
	int	i;

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
	return ;
}
