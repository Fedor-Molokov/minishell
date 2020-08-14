/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 19:44:13 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/14 20:23:58 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    ft_print_env(char **env, char *var, int len)
{
    int     i;

    i = 0;
    while(env[i] && var == NULL)
    {
        ft_printf("%s\n", env[i]); 
        i++;
    }
    while(env[i] && var != NULL)
    {
        if (!(ft_strncmp(env[i], var, len)))
        {
            ft_printf("%s\n", var);
            i++;
        }
        ft_printf("%s\n", env[i]); 
        i++;
    }
}