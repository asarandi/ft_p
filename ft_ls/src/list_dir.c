/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:36:29 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:59:16 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_allowed(char *fn)
{
	int	allowed;

	allowed = 1;
	if (fn[0] == '.')
	{
		allowed = 0;
		if (g_opt.show_hidden == 1)
		{
			if ((ft_strcmp(fn, ".")) == 0)
				allowed = 0;
			else if ((ft_strcmp(fn, "..")) == 0)
				allowed = 0;
			else
				allowed = 1;
		}
		if (g_opt.show_dot == 1)
			allowed = 1;
	}
	return (allowed);
}

void	destroy_list(t_file *list)
{
	t_file	*next;

	while (1)
	{
		next = list->next;
		free(list->name);
		free(list);
		if (next == NULL)
			break ;
		list = next;
	}
	return ;
}

t_file	*create_element(char *name, char *path)
{
	t_file	*new;

	if (is_allowed(name) == 1)
	{
		new = (t_file*)ft_memalloc(sizeof(t_file));
		new->name = ft_strdup(name);
		if (get_file_stats(path, new) == -1)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
		return (new);
	}
	else
		return (NULL);
}

t_file	*create_list(char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			*first;
	t_file			*index;
	t_file			*new;

	first = NULL;
	new = NULL;
	errno = 0;
	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	while ((dp = readdir(dirp)) != NULL)
	{
		new = create_element(dp->d_name, path);
		if ((first == NULL) && (new != NULL))
			parent_node(&first, &index, new);
		else if (new != NULL)
			child_node(&index, new);
	}
	index = NULL;
	closedir(dirp);
	return (first);
}

void	list_directory(char *path)
{
	t_file	*list;
	t_file	*start;
	char	*subdir;

	list = create_list(path);
	if (list != NULL)
	{
		listdir_sortprint(&list, path, &start);
		if (g_opt.recursive == 1)
		{
			while (list)
			{
				subdir = ft_strjoin(path, list->name);
				if ((is_directory(subdir, 0)) && (ok_to_recurse(list->name)))
					listdir_nextsubdir(&subdir);
				free(subdir);
				list = list->next;
			}
		}
		destroy_list(start);
	}
	else if (errno)
		ft_fprintf(2, "%s: %s: %s\n", g_ls_name, path, strerror(errno));
}
