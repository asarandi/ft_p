/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 02:22:14 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:58:59 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_max_filename_len(t_file *list)
{
	size_t	len;

	len = ft_strlen(list->name);
	len += has_symbol(list->st.st_mode);
	if (len > g_width.name)
		g_width.name = len;
}

void	print_tabs(intmax_t name_len)
{
	int	col_width;
	int nam_width;

	col_width = (g_width.name / TAB_SIZE) + 1;
	nam_width = (name_len / TAB_SIZE);
	while (nam_width < col_width)
	{
		write(1, "\t", 1);
		nam_width += 1;
	}
}

t_file	*get_nth_element(t_file *list, uintmax_t n)
{
	while ((list) && (n))
	{
		list = list->next;
		n--;
	}
	if (!list)
		return (NULL);
	return (list);
}

int		get_row_end(t_file *list, uintmax_t n, uintmax_t nth)
{
	uintmax_t	i;

	i = 0;
	while ((list) && (i < n))
	{
		i++;
		list = get_nth_element(list, nth);
	}
	return ((int)i);
}

void	print_column_item(t_file *list)
{
	ft_fprintf(1, "%s", list->name);
	print_entry_symbol(list->st.st_mode);
}
