/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:20:23 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 15:05:37 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_compare(char *name, char *value, char **env)
{
	int		equally;
	int		i;

	i = 0;
	while (env[i])
	{
		equally = ft_strnchr(env[i], '=');
		if (ft_strncmp(name, env[i], equally) == 0)
		{
			ft_bzeroall(&env[i][equally + 1]);
			ft_strcpy(&env[i][equally + 1], value);
			return (1);
		}
		i++;
	}
	return (0);
}

int		fsh_setenv_next(char **args, char **environ, int i)
{
	int		len1;

	if (ft_strchr(args[1], '='))
		ft_printf("setenv: Variable name must contain alphanumeric \
		characters.\n");
	else
	{
		len1 = ft_strlen(args[1]);
		if (!(environ[i] = (char *)malloc(sizeof(char) * (len1 + 2))))
			ft_error("malloc error\n");
		ft_strcpy(environ[i], args[1]);
		environ[i][len1] = '=';
		environ[i][len1 + 1] = '\0';
		environ[i + 1] = NULL;
	}
	return (1);
}

int		fsh_setenv(char **args, char **environ)
{
	int		i;
	int		len1;
	int		len2;

	i = 0;
	while (environ[i])
		i++;
	args[1] == NULL ? fsh_env(args, environ) : 1;
	if (args[1] && args[2] == NULL)
		return (fsh_setenv_next(args, environ, i));
	else if (args[1] != NULL && args[2])
	{
		if (ft_compare(args[1], args[2], environ))
			return (1);
		len1 = ft_strlen(args[1]);
		len2 = ft_strlen(args[2]);
		if (!(environ[i] = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
			ft_error("malloc error\n");
		ft_strcpy(environ[i], args[1]);
		ft_strcpy(&environ[i][len1], "=");
		ft_strcpy(&environ[i][len1 + 1], args[2]);
		environ[i][len1 + len2 + 2] = '\0';
		environ[i + 1] = NULL;
	}
	return (1);
}
