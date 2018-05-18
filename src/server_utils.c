/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:51:59 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 10:19:44 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

t_ftp	*g_ftp;

int		ftp_send_text(t_ftp *f, int code, char *str)
{
	ft_printf("{blue}[%s:%d] send: {eoc}",
			f->client_addr, f->client_port);
	ft_printf("%d %s\r\n", code, str);
	return (ft_fprintf(f->client, "%d %s\r\n", code, str));
}

void	server_cleanup(t_ftp *f)
{
	if (f->home != NULL)
		free(f->home);
	if (f->ft_ls != NULL)
		free(f->ft_ls);
	free(f);
	return ;
}

void	server_exit(t_ftp *f, char *msg, int exit_code)
{
	if (f->running)
		ft_printf(msg);
	(void)server_cleanup(f);
	exit(exit_code);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_fprintf(STDERR_FILENO, "Terminating server...\n");
		g_ftp->running = 0;
		close(g_ftp->client);
		close(g_ftp->socket);
	}
}
