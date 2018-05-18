/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_files3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 23:00:55 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/02 23:24:57 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_by_ctime_asc(t_file *file1, t_file *file2)
{
	if (file2->st.st_ctimespec.tv_sec > file1->st.st_ctimespec.tv_sec)
		return (1);
	else if (file2->st.st_ctimespec.tv_sec < file1->st.st_ctimespec.tv_sec)
		return (-1);
	else if (file2->st.st_ctimespec.tv_nsec > file1->st.st_ctimespec.tv_nsec)
		return (1);
	else if (file2->st.st_ctimespec.tv_nsec < file1->st.st_ctimespec.tv_nsec)
		return (-1);
	else
		return (sort_by_name_asc(file1, file2));
}

int		sort_by_ctime_desc(t_file *file1, t_file *file2)
{
	if (file2->st.st_ctimespec.tv_sec > file1->st.st_ctimespec.tv_sec)
		return (-1);
	else if (file2->st.st_ctimespec.tv_sec < file1->st.st_ctimespec.tv_sec)
		return (1);
	else if (file2->st.st_ctimespec.tv_nsec > file1->st.st_ctimespec.tv_nsec)
		return (-1);
	else if (file2->st.st_ctimespec.tv_nsec < file1->st.st_ctimespec.tv_nsec)
		return (1);
	else
		return (sort_by_name_desc(file1, file2));
}

int		sort_by_btime_asc(t_file *file1, t_file *file2)
{
	struct timespec	bts1;
	struct timespec	bts2;

	bts1 = file1->st.st_birthtimespec;
	bts2 = file2->st.st_birthtimespec;
	if (bts2.tv_sec > bts1.tv_sec)
		return (1);
	else if (bts2.tv_sec < bts1.tv_sec)
		return (-1);
	else if (bts2.tv_nsec > bts1.tv_nsec)
		return (1);
	else if (bts2.tv_nsec < bts1.tv_nsec)
		return (-1);
	else
		return (sort_by_name_asc(file1, file2));
}

int		sort_by_btime_desc(t_file *file1, t_file *file2)
{
	struct timespec	bts1;
	struct timespec	bts2;

	bts1 = file1->st.st_birthtimespec;
	bts2 = file2->st.st_birthtimespec;
	if (bts2.tv_sec > bts1.tv_sec)
		return (-1);
	else if (bts2.tv_sec < bts1.tv_sec)
		return (1);
	else if (bts2.tv_nsec > bts1.tv_nsec)
		return (-1);
	else if (bts2.tv_nsec < bts1.tv_nsec)
		return (1);
	else
		return (sort_by_name_desc(file1, file2));
}
