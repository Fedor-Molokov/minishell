/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:48:00 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/17 16:17:03 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int    ft_echo_print_val(char *var, char **env)
{
    int     equally;
    char    *value;
    int     i;

    i = 0;
    while(env[i])
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