/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 22:21:06 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/03 19:45:41 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_split(t_file *head, t_file **left, t_file **right)
{
	t_file	*slow;
	t_file	*fast;

	slow = head;
	if (head == NULL || head->next == NULL)
	{
		(*left) = head;
		(*right) = NULL;
	}
	else
	{
		fast = head->next;
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
	}
	(*left) = head;
	(*right) = slow->next;
	slow->next = NULL;
}

t_file	*merge_lists(t_file *left, t_file *right)
{
	t_file	*merged;

	if (!left)
		return (right);
	if (!right)
		return (left);
	if (g_opt.sort_algo(left, right) <= 0)
	{
		merged = left;
		merged->next = merge_lists(left->next, right);
	}
	else
	{
		merged = right;
		merged->next = merge_lists(left, right->next);
	}
	return (merged);
}

void	sort_list(t_file **list)
{
	t_file	*head;
	t_file	*left;
	t_file	*right;

	if (g_opt.sort == -1)
		return ;
	head = *list;
	if ((head == NULL) || (head->next == NULL))
		return ;
	list_split(head, &left, &right);
	sort_list(&left);
	sort_list(&right);
	(*list) = merge_lists(left, right);
}

void	choose_sort(void)
{
	int (*f)(t_file *f1, t_file *f2);

	f = sort_by_name_asc;
	if (g_opt.sort == 0)
		f = g_opt.reverse == 0 ? sort_by_name_asc : sort_by_name_desc;
	else if (g_opt.sort == 4)
		f = g_opt.reverse == 0 ? sort_by_size_asc : sort_by_size_desc;
	else if ((g_opt.sort == 1) && (g_opt.time == 1))
		f = g_opt.reverse == 0 ? sort_by_atime_asc : sort_by_atime_desc;
	else if ((g_opt.sort == 1) && (g_opt.time == 2))
		f = g_opt.reverse == 0 ? sort_by_btime_asc : sort_by_btime_desc;
	else if ((g_opt.sort == 1) && (g_opt.time == 3))
		f = g_opt.reverse == 0 ? sort_by_ctime_asc : sort_by_ctime_desc;
	else if (g_opt.sort == 1)
		f = g_opt.reverse == 0 ? sort_by_mtime_asc : sort_by_mtime_desc;
	g_opt.sort_algo = f;
}
