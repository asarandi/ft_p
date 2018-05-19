/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmds_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:20:11 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 03:36:54 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	passive_cleanup(t_ftp *f)
{
	close(f->passive->client);
	close(f->passive->socket);
	free(f->passive);
	f->use_passive = 0;
	return ;
}

int		cmd_pasv(t_ftp *f)
{
	t_ftp			*c;
	unsigned int	a;
	unsigned short	p;

	c = ft_memalloc(sizeof(t_ftp));
	c->listen_addr = f->listen_addr;
	c->listen_port = f->listen_port - 1;
	incoming_create(c);
	a = c->address.sin_addr.s_addr;
	p = c->address.sin_port;
	ft_printf("{blue}[%s:%d] send: {eoc}",
			f->client_addr, f->client_port);
	ft_printf("227 Entering Passive Mode (%d,%d,%d,%d,",
			a & 255, a >> 8 & 255, a >> 16 & 255, a >> 24 & 255);
	ft_printf("%d,%d).\r\n", p & 255, p >> 8 & 255);
	ft_fprintf(f->client, "227 Entering Passive Mode (%d,%d,%d,%d,",
			a & 255, a >> 8 & 255, a >> 16 & 255, a >> 24 & 255);
	ft_fprintf(f->client, "%d,%d).\r\n", p & 255, p >> 8 & 255);
	f->use_passive = 1;
	f->passive = c;
	return (1);
}

int		cmd_list_fork(t_ftp *f)
{
	pid_t	pid;
	char	*arg1;

	if ((pid = fork()) == -1)
	{
		ft_printf(E_FORK);
		return (0);
	}
	else if (pid == 0)
	{
		dup2(f->passive->client, STDOUT_FILENO);
		close(f->passive->client);
		close(STDIN_FILENO);
		close(STDERR_FILENO);
		arg1 = word(f->buf, 1);
		if ((arg1 != NULL) && (ft_strncmp("-a", arg1, 2) == 0)
				&& ((arg1[2] == 0) || (ft_isspace(arg1[2]))))
			execl(f->bin_ls, f->bin_ls, "-la", word(f->buf, 2), NULL);
		else
			execl(f->bin_ls, f->bin_ls, "-l", word(f->buf, 1), NULL);
		exit(0);
	}
	else
		wait4(pid, NULL, 0, NULL);
	return (1);
}

int		cmd_list(t_ftp *f)
{
	if (f->use_passive == 1)
	{
		(void)ftp_send_text(f, 150, "Here comes the directory listing.");
		if (incoming_accept(f->passive) == 1)
		{
			(void)cmd_list_fork(f);
			(void)ftp_send_text(f, 226, "Directory send OK.");
		}
		else
			(void)ftp_send_text(f, 450, "Directory send error.");
		passive_cleanup(f);
		return (1);
	}
	else
		(void)ftp_send_text(f, 425, "Use PORT or PASV first.");
	return (0);
}
