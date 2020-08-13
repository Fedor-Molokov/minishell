/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 05:29:13 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/13 06:49:42 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int     ft_load_config_file(char **environ, char ***newenv)
{
    char    **tmp;
    int     i;

    i = 1;
    // while(environ[i])
    // {
        tmp = ft_strsplit(environ[i], '=');
        newenv[i] = tmp;
        // ft_printf("%s\n", newenv[i][0]);
        // i++;
    // }
    newenv[++i] = NULL;
    i = 0;
    // while(newenv[i++])
        ft_printf("%s\n", newenv[i][0]);
    return (0);
}