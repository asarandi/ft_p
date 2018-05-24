/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_stor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:56:34 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 18:56:51 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	cmd_stor_receive(t_ftp *f)
{
	int		fd;
	char	buf[1024];
	ssize_t	buf_len;

	(void)ftp_send_text(f, 150, "Ok to send data.");
	fd = open(word(f->buf, 1), O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
			if (ip_matches(f) == 1)
			{
				(void)cmd_stor_receive(f);
			}
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
