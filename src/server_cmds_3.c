/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmds_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:25:41 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 09:30:35 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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
