/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:57:08 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 18:57:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	cmd_retr_write(t_ftp *f, char *data)
{
	(void)ftp_send_text(f, 150, "Sending over file");
	write(f->passive->client, data, file_get_size(word(f->buf, 1)));
	free(data);
	(void)ftp_send_text(f, 226, "File sent successfully.");
	return (1);
}

int	cmd_retr(t_ftp *f)
{
	char	*data;

	if (f->use_passive == 1)
	{
		if (incoming_accept(f->passive) == 1)
		{
			if (ip_matches(f) == 1)
			{
				if ((data = file_get_contents(word(f->buf, 1))) != NULL)
					(void)cmd_retr_write(f, data);
				else
					ftp_send_text(f, 550, "Failed to open file.");
			}
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
