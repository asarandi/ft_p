/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sockets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:36:41 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 09:37:22 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	socket_create(t_ftp *f)
{
	f->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (f->socket == -1)
	{
		f->error = E_SOCKET;
		return (0);
	}
	return (1);
}

int	socket_options(t_ftp *f)
{
	int	o1;
	int o2;

	f->opt = 1;
	o1 = setsockopt(f->socket, SOL_SOCKET, SO_REUSEADDR,
			&f->opt, sizeof(f->opt));
	o2 = setsockopt(f->socket, SOL_SOCKET, SO_REUSEPORT,
			&f->opt, sizeof(f->opt));
	if ((o1 == -1) || (o2 == -1))
	{
		close(f->socket);
		f->error = E_SETSOCKOPT;
		return (0);
	}
	return (1);
}

int	socket_bind(t_ftp *f)
{
	int	r;

	f->address.sin_family = AF_INET;
	f->address.sin_addr.s_addr = inet_addr(f->listen_addr);
	f->address.sin_port = htons(f->listen_port);
	f->addr_len = sizeof(f->address);
	r = bind(f->socket, (struct sockaddr *)&f->address, f->addr_len);
	if (r == -1)
	{
		close(f->socket);
		f->error = E_BIND;
		return (0);
	}
	return (1);
}

int	socket_listen(t_ftp *f)
{
	if (listen(f->socket, 1) == -1)
	{
		close(f->socket);
		f->error = E_LISTEN;
		return (0);
	}
	return (1);
}
