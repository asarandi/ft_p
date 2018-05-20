/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:47:59 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 00:48:08 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

const char	*g_cmds[] = {
	"SYST", "PASV", "PORT", "PWD", "CWD", "LIST", "STOR",
	"RETR", "USER", "PASS", "HELP", "MKD", "QUIT", "SIZE",
	"TYPE", "CDUP", "DELE", "RMD"};

static int	(*g_functions[]) (t_ftp *) = {
	&cmd_syst, &cmd_pasv, &cmd_port, &cmd_pwd, &cmd_cwd, &cmd_list, &cmd_stor,
	&cmd_retr, &cmd_user, &cmd_pass, &cmd_help, &cmd_mkd, &cmd_quit, &cmd_size,
	&cmd_type, &cmd_cdup, &cmd_dele, &cmd_rmd};

void	server_init(t_ftp *f)
{
	f->home = getcwd(NULL, 0);
	f->bin_ls = BIN_LS;
	if (incoming_create(f) != 1)
		server_exit(f, f->error, EXIT_FAILURE);
	ft_printf("server started, listening on %s:%d\n",
			inet_ntoa(f->address.sin_addr),
			ntohs(f->address.sin_port));
	(void)signal(SIGINT, sigint_handler);
	g_ftp = f;
	return ;
}

void	server_accept(t_ftp *f)
{
	if (incoming_accept(f) != 1)
		server_exit(f, f->error, EXIT_FAILURE);
	f->client_addr = inet_ntoa(f->address.sin_addr);
	f->client_port = ntohs(f->address.sin_port);
	ft_printf("{cyan}incoming connection from: %s:%d{eoc}\n",
			f->client_addr, f->client_port);
	ftp_send_text(f, 220, FTP_SERVER_NAME);
}

void	server_fork(t_ftp *f)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		ft_printf(E_FORK);
	else if (pid == 0)
	{
		close(f->client);
		close(f->socket);
		server_start(f->argc, f->argv, f->envp);
	}
	return ;
}

int		server_loop(t_ftp *f)
{
	int		i;

	(void)ft_bzero(f->buf, sizeof(f->buf));
	if ((f->buf_len = recv(f->client, f->buf, sizeof(f->buf), 0)) <= 0)
		return (0);
	(void)ft_printf("{green}[%s:%d] recv: {eoc}",
			f->client_addr, f->client_port);
	(void)write(STDOUT_FILENO, f->buf, f->buf_len);
	if (((f->req = request_split(f->buf)) == NULL) || (f->req[0] == NULL))
		i = CMD_COUNT;
	else
		i = 0;
	while (i < CMD_COUNT)
	{
		if (ft_strnicmp(f->req[0], g_cmds[i], ft_strlen(g_cmds[i])) == 0)
		{
			(void)g_functions[i](f);
			break ;
		}
		i++;
	}
	if (i == CMD_COUNT)
		(void)ftp_send_text(f, 502, "Command not implemented.");
	(void)destroy_char_array(f->req);
	return (1);
}
