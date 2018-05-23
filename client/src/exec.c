/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:37:32 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 08:41:23 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

const char	*g_cmds[] = {
	"!cd", "ls", "cd", "get", "put", "pwd", "quit", "help"};

static int	(*g_functions[]) (t_ftp *) = {
	&cmd_cd_local, &cmd_ls, &cmd_cd, &cmd_get, &cmd_put,
	&cmd_pwd, &cmd_quit, &cmd_help};

int	client_execute_shell_cmd(t_ftp *f)
{
	char	**argv;
	pid_t	pid;

	argv = ft_strsplit(&f->input[1], ' ');
	if ((pid = fork()) == -1)
	{
		ft_printf(E_FORK);
		return (0);
	}
	else if (pid == 0)
	{
		execvp(argv[0], argv);
		exit(0);
	}
	else
		wait4(pid, NULL, 0, NULL);
	destroy_char_array(argv);
	free(f->input);
	f->input = NULL;
	return (client_read_from_user(f));
}

int	client_send_raw(t_ftp *f)
{
	char	*cmd;

	cmd = ft_strjoin(&f->input[1], "\r\n");
	write(f->socket, cmd, ft_strlen(cmd));
	free(cmd);
	return (1);
}

int	client_execute_command(t_ftp *f)
{
	int	i;

	i = 0;
	while (i < CMD_COUNT)
	{
		if ((word(f->input, 0) != NULL) &&
				(ft_strnicmp(word(f->input, 0), g_cmds[i],
					ft_strlen(g_cmds[i])) == 0))
			return (g_functions[i](f));
		i++;
	}
	if (f->input[0] == '!')
		return (client_execute_shell_cmd(f));
	if (f->input[0] == '@')
		return (client_send_raw(f));
	ft_printf("Command not recognized.\n");
	return (client_read_from_user(f));
}
