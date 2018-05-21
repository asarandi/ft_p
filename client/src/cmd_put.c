/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:33:45 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:52:24 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	cmd_put(t_ftp *f)
{
	if (f->input_copy != NULL)
	{
		free(f->input_copy);
	}
	f->input_copy = ft_strdup(f->input);
	write(f->socket, "PASV\r\n", 6);
	f->passive_cmd = 3;
	return (1);
}

int	cmd_put_2(t_ftp *f)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin("STOR ", word(f->input_copy, 1));
	str2 = ft_strjoin(str1, "\r\n");
	free(str1);
	write(f->socket, str2, ft_strlen(str2));
	free(str2);
	f->passive_file = ft_strdup(word(f->input_copy, 1));
	free(f->input_copy);
	f->input_copy = NULL;
	return (1);
}

int	cmd_put_3(t_ftp *f)
{
	int		fd;
	char	c;

	if ((fd = open(f->passive_file, O_RDONLY)) > 0)
	{
		ft_printf("{green}uploading file to remote folder ... {eoc}");
		while ((read(fd, &c, 1) > 0) && (f->running == 1))
			write(f->passive->socket, &c, 1);
		close(fd);
		if (f->running == 0)
			ft_printf("{red}aborted{eoc}\n");
		else
			ft_printf("{green}done{eoc}\n");
	}
	else
		ft_printf("{red}error opening file ..\n");
	close(f->passive->socket);
	if (f->passive_file != NULL)
		free(f->passive_file);
	f->passive_file = NULL;
	f->passive_cmd = 0;
	return (1);
}
