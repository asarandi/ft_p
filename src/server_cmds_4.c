/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmds_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:31:25 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 09:31:34 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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

int	cmd_syst(t_ftp *f)
{
	(void)ftp_send_text(f, 215, "UNIX Type: L8");
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
