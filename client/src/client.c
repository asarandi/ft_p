/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 02:02:26 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 21:17:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_ftp	*g_ftp;

char	*word(char *str, int index)
{
	int	i;
	int	word;

	if (str == NULL)
		return (NULL);
	i = 0;
	word = 0;
	while (str[i])
	{
		while ((str[i]) && (ft_isspace(str[i])))
			i++;
		if ((str[i]) && (word == index))
			return (&str[i]);
		if (str[i] == 0)
			return (NULL);
		word++;
		while ((str[i]) && (!ft_isspace(str[i])))
			i++;
	}
	return (NULL);
}

int		count_char_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

void	destroy_char_array(char **array)
{
	int	count;
	int	i;

	if (array != NULL)
	{
		count = count_char_array(array);
		i = 0;
		while (i < count)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	return ;
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_fprintf(STDERR_FILENO, "Terminating client...\n");
		g_ftp->running = 0;
		close(g_ftp->socket);
	}
}


void	client_cleanup(t_ftp *f)
{
	close(f->socket);
	if (f->passive_ip != NULL)
		free(f->passive_ip);
	if (f->passive_port != NULL)
		free(f->passive_port);
	if (f->passive != NULL)
		free(f->passive);
	if (f->req != NULL)
		destroy_char_array(f->req);
	if (f->home != NULL)
		free(f->home);
	if (f->res0 != NULL)
		freeaddrinfo(f->res0);
	free(f);
	return ;
}

void	client_exit(t_ftp *f, char *msg, int exit_code)
{
	if (f->running)
		ft_printf(msg);
	(void)client_cleanup(f);
	exit(exit_code);
}

int	socket_connect(t_ftp *f)
{
	struct	sockaddr_in	*in;

	f->hints.ai_family = PF_UNSPEC;
	f->hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(f->connect_addr, f->connect_port, &f->hints, &f->res0) != 0)
	{
		f->error = E_GETADDRINFO;
		return (0);
	}
	f->res = f->res0;
	while (f->res != NULL)
	{
		f->socket = socket(f->res->ai_family,
				f->res->ai_socktype, f->res->ai_protocol);
		if (f->socket != -1)
		{
			in = (struct sockaddr_in *)f->res->ai_addr;
			if (connect(f->socket, f->res->ai_addr, f->res->ai_addrlen) != -1)
				return (1);
			close(f->socket);
		}
		f->res = f->res->ai_next;
	}
	freeaddrinfo(f->res0);
	f->res0 = NULL;
	f->error = E_CONNECT;
	return (0);
}

void	client_connect(t_ftp *f)
{
	struct	sockaddr_in	*in;

	f->home = getcwd(NULL, 0);
	f->bin_ls = BIN_LS;
	ft_printf("{yellow}attempting connection ... {eoc}");
	if (socket_connect(f) != 1)
		client_exit(f, f->error, EXIT_FAILURE);
	in = (struct sockaddr_in *)f->res->ai_addr;
	f->print_addr = inet_ntoa(in->sin_addr);
	f->print_port = ntohs(in->sin_port);
	ft_printf("{yellow}connected to %s:%d{eoc}\n", f->print_addr, f->print_port);
	(void)signal(SIGINT, sigint_handler);
	g_ftp = f;
	return ;
}


void	client_show_usage(t_ftp *f)
{
	ft_printf("welcome to %s\n", FTP_CLIENT_NAME);
	ft_printf("usage:\t%s <ip.ad.dr.es> <port>\n", f->argv[0]);
	ft_printf(" or\t%s <port>\n", f->argv[0]);
	ft_printf(" or\t%s\n", f->argv[0]);
	client_exit(f, "", 0);
}

void	client_parse(t_ftp *f, int argc, char **argv, char **envp)
{
	int	i;

	f->argc = argc;
	f->argv = argv;
	f->envp = envp;
	if (f->argc > 3)
		client_show_usage(f);
	i = 1;
	while (i < f->argc)
	{
		if ((ft_strcmp(f->argv[i], "-h") == 0) ||
				(ft_strcmp(f->argv[i], "--help") == 0))
			client_show_usage(f);
		i++;
	}
	f->connect_addr = CONNECT_ADDR;
	f->connect_port = CONNECT_PORT;
	if (f->argc == 2)
	{
		f->connect_port = PORT_21;
		f->connect_addr = f->argv[1];
	}
	if (f->argc == 3)
	{
		f->connect_addr = f->argv[1];
		f->connect_port = f->argv[2];
	}
}

int	client_read_from_server(t_ftp *f)
{
	int	flag;
	int	i;
	int	r;

	(void)ft_printf("{cyan}[%s:%d]: {eoc}",
			f->print_addr, f->print_port);
	flag = 0;
	i = 0;
	(void)ft_bzero(f->buf, sizeof(f->buf));
	while (flag != 5)
	{
		r = recv(f->socket, &f->buf[i], 1, 0);
		if (r <= 0)
			return (0);
		write(STDOUT_FILENO, &f->buf[i], 1);
		if ((i < 3) && (ft_isdigit(f->buf[i])))
			flag++;
		if ((i == 3) && (flag == 3))
		{
			if (ft_isspace(f->buf[i]))
				flag++;
			else
				flag = 0;
		}
		if (f->buf[i] == '\n')
		{
			if (flag == 4)
				flag++;
			else
			{
				flag = 0;
				i = -1;
				(void)ft_bzero(f->buf, sizeof(f->buf));
			}
		}
		i++;
	}
	return (1);
}

int	cmd_pasv(t_ftp *f)
{
	(void)client_read_from_server(f);
	return (ft_atoi(word(f->buf, 0)));
}

int cmd_cd_local(t_ftp *f)
{
	if (chdir(word(f->input, 1)) == 0)
	{
		(void)ft_printf("Directory successfully changed.\n");
		return (1);
	}
	else
		(void)ft_printf("Failed to change directory.\n");
	return (0);
}

int cmd_cd(t_ftp *f)
{
	char	*str1;
	char	*str2;

	if (word(f->input, 1) == NULL)
	{
		ft_printf("Please specify directory name.\n");
		return (0);
	}
	str1 = ft_strdup("CWD");
	str2 = ft_strjoin(str1, " ");
	free(str1);
	str1 = ft_strjoin(str2, word(f->input, 1));
	free(str2);
	str2 = ft_strjoin(str1, "\r\n");
	write(f->socket, str2, ft_strlen(str2));
	free(str2);
	return (1);

}

int	cmd_ls(t_ftp *f)
{
	write(f->socket, "PASV\r\n", 6);
	f->passive_cmd = 1;
	return (1);
}

int cmd_ls_2(t_ftp *f)
{
	char	*str1;
	char	*str2;

	str1 = ft_strdup("LIST");
	if (word(f->input, 1) != NULL)
	{
		str2 = ft_strjoin(str1, " ");
		free(str1);
		str1 = ft_strjoin(str2, word(f->input, 1));
		free(str2);
	}
	str2 = ft_strjoin(str1, "\r\n");
	write(f->socket, str2, ft_strlen(str2));
	free(str2);
	return (1);
}

int	cmd_get(t_ftp *f)
{
	write(f->socket, "PASV\r\n", 6);
	f->passive_cmd = 2;
	return (1);
}

int cmd_get_2(t_ftp *f)
{
	char	*str1;
	char	*str2;

	str1 = ft_strdup("RETR");
	str2 = ft_strjoin(str1, " ");
	free(str1);
	str1 = ft_strjoin(str2, word(f->input, 1));
	free(str2);
	str2 = ft_strjoin(str1, "\r\n");
	write(f->socket, str2, ft_strlen(str2));
	free(str2);
	f->passive_file = ft_strdup(word(f->input, 1));
	return (1);
}

int	cmd_put(t_ftp *f)
{
	write(f->socket, "PASV\r\n", 6);
	f->passive_cmd = 3;
	return (1);
}

int cmd_put_2(t_ftp *f)
{
	char	*str1;
	char	*str2;

	str1 = ft_strdup("STOR");
	str2 = ft_strjoin(str1, " ");
	free(str1);
	str1 = ft_strjoin(str2, word(f->input, 1));
	free(str2);
	str2 = ft_strjoin(str1, "\r\n");
	write(f->socket, str2, ft_strlen(str2));
	free(str2);
	f->passive_file = ft_strdup(word(f->input, 1));
	return (1);
}

int cmd_pwd(t_ftp *f)
{
	write(f->socket, "PWD\r\n", 5);
	return (1);
}

int cmd_quit(t_ftp *f)
{
	write(f->socket, "QUIT\r\n", 6);
	close(f->socket);
	client_exit(f, "bye!\n", EXIT_SUCCESS);
	return (0);
}

const char	*g_cmds[] = {
	"!cd", "ls", "cd", "get", "put", "pwd", "quit"};

static int	(*g_functions[]) (t_ftp *) = {
	&cmd_cd_local, &cmd_ls, &cmd_cd, &cmd_get, &cmd_put, &cmd_pwd, &cmd_quit};


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
		execv(argv[0], argv);
		exit(0);
	}
	else
		wait4(pid, NULL, 0, NULL);
	destroy_char_array(argv);
	return (1);
}

int	client_send_raw(t_ftp *f)
{
	char	*cmd;

	cmd = ft_strjoin(&f->input[1], "\r\n");
	write(f->socket, cmd, ft_strlen(cmd));
	free(cmd);
	return (1);
}

int	client_read_from_user(t_ftp *f)
{
	(void)ft_printf("{magenta}%s {eoc}", CLIENT_PROMPT);
	while (get_next_line(STDIN_FILENO, &f->input) > 0)
	{
		if (ft_strlen(f->input) > 0)
		{
			(void)client_execute_command(f);
			free(f->input);
			return (1);
		}
		free(f->input);
		continue ;
	}
	return (0);
}

int	client_execute_command(t_ftp *f)
{
	int	i;

	i = 0;
	while (i < CMD_COUNT)
	{
		if (ft_strnicmp(word(f->input, 0), g_cmds[i],
					ft_strlen(g_cmds[i])) == 0)
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

int	str_char_count(char *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	str_char_replace(char *str, char a, char b)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			str[i] = b;
		i++;
	}
	return (1);
}

char	*str_char_index(char *str, char c, int index)
{
	int	i;
	int	k;

	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (k == index)
				return (&str[i]);
			k++;
		}
		i++;
	}
	return (NULL);
}

char	*char_array_find_paren(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		if (array[i][0] == '(')
			return (array[i]);
		i++;
	}
	return (NULL);
}

int	client_parse_passive(t_ftp *f)
{
	char	*port;
	int		p;

	if ((f->passive_ip = ft_strrchr(f->buf, '(')) == NULL)
		return (0);
	f->passive_ip++;
	if (ft_strchr(f->passive_ip, ')') != NULL)
	{
		ft_strchr(f->passive_ip, ')')[0] = 0;
		if (str_char_count(f->passive_ip, ',') == 5)
		{
			str_char_replace(f->passive_ip, ',', '.');
			port = &str_char_index(f->passive_ip, '.', 3)[1];
			port[-1] = 0;
			p = ft_atoi(port) * 256 + ft_atoi(&ft_strchr(port, '.')[1]);
			f->passive_port = ft_itoa(p);
			f->passive_ip = ft_strdup(f->passive_ip);
			return (1);				
		}
	}
	return (0);
}

int	client_read_passive(t_ftp *p)
{
	while (1)
	{
		ft_bzero(p->buf, sizeof(p->buf));
		p->buf_len = read(p->socket, p->buf, sizeof(p->buf) - 1);
		if (p->buf_len <= 0)
			break ;
		write(p->passive_output_fd, p->buf, p->buf_len);
	}
	return (1);
}

int	client_loop(t_ftp *f)
{
	int	code;

	if (client_read_from_user(f) != 1)
		return (0);
	if (client_read_from_server(f) != 1)
		return (0);
	if ((code = ft_atoi(f->buf)) == 227)
	{
		if (client_parse_passive(f) != 1)
			return (0);
		f->passive = ft_memalloc(sizeof(struct s_ftp));
		f->passive->connect_addr = f->passive_ip;
		f->passive->connect_port = f->passive_port;
		f->use_passive = 1;
		if (socket_connect(f->passive) != 1)
			return (0);
		if (f->passive_cmd == 1)
			(void)cmd_ls_2(f);
		else if (f->passive_cmd == 2)
			(void)cmd_get_2(f);
		else if (f->passive_cmd == 3)
			(void)cmd_put_2(f);
		(void)client_read_from_server(f);
	}
	if ((code = ft_atoi(f->buf)) == 150)
	{
		f->passive->passive_output_fd = STDOUT_FILENO;
		client_read_passive(f->passive);
		if (client_read_from_server(f) != 1)
			return (0);
	}
	return (1);
}

void	client_start(int argc, char **argv, char **envp)
{
	t_ftp	*f;

	f = ft_memalloc(sizeof(t_ftp));
	f->running = 1;
	g_ftp = f;
	client_parse(f, argc, argv, envp);
	client_connect(f);
	(void)client_read_from_server(f);
	while (f->running == 1)
	{
		if (client_loop(f) == 0)
		{
			ft_printf("{red}closed connection to: %s:%d{eoc}\n",
			f->print_addr, f->print_port);
			break ;
		}
	}
	close(f->client);
	close(f->socket);
	client_cleanup(f);
}

int		main(int argc, char **argv, char **envp)
{
	client_start(argc, argv, envp);
	return (0);
}
