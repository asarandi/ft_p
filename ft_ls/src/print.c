/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:32:06 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:57:07 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_basic(t_file *list)
{
	while (list)
	{
		ft_fprintf(1, "%s", list->name);
		print_entry_symbol(list->st.st_mode);
		ft_fprintf(1, "\n");
		list = list->next;
	}
}

void	print_time(t_file *list)
{
	struct timespec	ts;

	if (g_opt.time == 1)
		ts = list->st.st_atimespec;
	else if (g_opt.time == 3)
		ts = list->st.st_ctimespec;
	else if (g_opt.time == 2)
		ts = list->st.st_birthtimespec;
	else
		ts = list->st.st_mtimespec;
	if (g_opt.fulltime == 1)
		ft_fprintf(1, "%.20s ", ctime(&ts.tv_sec) + 4);
	else
		ft_fprintf(1, "%.12s ", make_time_string(ts));
}

void	print_size(t_file *list)
{
	if (g_width.has_cb)
	{
		if ((S_ISCHR(list->st.st_mode)) || (S_ISBLK(list->st.st_mode)))
		{
			ft_fprintf(1, "%3d, ", major(list->st.st_rdev));
			if ((minor(list->st.st_rdev) > 255)
					|| ((int)minor(list->st.st_rdev) < 0))
				ft_fprintf(1, "0x%08x ", minor(list->st.st_rdev));
			else
				ft_fprintf(1, "%3d ", minor(list->st.st_rdev));
		}
		else
			ft_fprintf(1, "%*s%*llu ", 8 - g_width.size,
					"", g_width.size, list->st.st_size);
	}
	else
		ft_fprintf(1, "%*llu ", g_width.size, list->st.st_size);
}

void	print_owner_group(t_file *list)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(list->st.st_uid);
	if ((pwd != NULL) && (g_opt.hide_owner == 0))
		ft_fprintf(1, "%-*s  ", g_width.owner, pwd->pw_name);
	grp = getgrgid(list->st.st_gid);
	if ((grp != NULL) && (g_opt.hide_group == 0))
		ft_fprintf(1, "%-*s  ", g_width.group, grp->gr_name);
	if ((g_opt.hide_owner == 1) && (g_opt.hide_group == 1))
		ft_fprintf(1, "  ");
}

void	print_long(char *path, t_file *list)
{
	get_directory_widths(list);
	while (list != NULL)
	{
		print_file_mode(list->st.st_mode);
		ft_fprintf(1, " %*u ", g_width.links, list->st.st_nlink);
		(void)print_owner_group(list);
		(void)print_size(list);
		(void)print_time(list);
		ft_fprintf(1, "%s", list->name);
		print_entry_symbol(list->st.st_mode);
		(void)print_symlink(list, path);
		ft_fprintf(1, "\r\n");
		list = list->next;
	}
}
