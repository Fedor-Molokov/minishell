/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 05:29:13 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 15:00:54 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_print_env_next(char **env, char *var, int len, int i)
{
	int		flag;

	flag = 0;
	while (env[i] && var != NULL)
	{
		if (!(ft_strncmp(env[i], var, len)))
		{
			flag = 1;
			ft_printf("%s\n", var);
			if (env[i + 1] == NULL)
				break ;
			else
				i++;
		}
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (flag);
}

void	ft_print_env(char **env, char *var, int len)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (env[i] && var == NULL)
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	flag = ft_print_env_next(env, var, len, i);
	if (var && flag == 0)
		ft_printf("%s\n", var);
}

int		fsh_envargs(char **args, char **environ, t_envstrct envstrct)
{
	envstrct.len = ft_strlen(args[1]);
	envstrct.equally = ft_strnchr(args[1], '=');
	if (envstrct.equally == -1)
		ft_printf("%s: %s: No such file or directory\n", args[0], args[1]);
	else if (envstrct.len == envstrct.equally)
	{
		envstrct.varname = ft_strdup(args[1]);
		ft_print_env(environ, envstrct.varname, envstrct.len);
	}
	else if (envstrct.len != envstrct.equally)
	{
		envstrct.varname = ft_memalloc(envstrct.len + 1);
		envstrct.varname[envstrct.len] = '=';
		ft_strcpy(envstrct.varname, args[1]);
		ft_print_env(environ, envstrct.varname, envstrct.equally);
	}
	free(envstrct.varname);
	return (1);
}

int		fsh_env(char **args, char **environ)
{
	t_envstrct	envstrct;

	envstrct.varname = NULL;
	if (args[1] == NULL)
		ft_print_env(environ, NULL, 0);
	else if (args[1] != NULL)
		return (fsh_envargs(args, environ, envstrct));
	return (1);
}
