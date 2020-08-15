/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:57:35 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/15 08:06:22 by dmarsell         ###   ########.fr       */
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
# include "libft/ft_printf/ft_printf.h"

#define FSH_RL_BUFSIZE  1024
#define FD_MIN_SHELL    0

int     fsh_execute(char **args, char **newenv, char **environ);
int     ft_compare(char *name, char *value, char **env);
void    ft_print_env(char **env, char *var, int len);
void    ft_find_var(char *variable, char **env);
char    *ft_find_home(char **env, char *tmp);
char    **fsh_config(const char **environ);
char    *ft_del_quotation(char *str);
void    ft_error(char *str);

# endif