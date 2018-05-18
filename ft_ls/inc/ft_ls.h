/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:05:13 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/18 02:46:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <errno.h>
# include "libft.h"
# include "libftprintf.h"
# include <sys/acl.h>

# define TAB_SIZE 8

# ifdef __linux__
# define st_mtimespec		st_mtim
# define st_atimespec		st_atim
# define st_ctimespec		st_ctim
# define st_birthtimespec	st_mtim
# define acl_get_link_np	acl_get_file
# define ACL_TYPE_EXTENDED	ACL_TYPE_ACCESS
# include <sys/sysmacros.h>
# define	S_ISWHT(m)	((m & 0170000) == 0160000)
# endif


typedef uintmax_t	t_x;

typedef struct		s_file
{
	char			*name;
	struct stat		st;
	struct s_file	*next;
}					t_file;

typedef struct		s_options
{
	int				across;
	int				column;
	int				basic;
	int				long_list;
	int				recursive;
	int				reverse;
	int				show_dot;
	int				show_hidden;
	int				time;
	int				sort;
	int				(*sort_algo)(t_file *f1, t_file *f2);
	int				symbol;
	int				slash;
	int				colors;
	int				fulltime;
	int				hide_owner;
	int				hide_group;
	int				show_acl;
	int				show_extattr;
	int				plain;
	int				last_opt;
}					t_options;

typedef struct		s_widths
{
	uintmax_t		links;
	uintmax_t		owner;
	uintmax_t		group;
	uintmax_t		size;
	uintmax_t		blocks;
	uintmax_t		has_cb;
	uintmax_t		name;
}					t_widths;

t_options			g_opt;
t_widths			g_width;

char				*g_ls_name;

int					get_row_end(t_file *list, uintmax_t n, uintmax_t nth);
void				print_tabs(intmax_t name_len);
void				print_column_item(t_file *list);
t_file				*get_nth_element(t_file *list, uintmax_t n);
int					has_symbol(unsigned long st_mode);
void				get_max_filename_len(t_file *list);
void				print_columns(t_file *list);
void				print_across(t_file *list);
void				choose_print(char *path, t_file *list);
char				*get_symlink_address(char *path, t_file *list);
char				*make_time_string(struct timespec ts);
int					check_all_options(char c);
int					count_digits(unsigned long long n);
int					display_files(int ac, char **av);
int					get_file_stats(char *path, t_file *file);
int					is_allowed(char *fn);
int					is_directory(char *path, int show_error);
int					ok_to_recurse(char *path);
int					parse_options5(char c);
int					sort_by_atime_asc(t_file *file1, t_file *file2);
int					sort_by_atime_desc(t_file *file1, t_file *file2);
int					sort_by_btime_asc(t_file *file1, t_file *file2);
int					sort_by_btime_desc(t_file *file1, t_file *file2);
int					sort_by_ctime_asc(t_file *file1, t_file *file2);
int					sort_by_ctime_desc(t_file *file1, t_file *file2);
int					sort_by_mtime_asc(t_file *file1, t_file *file2);
int					sort_by_mtime_desc(t_file *file1, t_file *file2);
int					sort_by_name_asc(t_file *file1, t_file *file2);
int					sort_by_name_desc(t_file *file1, t_file *file2);
int					sort_by_size_asc(t_file *file1, t_file *file2);
int					sort_by_size_desc(t_file *file1, t_file *file2);
int					main(int ac, char **av);
int					parse_options1(char c);
int					parse_options2(char c);
int					parse_options3(char c);
int					parse_options4(char c);
t_file				*build_directory_list(int ac, char **av);
t_file				*build_file_list(int ac, char **av);
t_file				*cmdline_dir(char *name);
t_file				*cmdline_file(char *name);
t_file				*create_element(char *name, char *path);
t_file				*create_list(char *path);
void				calculate_widths(void);
void				child_node(t_file **index, t_file *node);
void				choose_sort(void);
void				clear_options(void);
void				clear_widths(void);
void				destroy_list(t_file *list);
void				directory_add_slash(char **path);
void				display_directories(int ac, char **av, int flag);
void				get_directory_widths(t_file *list);
void				get_str_group_width(t_x *save, gid_t gid);
void				get_str_owner_width(t_x *save, uid_t uid);
void				illegal_option(char c);
void				list_directory(char *path);
void				list_split(t_file *head, t_file **left, t_file **right);
void				listdir_nextsubdir(char **subdir);
void				listdir_sortprint(t_file **list, char *path, t_file **sta);
void				parent_node(t_file **head, t_file **index, t_file *newf);
void				parse_cmdline(int ac, char **av);
void				print_basic(t_file *list);
void				print_entry_symbol(unsigned long st_mode);
void				print_entry_type(unsigned long st_mode);
void				print_extended_attributes(char *path, t_file *file);
void				print_file_mode(unsigned long st_mode);
void				print_long(char *path, t_file *list);
void				print_owner_group(t_file *list);
void				print_permissions(unsigned long st_mode);
void				print_size(t_file *list);
void				print_symlink(t_file *list, char *path);
void				print_time(t_file *list);
void				sort_list(t_file **list);

#endif
