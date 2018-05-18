/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symlink.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:50:10 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:57:30 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_symlink_address(char *path, t_file *list)
{
	char	*symlink;
	char	*fullpath;

	if ((fullpath = ft_strjoin(path, list->name)) == NULL)
		return (NULL);
	if ((symlink = ft_memalloc(PATH_MAX)) == NULL)
	{
		free(fullpath);
		return (NULL);
	}
	if ((readlink(fullpath, symlink, PATH_MAX)) == -1)
	{
		free(symlink);
		free(fullpath);
		return (NULL);
	}
	free(fullpath);
	return (symlink);
}

void	print_symlink(t_file *list, char *path)
{
	char	*symlink;

	if (S_ISLNK(list->st.st_mode))
	{
		symlink = get_symlink_address(path, list);
		if (symlink != NULL)
		{
			ft_fprintf(1, " -> %s", symlink);
			free(symlink);
		}
	}
}
