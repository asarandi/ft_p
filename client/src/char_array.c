/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 21:30:50 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 21:31:36 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	*char_array_find_paren(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		if (array[i][0] == '(')
			return (array[i]);
		i++;
	}
	return (NULL);
}

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
