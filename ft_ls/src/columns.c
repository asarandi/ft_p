/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 05:22:23 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:56:31 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long	list_length(t_file *list)
{
	long i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	across_output(int num_col, t_file *list)
{
	uintmax_t	i;
	intmax_t	len;

	i = 0;
	while (list)
	{
		ft_fprintf(1, "%s", list->name);
		print_entry_symbol(list->st.st_mode);
		if (list->next == NULL)
			break ;
		if ((i + 1) % num_col == 0)
			ft_fprintf(1, "\n");
		else
		{
			len = ft_strlen(list->name);
			print_tabs(len + has_symbol(list->st.st_mode));
		}
		list = list->next;
		i++;
	}
	write(1, "\n", 1);
}

void	column_output(int total, int nth, int num_col, t_file *list)
{
	int			j;
	t_file		*next;
	t_file		*last;
	int			row_max;

	last = get_nth_element(list, nth);
	while (list)
	{
		next = list;
		row_max = get_row_end(list, num_col, nth);
		j = 0;
		while (next)
		{
			print_column_item(next);
			if ((--total <= 0) || (++j >= row_max))
				break ;
			print_tabs(ft_strlen(next->name) + has_symbol(next->st.st_mode));
			next = get_nth_element(next, nth);
		}
		ft_fprintf(1, "\n");
		list = list->next;
		if (list == last)
			break ;
	}
}

void	print_columns(t_file *list)
{
	struct winsize	ws;
	int				num_col;
	int				tabs_longest_name;
	int				nth;
	int				len;

	if ((isatty(1) == 0) || (ioctl(0, TIOCGWINSZ, &ws) == -1))
		return (print_basic(list));
	get_directory_widths(list);
	tabs_longest_name = (g_width.name / TAB_SIZE) + 1;
	num_col = ((ws.ws_col / TAB_SIZE)) / tabs_longest_name;
	len = list_length(list);
	if (len <= num_col)
		return (print_across(list));
	nth = len / num_col;
	while (nth * num_col < len)
		nth += 1;
	column_output(len, nth, num_col, list);
}

void	print_across(t_file *list)
{
	struct winsize	ws;
	int				num_col;
	int				tabs_longest_name;

	if (isatty(1) == 0)
		return (print_basic(list));
	if ((num_col = ioctl(0, TIOCGWINSZ, &ws)) == -1)
		return (print_basic(list));
	get_directory_widths(list);
	tabs_longest_name = (g_width.name / TAB_SIZE) + 1;
	num_col = (ws.ws_col / TAB_SIZE) / tabs_longest_name;
	across_output(num_col, list);
}
