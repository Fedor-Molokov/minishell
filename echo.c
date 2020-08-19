/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:48:00 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 16:04:45 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_quotation(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			count++;
		i++;
	}
	return (count);
}

char	*ft_del_quotation(char *str)
{
	char	*tmp;
	int		count;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str);
	count = ft_count_quotation(str);
	if (!(tmp = ft_memalloc(len - count + 1)))
		ft_error("malloc error");
	j = 0;
	i = 0;
	while (str[i] && j < (len - count))
	{
		while (str[i] == 34 || str[i] == 39)
			i++;
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int		ft_echo_print_val(char *var, char **env)
{
	int		equally;
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		equally = ft_strnchr(env[i], '=');
		if (!(ft_strncmp(var, env[i], equally)))
		{
			value = ft_strdup(&env[i][equally + 1]);
			ft_printf("%s\n", value);
			free(var);
			free(value);
			return (1);
		}
		i++;
	}
	ft_printf("%s: Undefined variable.\n", var);
	free(var);
	return (1);
}

int		fsh_echo(char **args, char **environ)
{
	char	*tmp;
	int		i;

	i = 1;
	while (args[i])
	{
		if (args[1][0] == '$')
		{
			tmp = ft_strdup(&args[1][1]);
			return (ft_echo_print_val(tmp, environ));
		}
		if (ft_strchr(args[i], 34) || ft_strchr(args[i], 39))
		{
			tmp = ft_del_quotation(args[i]);
			args[i + 1] == NULL ? ft_printf("%s\n", tmp) :\
			ft_printf("%s ", tmp);
			free(tmp);
			i++;
			continue ;
		}
		args[i + 1] == NULL ? ft_printf("%s\n", args[i]) :\
		ft_printf("%s ", args[i]);
		i++;
	}
	return (1);
}
