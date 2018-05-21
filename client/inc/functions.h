/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:40:50 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/20 19:24:37 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "client.h"

typedef struct s_ftp	t_ftp;

char	*char_array_find_paren(char **array);
char	*str_char_index(char *str, char c, int index);
char	*word(char *str, int index);
int		count_char_array(char **array);
int		main(int argc, char **argv, char **envp);
int	client_execute_command(t_ftp *f);
int	client_execute_shell_cmd(t_ftp *f);
int	client_loop(t_ftp *f);
int	client_parse_passive(t_ftp *f);
int	client_read_from_server(t_ftp *f);
int	client_read_from_user(t_ftp *f);
int	client_read_passive(t_ftp *p);
int	client_send_raw(t_ftp *f);
int	cmd_get(t_ftp *f);
int	cmd_ls(t_ftp *f);
int	cmd_pasv(t_ftp *f);
int	cmd_put(t_ftp *f);
int	socket_connect(t_ftp *f);
int	str_char_count(char *str, char c);
int	str_char_replace(char *str, char a, char b);
int cmd_cd(t_ftp *f);
int cmd_cd_local(t_ftp *f);
int cmd_get_2(t_ftp *f);
int cmd_ls_2(t_ftp *f);
int cmd_put_2(t_ftp *f);
int cmd_pwd(t_ftp *f);
int cmd_quit(t_ftp *f);
void	client_cleanup(t_ftp *f);
void	client_connect(t_ftp *f);
void	client_exit(t_ftp *f, char *msg, int exit_code);
void	client_parse(t_ftp *f);
void	client_show_usage(t_ftp *f);
void	client_start(int argc, char **argv, char **envp);
void	destroy_char_array(char **array);
void	sigint_handler(int signo);

#endif
