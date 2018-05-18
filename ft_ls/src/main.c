/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:02:16 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/03 22:01:38 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	int			mixed_input;

	g_ls_name = av[0];
	if ((av[0][0] == '.') && (av[0][1] == '/'))
		g_ls_name = &av[0][2];
	parse_cmdline(ac, av);
	if (!av[g_opt.last_opt])
	{
		g_opt.last_opt -= 1;
		av[g_opt.last_opt][0] = '.';
		av[g_opt.last_opt][1] = 0;
	}
	choose_sort();
	mixed_input = display_files(ac, av);
	display_directories(ac, av, mixed_input);
	return (0);
}
