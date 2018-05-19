/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmds_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:31:56 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 04:22:07 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	cmd_quit(t_ftp *f)
{
	(void)ftp_send_text(f, 221, "Goodbye.");
	close(f->client);
	return (1);
}

int	cmd_size(t_ftp *f)
{
	ssize_t	size;

	size = file_get_size(word(f->buf, 1));
	if (size == -1)
	{
		ftp_send_text(f, 550, "Could not get file size.");
		return (0);
	}
	else
	{
		ft_printf("{blue}[%s:%d] send: {eoc}",
			f->client_addr, f->client_port);
		ft_printf("213 %ld\r\n", size);
		ft_fprintf(f->client, "213 %ld\r\n", size);
	}
	return (1);
}

int	cmd_type(t_ftp *f)
{
	ftp_send_text(f, 200, "OK.");
	return (1);
}

int	cmd_help(t_ftp *f)
{
	int	i;

	ft_printf("{blue}[%s:%d] send: {eoc}", f->client_addr, f->client_port);
	ft_printf("214-The following commands are recognized.\r\n");
	ft_fprintf(f->client, "214-The following commands are recognized.\r\n");
	i = 0;
	while (i < CMD_COUNT)
	{
		ft_printf(g_cmds[i]);
		ft_fprintf(f->client, g_cmds[i]);
		if ((++i % 3 == 0) || (i >= CMD_COUNT))
		{
			ft_printf("\r\n");
			ft_fprintf(f->client, "\r\n");
		}
		else
		{
			ft_printf(" ");
			ft_fprintf(f->client, " ");
		}
	}
	ftp_send_text(f, 214, "Help OK.");
	return (1);
}
