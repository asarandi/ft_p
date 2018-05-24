/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:48:07 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:14:49 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_fork(t_ftp *f)
{
	pid_t	pid;
	t_ftp	*c;

	if ((pid = fork()) == -1)
		ft_printf(E_FORK);
	else if (pid == 0)
	{
		c = ft_memalloc(sizeof(t_ftp));
		c = ft_memcpy(c, f, sizeof(t_ftp));
		close(f->socket);
		(void)signal(SIGINT, worker_sigint_handler);
		(void)signal(SIGCHLD, worker_sigchld_handler);
		c->pid = getpid();
		ft_printf("{cyan}[listener] spawning new worker process, {eoc}");
		ft_printf("{cyan}pid %lu{eoc}\n", c->pid);
		g_ftp = c;
		ftp_send_text(c, 220, FTP_SERVER_NAME);
		worker_routine(c);
		exit(0);
	}
	close(f->client);
	return ;
}

void	server_start(int argc, char **argv, char **envp)
{
	t_ftp	*f;

	f = ft_memalloc(sizeof(t_ftp));
	f->running = 1;
	f->argc = argc;
	f->argv = argv;
	f->envp = envp;
	if (server_parse(f) != 1)
		return (server_cleanup(f));
	if (server_init(f) != 1)
		return (server_cleanup(f));
	while ((f->running == 1) && (server_accept(f) == 1))
	{
		server_fork(f);
	}
	server_cleanup(f);
	return ;
}

int		main(int argc, char **argv, char **envp)
{
	server_start(argc, argv, envp);
	return (0);
}
