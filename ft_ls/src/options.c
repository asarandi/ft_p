/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:29:57 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:58:46 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	illegal_option(char c)
{
	ft_fprintf(2, "%s: illegal option -- %c\n", g_ls_name, c);
	ft_fprintf(2, "usage: %s [-AaCcFfglopRrSTtUux1] [file ...]\n", g_ls_name);
	exit(1);
}

int		parse_options6(char c)
{
	if (c == 'a')
	{
		g_opt.show_dot = 1;
		return (1);
	}
	else if (c == '1')
	{
		g_opt.basic = 1;
		g_opt.long_list = 0;
		g_opt.across = 0;
		g_opt.column = 0;
		return (1);
	}
	return (0);
}

int		parse_options5(char c)
{
	if (c == 'x')
	{
		g_opt.across = 1;
		g_opt.long_list = 0;
		g_opt.column = 0;
		g_opt.basic = 0;
		return (1);
	}
	else if (c == 'C')
	{
		g_opt.column = 1;
		g_opt.long_list = 0;
		g_opt.across = 0;
		g_opt.basic = 0;
		return (1);
	}
	return (parse_options6(c));
}

/*
**int	parse_options7(char c)
**{
**	if (c == 'e')
**	{
**		g_opt.show_acl = 1;
**		return (1);
**	}
**	else if (c == '@')
**	{
**		g_opt.show_extattr = 1;
**		return (1);
**	}
**	else if (c == 'd')
**	{
**		g_opt.plain = 1;
**		return (1);
**	}
**	else if (c == 'G')
**	{
**		g_opt.colors = 1;
**		return (1);
**	}
**	return (0);
**}
*/

int		check_all_options(char c)
{
	if (parse_options1(c) == 1)
		return (1);
	else
		(void)illegal_option(c);
	return (0);
}

void	parse_cmdline(int ac, char **av)
{
	int			i;
	int			k;

	g_opt.last_opt = 1;
	(void)clear_options();
	i = 1;
	while (i < ac)
	{
		while ((av[i]) && (av[i][0] == '-'))
		{
			if ((av[i][1] == '-') && (av[i][2] == 0))
			{
				g_opt.last_opt = ++i;
				return ;
			}
			k = 1;
			while (av[i][k])
				(void)check_all_options(av[i][k++]);
			i++;
			g_opt.last_opt = i;
		}
		return ;
	}
}
