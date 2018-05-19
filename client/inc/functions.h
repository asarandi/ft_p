/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:40:50 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/19 04:55:02 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "client.h"

typedef struct s_ftp	t_ftp;

char	*word(char *str, int index);
char	**request_split(char *str);
char	*file_get_contents(char *filename);
int		count_char_array(char **array);
int		ftp_send_text(t_ftp *f, int code, char *str);
int		server_loop(t_ftp *f);
int		cmd_cdup(t_ftp *f);
int		cmd_cwd(t_ftp *f);
int		cmd_dele(t_ftp *f);
int		cmd_help(t_ftp *f);
int		cmd_list(t_ftp *f);
int		cmd_list_fork(t_ftp *f);
int		cmd_mkd(t_ftp *f);
int		cmd_pass(t_ftp *f);
int		cmd_pasv(t_ftp *f);
int		cmd_port(t_ftp *f);
int		cmd_pwd(t_ftp *f);
int		cmd_quit(t_ftp *f);
int		cmd_retr(t_ftp *f);
int		cmd_rmd(t_ftp *f);
int		cmd_size(t_ftp *f);
int		cmd_stor(t_ftp *f);
int		cmd_stor_receive(t_ftp *f);
int		cmd_syst(t_ftp *f);
int		cmd_type(t_ftp *f);
int		cmd_user(t_ftp *f);
int		incoming_accept(t_ftp *f);
int		incoming_create(t_ftp *f);
int		main(int argc, char **argv, char **envp);
int		socket_bind(t_ftp *f);
int		socket_create(t_ftp *f);
int		socket_listen(t_ftp *f);
int		socket_options(t_ftp *f);
ssize_t	file_get_size(char *filename);
void	destroy_char_array(char **array);
void	passive_cleanup(t_ftp *f);
void	server_accept(t_ftp *f);
void	server_cleanup(t_ftp *f);
void	server_exit(t_ftp *f, char *msg, int exit_code);
void	server_fork(t_ftp *f);
void	server_init(t_ftp *f);
void	server_parse(t_ftp *f, int argc, char **argv, char **envp);
void	server_show_usage(t_ftp *f);
void	server_start(int argc, char **argv, char **envp);
void	sigint_handler(int signo);
void	string_shift_left(char *str);
void	whitespace_consolidate(char *str);
void	whitespace_transform(char *str);

#endif
