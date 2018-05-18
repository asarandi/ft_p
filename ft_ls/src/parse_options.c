/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 21:56:01 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/05 02:42:58 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	parse_options1(char c)
{
	if (c == 'l')
	{
		g_opt.long_list = 1;
		g_opt.basic = 0;
		g_opt.column = 0;
		g_opt.across = 0;
		return (1);
	}
	else if (c == 'R')
	{
		g_opt.recursive = 1;
		return (1);
	}
	else if (c == 'r')
	{
		g_opt.reverse = 1;
		return (1);
	}
	return (parse_options2(c));
}

int	parse_options2(char c)
{
	if (c == 'A')
	{
		g_opt.show_hidden = 1;
		return (1);
	}
	else if (c == 'S')
	{
		g_opt.sort = 4;
		return (1);
	}
	else if (c == 'u')
	{
		g_opt.time = 1;
		return (1);
	}
	else if (c == 'U')
	{
		g_opt.time = 2;
		return (1);
	}
	return (parse_options3(c));
}

int	parse_options3(char c)
{
	if (c == 'c')
	{
		g_opt.time = 3;
		return (1);
	}
	else if (c == 'T')
	{
		g_opt.fulltime = 1;
		return (1);
	}
	else if (c == 't')
	{
		if (g_opt.sort != 4)
			g_opt.sort = 1;
		return (1);
	}
	else if (c == 'f')
	{
		g_opt.sort = -1;
		g_opt.show_dot = 1;
		return (1);
	}
	return (parse_options4(c));
}

int	parse_options4(char c)
{
	if (c == 'F')
	{
		g_opt.symbol = 1;
		g_opt.slash = 0;
		return (1);
	}
	else if (c == 'p')
	{
		g_opt.slash = 1;
		g_opt.symbol = 0;
		return (1);
	}
	else if (c == 'g')
	{
		g_opt.hide_owner = 1;
		return (parse_options1('l'));
	}
	else if (c == 'o')
	{
		g_opt.hide_group = 1;
		return (parse_options1('l'));
	}
	return (parse_options5(c));
}
