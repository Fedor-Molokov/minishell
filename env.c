/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 05:29:13 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/13 15:56:02 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char     ***ft_load_config_file(const char **environ)
{
    char    **tmp;
    char    ***newenv;
    int     i;
    int     j;

    i = 0;
    j = 0;
    tmp = NULL;
    newenv = NULL;
    while (environ[i])
        i++;
    newenv = malloc(sizeof(char **) * (i + 1));
    if (NULL == newenv)
        return (NULL);
    newenv[i] = NULL;
    j = 0;
    while (j < i)
    {
        newenv[j] = malloc(sizeof(char *) * 3);
        newenv[j][0] = NULL;
        newenv[j][1] = NULL;
        newenv[j][2] = NULL;
        j++;
    }
    i = 0;
    while(environ[i])
    {
        tmp = ft_strsplit(environ[i], '=');
        newenv[i][0] = ft_strdup(tmp[0]);
        newenv[i][1] = ft_strdup(tmp[1]);
        free(tmp[0]);
        free(tmp[1]);
        ft_printf("%s\n", newenv[i][0]);
        i++;
    }
    // newenv[++i] 
    // i = 0;
    // while(newenv[i++])
    //     ft_printf("%s\n", newenv[i][0]);
    return (newenv);
}