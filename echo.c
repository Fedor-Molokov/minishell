/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:48:00 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/18 02:26:44 by dmarsell         ###   ########.fr       */
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

int     fsh_echo(char **args, char **newenv, char **environ)
{
    char    *tmp;
    int     i;

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
            args[i + 1] == NULL ? ft_printf("%s\n", tmp) : ft_printf("%s ", tmp);
            free(tmp);
            i++;
            continue ;
        }
        args[i + 1] == NULL ? ft_printf("%s\n", args[i]) : ft_printf("%s ", args[i]);
        i++;
    }
    ft_memdel(args);
    return (1);
}