/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_files2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 23:00:34 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/02 23:11:36 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#ifdef __linux__
#define st_mtimespec	st_mtim
#define st_atimespec	st_atim
#define st_ctimespec	st_ctim
#endif

int		sort_by_mtime_asc(t_file *file1, t_file *file2)
{
	if (file2->st.st_mtimespec.tv_sec > file1->st.st_mtimespec.tv_sec)
		return (1);
	else if (file2->st.st_mtimespec.tv_sec < file1->st.st_mtimespec.tv_sec)
		return (-1);
	else if (file2->st.st_mtimespec.tv_nsec > file1->st.st_mtimespec.tv_nsec)
		return (1);
	else if (file2->st.st_mtimespec.tv_nsec < file1->st.st_mtimespec.tv_nsec)
		return (-1);
	else
		return (sort_by_name_asc(file1, file2));
}

int		sort_by_mtime_desc(t_file *file1, t_file *file2)
{
	if (file2->st.st_mtimespec.tv_sec > file1->st.st_mtimespec.tv_sec)
		return (-1);
	else if (file2->st.st_mtimespec.tv_sec < file1->st.st_mtimespec.tv_sec)
		return (1);
	else if (file2->st.st_mtimespec.tv_nsec > file1->st.st_mtimespec.tv_nsec)
		return (-1);
	else if (file2->st.st_mtimespec.tv_nsec < file1->st.st_mtimespec.tv_nsec)
		return (1);
	else
		return (sort_by_name_desc(file1, file2));
}

int		sort_by_atime_asc(t_file *file1, t_file *file2)
{
	if (file2->st.st_atimespec.tv_sec > file1->st.st_atimespec.tv_sec)
		return (1);
	else if (file2->st.st_atimespec.tv_sec < file1->st.st_atimespec.tv_sec)
		return (-1);
	else if (file2->st.st_atimespec.tv_nsec > file1->st.st_atimespec.tv_nsec)
		return (1);
	else if (file2->st.st_atimespec.tv_nsec < file1->st.st_atimespec.tv_nsec)
		return (-1);
	else
		return (sort_by_name_asc(file1, file2));
}

int		sort_by_atime_desc(t_file *file1, t_file *file2)
{
	if (file2->st.st_atimespec.tv_sec > file1->st.st_atimespec.tv_sec)
		return (-1);
	else if (file2->st.st_atimespec.tv_sec < file1->st.st_atimespec.tv_sec)
		return (1);
	else if (file2->st.st_atimespec.tv_nsec > file1->st.st_atimespec.tv_nsec)
		return (-1);
	else if (file2->st.st_atimespec.tv_nsec < file1->st.st_atimespec.tv_nsec)
		return (1);
	else
		return (sort_by_name_desc(file1, file2));
}
