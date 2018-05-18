/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:24:15 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/04 16:34:36 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	clear_options(void)
{
	g_opt.across = 0;
	g_opt.column = 0;
	g_opt.basic = 0;
	g_opt.long_list = 0;
	g_opt.recursive = 0;
	g_opt.reverse = 0;
	g_opt.show_dot = 0;
	g_opt.show_hidden = 0;
	g_opt.time = 0;
	g_opt.sort = 0;
	g_opt.symbol = 0;
	g_opt.slash = 0;
	g_opt.colors = 0;
	g_opt.fulltime = 0;
	g_opt.hide_owner = 0;
	g_opt.hide_group = 0;
	g_opt.show_acl = 0;
	g_opt.show_extattr = 0;
	g_opt.plain = 0;
	g_opt.last_opt = 1;
}

void	clear_widths(void)
{
	g_width.links = 0;
	g_width.owner = 0;
	g_width.group = 0;
	g_width.size = 0;
	g_width.blocks = 0;
	g_width.has_cb = 0;
	g_width.name = 0;
}
