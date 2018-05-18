/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:27:58 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:57:46 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		display_files(int ac, char **av)
{
	t_file	*list;

	list = build_file_list(ac, av);
	if (list != NULL)
	{
		sort_list(&list);
		choose_print("", list);
		destroy_list(list);
		return (1);
	}
	return (0);
}

void	display_directories(int ac, char **av, int flag)
{
	t_file	*list;
	t_file	*first;

	list = build_directory_list(ac, av);
	first = list;
	if ((list != NULL) && (flag))
		ft_fprintf(1, "\n");
	if ((list) && (list->next))
		flag = 1;
	if (list != NULL)
	{
		sort_list(&list);
		while (list)
		{
			if (flag)
				ft_fprintf(1, "%s:\n", list->name);
			directory_add_slash(&list->name);
			list_directory(list->name);
			list = list->next;
			if (list)
				ft_fprintf(1, "\n");
		}
		destroy_list(first);
	}
}
