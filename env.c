/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 05:29:13 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/14 22:35:23 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char     **fsh_config(const char **environ)
{
    char    **newenv;
    int     i;
    int     j;
    int     len;

    len = 0;
    i = 0;
    j = 0;
    newenv = NULL;
    while (environ[i])
        i++;
    if (!(newenv = (char **)malloc(sizeof(char *) * (i + 1))))
        ft_error("malloc error\n");
    newenv[i] = NULL;
    j = 0;
    while (j < i)
    {
        len = ft_strlen(environ[j]);
        if (!(newenv[j] = (char *)malloc(sizeof(char) * (len + 1))))
            ft_error("malloc error\n");
        newenv[j][len] = '\0';
        j++;
    }
    i = 0;
    while(environ[i])
    {
        newenv[i] = ft_strdup(environ[i]);
        // ft_printf("%s\n", newenv[i]);
        i++;
    }
    return (newenv);
}

void    ft_print_env(char **env, char *var, int len)
{
    char    *tmp;
    int     i;

    i = 0;
    while(env[i] && var == NULL)
    {
        ft_printf("%d = %s\n", i, env[i]); 
        i++;
    }
    while(env[i] && var != NULL)
    {
        if (!(ft_strncmp(env[i], var, len)))
        {
            tmp = ft_strdup(env[i]);
            ft_bzeroall(env[i]);
            ft_strcpy(env[i], var);
            ft_printf("%d = %s\n", i, env[i]);
            ft_bzeroall(env[i]);
            ft_strcpy(env[i], tmp);
            free(tmp);
            if (env[i + 1] == NULL)
                break ;
            else
                i++;
        }
        ft_printf("%d = %s\n", i, env[i]); 
        i++;
    }
}