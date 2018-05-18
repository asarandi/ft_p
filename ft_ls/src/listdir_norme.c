/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdir_norme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 03:22:19 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:58:33 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parent_node(t_file **head, t_file **index, t_file *new)
{
	(*head) = new;
	(*index) = *head;
}

void	child_node(t_file **index, t_file *node)
{
	(*index)->next = node;
	(*index) = (*index)->next;
}

void	choose_print(char *path, t_file *list)
{
	if (g_opt.basic == 1)
		print_basic(list);
	else if (g_opt.long_list == 1)
		print_long(path, list);
	else if (g_opt.across == 1)
		print_across(list);
	else
		print_columns(list);
}

void	listdir_sortprint(t_file **list, char *path, t_file **start)
{
	sort_list(list);
	choose_print(path, *list);
	(*start) = *list;
}

void	listdir_nextsubdir(char **subdir)
{
	ft_fprintf(1, "\n%s:\n", *subdir);
	directory_add_slash(subdir);
	list_directory(*subdir);
}
