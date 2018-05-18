/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:02:16 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/04 17:12:56 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_entry_type(unsigned long st_mode)
{
	if (S_ISREG(st_mode))
		write(1, "-", 1);
	else if (S_ISDIR(st_mode))
		write(1, "d", 1);
	else if (S_ISCHR(st_mode))
		write(1, "c", 1);
	else if (S_ISBLK(st_mode))
		write(1, "b", 1);
	else if (S_ISFIFO(st_mode))
		write(1, "p", 1);
	else if (S_ISLNK(st_mode))
		write(1, "l", 1);
	else if (S_ISSOCK(st_mode))
		write(1, "s", 1);
	else
		write(1, "?", 1);
}

int		has_symbol(unsigned long st_mode)
{
	if (g_opt.slash == 1)
	{
		if (S_ISDIR(st_mode))
			return (1);
	}
	if (g_opt.symbol == 1)
	{
		if (S_ISDIR(st_mode))
			return (1);
		else if (S_ISFIFO(st_mode))
			return (1);
		else if (S_ISLNK(st_mode))
			return (1);
		else if (S_ISSOCK(st_mode))
			return (1);
		else if (S_ISWHT(st_mode))
			return (1);
		else if (st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
			return (1);
	}
	return (0);
}

void	print_entry_symbol(unsigned long st_mode)
{
	if (g_opt.slash == 1)
	{
		if (S_ISDIR(st_mode))
			write(1, "/", 1);
		return ;
	}
	if (g_opt.symbol == 1)
	{
		if (S_ISDIR(st_mode))
			write(1, "/", 1);
		else if (S_ISFIFO(st_mode))
			write(1, "|", 1);
		else if (S_ISLNK(st_mode))
			write(1, "@", 1);
		else if (S_ISSOCK(st_mode))
			write(1, "=", 1);
		else if (S_ISWHT(st_mode))
			write(1, "%", 1);
		else if (st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
			write(1, "*", 1);
	}
}

void	print_permissions(unsigned long st_mode)
{
	(st_mode & S_IRUSR) ? write(1, "r", 1) : write(1, "-", 1);
	(st_mode & S_IWUSR) ? write(1, "w", 1) : write(1, "-", 1);
	if (st_mode & S_ISUID)
		(st_mode & S_IXUSR) ? write(1, "s", 1) : write(1, "S", 1);
	else
		(st_mode & S_IXUSR) ? write(1, "x", 1) : write(1, "-", 1);
	(st_mode & S_IRGRP) ? write(1, "r", 1) : write(1, "-", 1);
	(st_mode & S_IWGRP) ? write(1, "w", 1) : write(1, "-", 1);
	if (st_mode & S_ISGID)
		(st_mode & S_IXGRP) ? write(1, "s", 1) : write(1, "S", 1);
	else
		(st_mode & S_IXGRP) ? write(1, "x", 1) : write(1, "-", 1);
	(st_mode & S_IROTH) ? write(1, "r", 1) : write(1, "-", 1);
	(st_mode & S_IWOTH) ? write(1, "w", 1) : write(1, "-", 1);
	if (st_mode & S_ISVTX)
		(st_mode & S_IXOTH) ? write(1, "t", 1) : write(1, "T", 1);
	else
		(st_mode & S_IXOTH) ? write(1, "x", 1) : write(1, "-", 1);
}

void	print_file_mode(unsigned long st_mode)
{
	(void)print_entry_type(st_mode);
	(void)print_permissions(st_mode);
}
