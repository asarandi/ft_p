/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:41:40 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 10:05:17 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		count_char_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

void	destroy_char_array(char **array)
{
	int	count;
	int	i;

	if (array != NULL)
	{
		count = count_char_array(array);
		i = 0;
		while (i < count)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	return ;
}

char	**request_split(char *str)
{
	(void)whitespace_transform(str);
	(void)whitespace_consolidate(str);
	return (ft_strsplit(str, ' '));
}
