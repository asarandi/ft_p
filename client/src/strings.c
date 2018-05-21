/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:29:58 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:32:13 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	*word(char *str, int index)
{
	int	i;
	int	word;

	if (str == NULL)
		return (NULL);
	i = 0;
	word = 0;
	while (str[i])
	{
		while ((str[i]) && (ft_isspace(str[i])))
			i++;
		if ((str[i]) && (word == index))
			return (&str[i]);
		if (str[i] == 0)
			return (NULL);
		word++;
		while ((str[i]) && (!ft_isspace(str[i])))
			i++;
	}
	return (NULL);
}

int		str_char_count(char *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int		str_char_replace(char *str, char a, char b)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			str[i] = b;
		i++;
	}
	return (1);
}

char	*str_char_index(char *str, char c, int index)
{
	int	i;
	int	k;

	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (k == index)
				return (&str[i]);
			k++;
		}
		i++;
	}
	return (NULL);
}
