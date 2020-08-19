/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 15:21:30 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 15:29:00 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_sort_env(char **env, int i)
{
	if (env[i + 1] == NULL)
	{
		env[i] = NULL;
		return (1);
	}
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
	return (1);
}

void	ft_find_var(char *variable, char **env)
{
	int		equally;
	int		i;

	i = 0;
	while (env[i])
	{
		equally = ft_strnchr(env[i], '=');
		if (!(ft_strncmp(variable, env[i], equally)))
			ft_sort_env(env, i);
		i++;
	}
}

int		fsh_unsetenv(char **args, char **environ)
{
	if (args[1] == NULL)
	{
		ft_printf("unsetenv: Too few arguments.\n");
		return (1);
	}
	if (ft_strchr(args[1], '='))
		return (1);
	if (args[1])
		ft_find_var(args[1], environ);
	return (1);
}
