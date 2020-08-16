/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:57:35 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/16 03:22:18 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h> 
# include <errno.h>
# include "libft/ft_printf/ft_printf.h"

#define FSH_RL_BUFSIZE  1024
#define FD_MIN_SHELL    0
#define READ_SIZE       256

// typedef struct  s_sort
// {
//     char    **sort;
//     // int     flag;
//     // int     j;
//     // int     i;
//     // int     sym;
// }               t_sort;

int     fsh_execute(char **args, char **environ);
int     ft_compare(char *name, char *value, char **env);
void    ft_print_env(char **env, char *var, int len);
void    ft_find_var(char *variable, char **env);
int     fsh_exit(char **args, char **environ);
char    *ft_find_home(char **env, char *tmp);
char    **fsh_config(const char **environ);
char    *ft_del_quotation(char *str);
void    ft_error(char *str);

void    ft_sort(char *tmp, char **names, char **sort);
int     ft_find_sp(char line[READ_SIZE]);
void   ft_autocomplete(char line[READ_SIZE]);

# endif