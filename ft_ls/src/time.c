/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:44:43 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/03 18:44:47 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*make_time_string(struct timespec ts)
{
	time_t	now;
	char	*result;
	int		i;

	now = time(&now);
	result = ctime(&ts.tv_sec);
	if ((ts.tv_sec + ((365 / 2) * 86400) < now) ||
			(now + ((365 / 2) * 86400) < ts.tv_sec))
	{
		i = 0;
		while (i < 5)
		{
			result[11 + i] = result[19 + i];
			i++;
		}
	}
	return (&result[4]);
}
