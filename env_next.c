/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:13:35 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 14:23:33 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_find_home(char **env, char *tmp)
{
    int     i;

    i = 0;
    while(env[i])
    {
        if (ft_strncmp("HOME", env[i], 4) == 0)
        {
            tmp = ft_strdup(&env[i][5]);
            return(tmp);
        }
        i++;
    }
    return (NULL);
}

int     ft_count_quotation(char *str)
{
    int     i;
    int     count;

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

char    *ft_del_quotation(char *str)
{
    char    *tmp;
    int     count;
    int     len;
    int     i;
    int     j;
    
    len = ft_strlen(str);
    count = ft_count_quotation(str);
    if (!(tmp = ft_memalloc(len - count + 1)))
        ft_error("malloc error");
    j = 0;
    i = 0;
    while(str[i] && j < (len - count))
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

int     ft_sort_env(char **env, int i)
{
    if (env[i + 1] == NULL)
    {
        env[i] = NULL;
        return (1);
    }
    while(env[i])
    {
        env[i] = env[i + 1];
        i++;
    }
    env[i] = NULL;
    return (1);
}

void    ft_find_var(char *variable, char **env)
{
    int     equally;
    int     i;

    i = 0;
    while(env[i])
    {
        equally = ft_strnchr(env[i], '=');
        if (!(ft_strncmp(variable, env[i], equally)))
            ft_sort_env(env, i);
        i++;
    }
}

// int     ft_compare(char *name, char *value, char **env)
// {
//     int     equally;
//     int     i;

//     i = 0;
//     while(env[i])
//     {
//         equally = ft_strnchr(env[i], '=');
//         if (ft_strncmp(name, env[i], equally) == 0)
//         {
//             ft_bzeroall(&env[i][equally + 1]);
//             ft_strcpy(&env[i][equally + 1], value);
//             return (1);
//         }
//         i++;
//     }
//     return (0);
// }