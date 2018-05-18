/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 02:02:26 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 08:56:49 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

const char	*cmds[] = {
	"SYST", "PASV", "PORT", "PWD", "CWD", "LIST", "STOR",
	"RETR", "USER", "PASS", "HELP", "MKD", "QUIT", "SIZE",
	"TYPE", "CDUP", "DELE", "RMD"};

static int	(*functions[]) (t_ftp *) = {
	&cmd_syst, &cmd_pasv, &cmd_port, &cmd_pwd, &cmd_cwd, &cmd_list, &cmd_stor,
	&cmd_retr, &cmd_user, &cmd_pass, &cmd_help, &cmd_mkd, &cmd_quit, &cmd_size,
	&cmd_type, &cmd_cdup, &cmd_dele, &cmd_rmd};

# define CMD_COUNT	18

t_ftp	*g_ftp;

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

int	ftp_send_text(t_ftp *f, int code, char *str)
{
	ft_printf("{blue}[%s:%d] send: {eoc}",
			f->client_addr, f->client_port);
	ft_printf("%d %s\r\n", code, str);
	return (ft_fprintf(f->client, "%d %s\r\n", code, str));
}

int	cmd_syst(t_ftp *f)
{
	(void)ftp_send_text(f, 215, "UNIX Type: L8");
	return (1);
}

int	cmd_pasv(t_ftp *f)
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

int	cmd_port(t_ftp *f)
{
	(void)ftp_send_text(f, 502, "PORT is not yet implemented, use PASV");
	return (1);
}

int	cmd_pwd(t_ftp *f)
{
	char	*str1;
	char	*str2;

	str1 = getcwd(NULL, 0);
	str2 = ft_strjoin("\"", str1);
	free(str1);
	str1 = ft_strjoin(str2, "\"");
	free(str2);
	(void)ftp_send_text(f, 257, str1);
	free(str1);
	return (1);
}

int	cmd_dele(t_ftp *f)
{
	if (unlink(f->req[1]) == 0)
	{
		(void)ftp_send_text(f, 250, "File deleted successfully.");
		return (1);
	}
	else
		(void)ftp_send_text(f, 550, "Failed to delete file.");
	return (0);
}

int	cmd_rmd(t_ftp *f)
{
	if (rmdir(f->req[1]) == 0)
	{
		(void)ftp_send_text(f, 250, "Directory removed successfully.");
		return (1);
	}
	else
		(void)ftp_send_text(f, 550, "Failed to remove directory.");
	return (0);
}

int	cmd_cwd(t_ftp *f)
{
	if (chdir(f->req[1]) == 0)
	{
		(void)ftp_send_text(f, 250, "Directory successfully changed.");
		return (1);
	}
	else
		(void)ftp_send_text(f, 550, "Failed to change directory.");
	return (0);
}

int	cmd_cdup(t_ftp *f)
{
	if (chdir("..") == 0)
	{
		(void)ftp_send_text(f, 250, "Directory successfully changed.");
		return (1);
	}
	else
		(void)ftp_send_text(f, 550, "Failed to change directory.");
	return (0);
}


int	cmd_list_fork(t_ftp *f)
{
	pid_t	pid;

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
		if ((f->req[1] != NULL) && (ft_strcmp(f->req[1], "-a") == 0))
			execl(f->ft_ls, f->ft_ls, "-la", f->req[2], NULL);
		else
			execl(f->ft_ls, f->ft_ls, "-l", f->req[1], NULL);
		exit(0);
	}
	else
		wait4(pid, NULL, 0, NULL);
	return (1);
}

void	passive_cleanup(t_ftp *f)
{
	close(f->passive->client);
	close(f->passive->socket);
	free(f->passive);
	f->use_passive = 0;
	return ;
}

int	cmd_list(t_ftp *f)
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

int	cmd_stor_receive(t_ftp *f)
{
	int		fd;
	char	buf[1024];
	ssize_t	buf_len;

	(void)ftp_send_text(f, 150, "Ok to send data.");
	fd = open(f->req[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		(void)ftp_send_text(f, 550, "Failed to open file.");
		return (0);
	}
	while ((buf_len = read(f->passive->client, buf, 1023)) > 0)
		write(fd, buf, buf_len);
	close(fd);
	if (buf_len < 0)
	{
		(void)ftp_send_text(f, 550, "Error writing file.");
		return (0);
	}
	else
		(void)ftp_send_text(f, 226, "Transfer complete.");
	return (1);
}

int	cmd_stor(t_ftp *f)
{
	if (f->use_passive == 1)
	{
		if (incoming_accept(f->passive) == 1)
		{
			(void)cmd_stor_receive(f);
		}
		else
			(void)ftp_send_text(f, 450, "File receive error.");
		passive_cleanup(f);
		return (1);
	}
	else
		(void)ftp_send_text(f, 425, "Use PORT or PASV first.");
	return (0);
}

char	*file_get_contents(char *filename)
{
	int			fd;
	struct stat	st;
	char		*data;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	data = NULL;
	if ((fstat(fd, &st)) == 0)
	{
		if ((data = ft_memalloc(st.st_size + 1)) == NULL)
		{
			(void)close(fd);
			return (NULL);
		}
		if ((read(fd, data, st.st_size)) != st.st_size)
		{
			free(data);
			data = NULL;
		}
	}
	(void)close(fd);
	return (data);
}

ssize_t	file_get_size(char *filename)
{
	int		fd;
	ssize_t	size;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	size = lseek(fd, 0, SEEK_END);
	close(fd);
	return (size);
}

int	cmd_retr(t_ftp *f)
{
	char	*data;

	if (f->use_passive == 1)
	{
		if (incoming_accept(f->passive) == 1)
		{
			if ((data = file_get_contents(f->req[1])) != NULL)
			{
				(void)ftp_send_text(f, 150, "Sending over file");
				write(f->passive->client, data, file_get_size(f->req[1]));
				free(data);
				(void)ftp_send_text(f, 226, "File sent successfully.");
			}
			else
				ftp_send_text(f, 550, "Failed to open file.");
		}
		else
			(void)ftp_send_text(f, 450, "File send error.");
		passive_cleanup(f);
		return (1);
	}
	else
		(void)ftp_send_text(f, 425, "Use PORT or PASV first.");
	return (0);
}

int	cmd_user(t_ftp *f)
{
	(void)ftp_send_text(f, 200, "OK");
	return (1);
}

int	cmd_pass(t_ftp *f)
{
	(void)ftp_send_text(f, 200, "OK");
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
		ft_printf(cmds[i]);
		ft_fprintf(f->client, cmds[i]);
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

int	cmd_mkd(t_ftp *f)
{
	if (mkdir(f->req[1], 0755) == 0)
	{
		(void)ftp_send_text(f, 250, "Directory created successfully.");
		return (1);
	}
	else
		(void)ftp_send_text(f, 550, "Failed to create directory.");
	return (0);
}

int	cmd_quit(t_ftp *f)
{
	(void)ftp_send_text(f, 221, "Goodbye.");
	close(f->client);
	return (1);
}

int	socket_create(t_ftp *f)
{
	f->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (f->socket == -1)
	{
		f->error = E_SOCKET;
		return (0);
	}
	return (1);
}

int	socket_options(t_ftp *f)
{
	int	o1;
	int o2;

	f->opt = 1;
	o1 = setsockopt(f->socket, SOL_SOCKET, SO_REUSEADDR,
			&f->opt, sizeof(f->opt));
	o2 = setsockopt(f->socket, SOL_SOCKET, SO_REUSEPORT,
			&f->opt, sizeof(f->opt));
	if ((o1 == -1) || (o2 == -1))
	{
		close(f->socket);
		f->error = E_SETSOCKOPT;
		return (0);
	}
	return (1);
}

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

int	socket_listen(t_ftp *f)
{
	if (listen(f->socket, 1) == -1)
	{
		close(f->socket);
		f->error = E_LISTEN;
		return (0);
	}
	return (1);
}

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

char	**request_split(char *str)
{
	(void)whitespace_transform(str);
	(void)whitespace_consolidate(str);
	return (ft_strsplit(str, ' '));
}

int	cmd_size(t_ftp *f)
{
	ssize_t	size;

	size = file_get_size(f->req[1]);
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

void	server_init(t_ftp *f)
{
	f->home = getcwd(NULL, 0);
	if (f->home[ft_strlen(f->home) - 1] != '/')
		f->ft_ls = ft_strjoin(f->home, "/ft_ls/ft_ls");
	else
		f->ft_ls = ft_strjoin(f->home, "ft_ls/ft_ls");
	if (incoming_create(f) != 1)
		server_exit(f, f->error, EXIT_FAILURE);
	ft_printf("server started, listening on %s:%d\n",
			inet_ntoa(f->address.sin_addr),
			ntohs(f->address.sin_port));
	(void)signal(SIGINT, sigint_handler);
	g_ftp = f;
	return ;
}

int	server_loop(t_ftp *f)
{
	int		i;

	(void)ft_bzero(f->buf, sizeof(f->buf));
	if ((f->buf_len = recv(f->client, f->buf, sizeof(f->buf), 0)) <= 0)
		return (0);
	(void)ft_printf("{green}[%s:%d] recv: {eoc}",
			f->client_addr, f->client_port);
	(void)write(STDOUT_FILENO, f->buf, f->buf_len);
	if ((f->req = request_split(f->buf)) == NULL)
		return (1);
	i = 0;
	while (i < CMD_COUNT)
	{
		if (ft_strcmp(f->req[0], cmds[i]) == 0)
		{
			(void)functions[i](f);
			break ;
		}
		i++;
	}
	if (i == CMD_COUNT)
		(void)ftp_send_text(f, 502, "Command not implemented.");
	(void)destroy_char_array(f->req);
	return (1);
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

void	server_show_usage(t_ftp *f)
{
	ft_printf("welcome to %s\n", FTP_SERVER_NAME);
	ft_printf("usage:\t%s <ip.ad.dr.es> <port>\n", f->argv[0]);
	ft_printf(" or\t%s <port>\n", f->argv[0]);
	ft_printf(" or\t%s\n", f->argv[0]);
	server_exit(f, "", 0);
}

void	server_parse(t_ftp *f, int argc, char **argv, char **envp)
{
	int	i;

	f->argc = argc;
	f->argv = argv;
	f->envp = envp;
	if (f->argc > 3)
		server_show_usage(f);
	i = 1;
	while (i < f->argc)
	{
		if ((ft_strcmp(f->argv[i], "-h") == 0) ||
				(ft_strcmp(f->argv[i], "--help") == 0))
			server_show_usage(f);
		i++;
	}
	f->listen_addr = LISTEN_ADDR;
	f->listen_port = LISTEN_PORT;
	if (f->argc == 2)
		f->listen_port = ft_atoi(f->argv[1]);
	if (f->argc == 3)
	{
		if (ft_strcmp(f->argv[1], "localhost") != 0)
			f->listen_addr = f->argv[1];
		f->listen_port = ft_atoi(f->argv[2]);
	}
}

void	server_start(int argc, char **argv, char **envp)
{
	t_ftp	*f;

	f = ft_memalloc(sizeof(t_ftp));
	f->running = 1;
	server_parse(f, argc, argv, envp);
	server_init(f);
	server_accept(f);
	server_fork(f);
	while (f->running == 1)
	{
		if (server_loop(f) == 0)
		{
			ft_printf("{red}closed connection to: %s:%d{eoc}\n",
			f->client_addr, f->client_port);
			close(f->client);
			server_accept(f);
		}
	}
	close(f->client);
	close(f->socket);
	server_cleanup(f);
}

int	main(int argc, char **argv, char **envp)
{
	server_start(argc, argv, envp);
	return (0);
}
