/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:57:35 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/13 16:23:26 by dmarsell         ###   ########.fr       */
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

char    **fsh_config(const char **environ);
int     fsh_execute(char **args, char **newenv);
void    ft_error(char *str);

# endif