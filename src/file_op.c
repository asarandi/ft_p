/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:33:16 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 09:33:42 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*file_get_contents(char *filename)
{
	int			fd;
	struct stat	st;
	char		*data;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	data = NULL;
	if ((fstat(fd, &st)) == 0)
	{
		if ((data = ft_memalloc(st.st_size + 1)) == NULL)
		{
			(void)close(fd);
			return (NULL);
		}
		if ((read(fd, data, st.st_size)) != st.st_size)
		{
			free(data);
			data = NULL;
		}
	}
	(void)close(fd);
	return (data);
}

ssize_t	file_get_size(char *filename)
{
	int		fd;
	ssize_t	size;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	size = lseek(fd, 0, SEEK_END);
	close(fd);
	return (size);
}
