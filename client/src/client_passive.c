/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_passive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:35:32 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:55:06 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
	while (g_ftp->running == 1)
	{
		ft_bzero(p->buf, sizeof(p->buf));
		p->buf_len = read(p->socket, p->buf, sizeof(p->buf) - 1);
		if (p->buf_len <= 0)
			break ;
		write(p->passive_output_fd, p->buf, p->buf_len);
	}
	if (g_ftp->running == 0)
		ft_printf("{red}aborted{eoc}\n");
	return (1);
}

int	client_init_passive(t_ftp *f)
{
	if (client_parse_passive(f) != 1)
		return (0);
	f->passive = ft_memalloc(sizeof(struct s_ftp));
	f->passive->connect_addr = f->passive_ip;
	f->passive->connect_port = f->passive_port;
	if (socket_connect(f->passive) != 1)
	{
		free(f->passive);
		f->passive = NULL;
		return (0);
	}
	f->use_passive = 1;
	if (f->passive_cmd == 1)
		(void)cmd_ls_2(f);
	else if (f->passive_cmd == 2)
		(void)cmd_get_2(f);
	else if (f->passive_cmd == 3)
		(void)cmd_put_2(f);
	else
		(void)client_read_from_user(f);
	(void)client_read_from_server(f);
	return (1);
}

int	client_passive_data(t_ftp *f)
{
	if (f->passive_cmd == 1)
		cmd_ls_3(f);
	else if (f->passive_cmd == 2)
		cmd_get_3(f);
	else if (f->passive_cmd == 3)
		cmd_put_3(f);
	else
		(void)client_read_from_user(f);
	return (client_read_from_server(f));
}
