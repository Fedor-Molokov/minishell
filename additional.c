/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:58:26 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 17:29:40 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str)
{
	ft_printf("%s", str);
	fsh_exit(NULL, NULL);
}

int		ft_find_semi_colon(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

void	ft_del_tabs(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}

int		fsh_tab(char **args, char **environ)
{
	(void)args;
	(void)environ;
	return (1);
}
