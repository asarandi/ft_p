/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_incoming.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:38:22 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 04:22:21 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	incoming_accept(t_ftp *f)
{
	f->client = accept(f->socket,
			(struct sockaddr *)&f->address, &f->addr_len);
	if (f->client == -1)
	{
		close(f->socket);
		f->error = E_ACCEPT;
		return (0);
	}
	return (1);
}

int	incoming_create(t_ftp *f)
{
	if (socket_create(f) != 1)
		return (0);
	if (socket_options(f) != 1)
		return (0);
	if (socket_bind(f) != 1)
		return (0);
	if (socket_listen(f) != 1)
		return (0);
	return (1);
}
