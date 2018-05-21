/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:28:39 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:52:50 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	client_read_flag_util(t_ftp *f, int *i, int *flag)
{
	if ((*i < 3) && (ft_isdigit(f->buf[*i])))
		(*flag)++;
	if ((*i == 3) && (*flag == 3))
	{
		if (ft_isspace(f->buf[*i]))
			(*flag)++;
		else
			(*flag) = 0;
	}
	if (f->buf[*i] == '\n')
	{
		if (*flag == 4)
			(*flag)++;
		else
		{
			(*flag) = 0;
			(*i) = -1;
			(void)ft_bzero(f->buf, sizeof(f->buf));
		}
	}
	return (1);
}

int	client_read_from_server(t_ftp *f)
{
	int	flag;
	int	i;

	(void)ft_printf("{cyan}[%s:%d]: {eoc}",
			f->print_addr, f->print_port);
	flag = 0;
	i = 0;
	(void)ft_bzero(f->buf, sizeof(f->buf));
	while (flag != 5)
	{
		if (recv(f->socket, &f->buf[i], 1, 0) <= 0)
			return (0);
		write(STDOUT_FILENO, &f->buf[i], 1);
		(void)client_read_flag_util(f, &i, &flag);
		i++;
	}
	f->response_code = ft_atoi(word(f->buf, 0));
	return (1);
}

int	client_read_from_user(t_ftp *f)
{
	(void)ft_printf("{magenta}%s {eoc}", CLIENT_PROMPT);
	while ((get_next_line(STDIN_FILENO, &f->input) > 0) && (f->running == 1))
	{
		if (ft_strlen(f->input) > 0)
		{
			(void)client_execute_command(f);
			if (f->input != NULL)
			{
				free(f->input);
				f->input = NULL;
			}
			return (1);
		}
		free(f->input);
		continue ;
	}
	return (0);
}
