/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 02:02:26 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 10:21:47 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
The client must understand the following commands:
• ls : list in the current server’s directory.
• cd : change the current server’s directory.
• get _file_ : download the file _file_ from the server to the client.
• put _file_ : upload the file _file_ from the client to the server.
• pwd : display the path of the current server’s directory.
• quit : cuts the connection + exit the program.
and meet the following requirements:
• A specific prompts to the client (to distinguish it from Shell).
• Impossibility to lower to a level inferior to the server’s executable dirctry
(unless a parameter specified to the server indicates another start directory).
• Display on the client of SUCCESS or ERROR messages + explanation after each
request.
*/

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_printf("client\n");
	return (0);
}
