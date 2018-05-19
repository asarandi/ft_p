/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sockets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:36:41 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 05:59:31 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"



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


