/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:57:35 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 12:19:04 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include "libft/ft_printf/ft_printf.h"

#define FSH_RL_BUFSIZE  1024
#define FD_MIN_SHELL    0

int     ft_cd_home(char **args, char *tmp, char **environ);
int     ft_compare(char *name, char *value, char **env);
void    ft_print_env(char **env, char *var, int len);
int     ft_echo_print_val(char *var, char **env);
int     fsh_execute(char **args, char **environ);
void    ft_find_var(char *variable, char **env);
int     fsh_exit(char **args, char **environ);
int     fsh_echo(char **args, char **environ);
int     fsh_tab(char **args, char **environ);
char    *ft_find_home(char **env, char *tmp);
int     fsh_cd(char **args, char **environ);
char    **fsh_config(const char **environ);
int     ft_find_semi_colon(char *line);
char    *ft_del_quotation(char *str);
void    ft_del_tabs(char *line);
void    ft_error(char *str);

# endif