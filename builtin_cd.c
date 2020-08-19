/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 12:16:46 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 13:52:54 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char		*g_prevpath;
extern char		*g_addpath;

int		ft_cd_arg(char **args, char **environ, char *tmp)
{
	ft_bzeroall(g_prevpath);
	ft_bzeroall(g_addpath);
	getcwd(g_prevpath, BUFSIZ);
	if (args[1][0] == '~')
		return (ft_cd_home(args, tmp, environ));
	else if (chdir(args[1]) != 0)
		ft_printf("%s: No such file or directory.\n", args[1]);
	return (1);
}

void	ft_cd_minus(void)
{
	if (g_addpath[0] != '\0')
	{
		ft_bzeroall(g_prevpath);
		getcwd(g_prevpath, BUFSIZ);
		chdir(g_addpath);
		ft_bzeroall(g_addpath);
	}
	else
	{
		ft_bzeroall(g_addpath);
		getcwd(g_addpath, BUFSIZ);
		chdir(g_prevpath);
	}
}

int		ft_cd_home(char **args, char *tmp, char **environ)
{
	ft_bzeroall(g_prevpath);
	ft_bzeroall(g_addpath);
	getcwd(g_prevpath, BUFSIZ);
	tmp = ft_find_home(environ, tmp);
	if (args[1])
	{
		if (args[1][1] != '\0')
			tmp = ft_strjoin(tmp, &args[1][1]);
	}
	chdir(tmp);
	free(tmp);
	return (1);
}

int		fsh_cd(char **args, char **environ)
{
	char	*tmp;

	tmp = NULL;
	if (args[1] == NULL)
		return (ft_cd_home(args, tmp, environ));
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		if (g_prevpath[0] == '\0' && g_addpath[0] == '\0')
		{
			ft_printf("fsh: No such file or directory\n");
			return (1);
		}
		else
			ft_cd_minus();
	}
	else
		ft_cd_arg(args, environ, tmp);
	(void)environ;
	return (1);
}
