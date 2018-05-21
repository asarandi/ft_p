/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:41:24 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:56:37 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	socket_set_hints(t_ftp *f)
{
	f->hints.ai_family = PF_UNSPEC;
	f->hints.ai_socktype = SOCK_STREAM;
	return (1);
}

int	socket_return_error(t_ftp *f, char *e)
{
	f->error = e;
	return (0);
}

int	socket_connect(t_ftp *f)
{
	(void)socket_set_hints(f);
	if (getaddrinfo(f->connect_addr, f->connect_port, &f->hints, &f->res0) != 0)
		return (socket_return_error(f, E_GETADDRINFO));
	f->res = f->res0;
	while (f->res != NULL)
	{
		f->socket = socket(f->res->ai_family,
				f->res->ai_socktype, f->res->ai_protocol);
		if (f->socket != -1)
		{
			if (connect(f->socket, f->res->ai_addr, f->res->ai_addrlen) != -1)
				return (1);
			close(f->socket);
		}
		f->res = f->res->ai_next;
	}
	freeaddrinfo(f->res0);
	f->res0 = NULL;
	return (socket_return_error(f, E_CONNECT));
}
