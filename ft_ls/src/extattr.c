/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extattr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:46:39 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/03 19:41:11 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_extended_attributes(char *path, t_file *file)
{
	acl_t	acl;
	char	*fullpath;

	fullpath = ft_strjoin(path, file->name);
	if ((listxattr(fullpath, NULL, 0, XATTR_NOFOLLOW)) > 0)
		write(1, "@", 1);
	else
	{
		acl = acl_get_link_np(fullpath, ACL_TYPE_EXTENDED);
		if (acl != NULL)
		{
			acl_free(acl);
			write(1, "+", 1);
		}
		else
			write(1, " ", 1);
	}
	free(fullpath);
}
