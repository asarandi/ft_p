/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:26:01 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:55:41 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_file_stats(char *path, t_file *file)
{
	char	*fullpath;
	int		result;

	fullpath = ft_strjoin(path, file->name);
	result = lstat(fullpath, &file->st);
	free(fullpath);
	if (result == -1)
		ft_fprintf(2, "%s: %s: %s\n", g_ls_name, file->name, strerror(errno));
	return (result);
}

t_file	*cmdline_file(char *name)
{
	t_file	*new;

	if (is_directory(name, 0) == 0)
	{
		new = (t_file*)ft_memalloc(sizeof(t_file));
		if (new == NULL)
		{
			ft_fprintf(2, "%s: %s\n", g_ls_name, strerror(errno));
			exit(1);
		}
		new->name = ft_strdup(name);
		if (get_file_stats("", new) != 0)
		{
			free(new->name);
			free(new);
			return (NULL);
		}
		else
			return (new);
	}
	else
		return (NULL);
}

t_file	*build_file_list(int ac, char **av)
{
	int		i;
	t_file	*first;
	t_file	*index;
	t_file	*new;

	i = g_opt.last_opt;
	first = NULL;
	while (i < ac)
	{
		if ((new = cmdline_file(av[i])) != NULL)
		{
			if (first == NULL)
			{
				first = new;
				index = first;
			}
			else
			{
				index->next = new;
				index = index->next;
			}
		}
		i++;
	}
	return (first);
}

t_file	*cmdline_dir(char *name)
{
	t_file	*new;

	new = (t_file*)ft_memalloc(sizeof(t_file));
	if (new == NULL)
	{
		ft_fprintf(2, "%s: %s\n", g_ls_name, strerror(errno));
		exit(1);
	}
	new->name = ft_strdup(name);
	get_file_stats("", new);
	return (new);
}

t_file	*build_directory_list(int ac, char **av)
{
	int		i;
	t_file	*first;
	t_file	*index;

	i = g_opt.last_opt;
	first = NULL;
	while (i < ac)
	{
		if (is_directory(av[i], 0) == 1)
		{
			if (first == NULL)
			{
				first = cmdline_dir(av[i]);
				index = first;
			}
			else
			{
				index->next = cmdline_dir(av[i]);
				index = index->next;
			}
		}
		i++;
	}
	index = NULL;
	return (first);
}
