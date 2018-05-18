/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_files1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 22:58:26 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/02 23:09:33 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_by_name_asc(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name));
}

int		sort_by_name_desc(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file2->name, file1->name));
}

int		sort_by_size_asc(t_file *file1, t_file *file2)
{
	if (file2->st.st_size > file1->st.st_size)
		return (1);
	if (file2->st.st_size < file1->st.st_size)
		return (-1);
	else
		return (sort_by_name_asc(file1, file2));
}

int		sort_by_size_desc(t_file *file1, t_file *file2)
{
	if (file2->st.st_size > file1->st.st_size)
		return (-1);
	if (file2->st.st_size < file1->st.st_size)
		return (1);
	else
		return (sort_by_name_desc(file1, file2));
}
