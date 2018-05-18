/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:41:19 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:57:58 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	directory_add_slash(char **path)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*path);
	if ((*(*path)) && ((*path)[len - 1] != '/'))
	{
		tmp = ft_strjoin(*path, "/");
		free((*path));
		(*path) = tmp;
	}
}

int		is_directory(char *path, int show_error)
{
	struct stat	st;
	int			r;

	r = lstat(path, &st);
	if (r == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (1);
		else
			return (0);
	}
	if (show_error == 1)
		ft_fprintf(2, "%s: %s: %s\n", g_ls_name, path, strerror(errno));
	return (0);
}

int		ok_to_recurse(char *path)
{
	if (ft_strcmp(path, ".") == 0)
		return (0);
	if (ft_strcmp(path, "..") == 0)
		return (0);
	return (1);
}
