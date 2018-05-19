/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 05:10:49 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 04:22:44 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	whitespace_transform(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			str[i] = ' ';
		i++;
	}
}

void	string_shift_left(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return ;
}

void	whitespace_consolidate(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((ft_isspace(str[i])) && (ft_isspace(str[i + 1])))
		{
			string_shift_left(&str[i]);
			i = 0;
			continue ;
		}
		i++;
	}
}
