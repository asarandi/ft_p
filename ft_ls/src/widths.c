/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 14:28:58 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/04 07:02:30 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_digits(unsigned long long n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

void	calculate_widths(void)
{
	t_x	temp;

	temp = g_width.links;
	g_width.links = count_digits(temp);
	temp = g_width.size;
	g_width.size = count_digits(temp);
}

void	get_str_owner_width(t_x *save, uid_t uid)
{
	struct passwd	*pwd;
	int				k;

	*save = uid;
	pwd = getpwuid(uid);
	if (pwd != NULL)
	{
		k = ft_strlen(pwd->pw_name);
		if (k > (int)g_width.owner)
			g_width.owner = k;
	}
}

void	get_str_group_width(t_x *save, gid_t gid)
{
	struct group	*grp;
	int				k;

	*save = gid;
	grp = getgrgid(gid);
	if (grp != NULL)
	{
		k = ft_strlen(grp->gr_name);
		if (k > (int)g_width.group)
			g_width.group = k;
	}
}

void	get_directory_widths(t_file *list)
{
	t_x	uid;
	t_x	gid;

	uid = -1;
	gid = -1;
	clear_widths();
	while (list)
	{
		get_max_filename_len(list);
		if (list->st.st_nlink > g_width.links)
			g_width.links = list->st.st_nlink;
		if (list->st.st_size > (off_t)g_width.size)
			g_width.size = list->st.st_size;
		if (list->st.st_uid != uid)
			get_str_owner_width(&uid, list->st.st_uid);
		if (list->st.st_gid != gid)
			get_str_group_width(&gid, list->st.st_gid);
		if ((S_ISCHR(list->st.st_mode)) ||
				(S_ISBLK(list->st.st_mode)))
			g_width.has_cb = 1;
		g_width.blocks += list->st.st_blocks;
		list = list->next;
	}
	calculate_widths();
}
