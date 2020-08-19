/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 15:42:57 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 16:57:21 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_countpid;
extern int		g_countaloc;
extern int		g_ctrlc;
extern pid_t	*g_pids;


void    fsh_execve(char *path, char **args, char **environ)
{
    if (execve(path, args, environ) == -1)
        ft_printf("fsh: execve error\n");
    exit(EXIT_FAILURE);
}

void     ft_realloc(pid_t *g_pids)
{
    pid_t   *tmp;

    g_countaloc++;
    tmp = ft_memdup(g_pids);
    free(g_pids);
    g_pids = ft_memalloc(BUFSIZ * g_countaloc);
    g_pids = ft_memcpy(g_pids, tmp, (BUFSIZ * g_countaloc));
    free(tmp);
}

void    fsh_launch_n_next(char **args, char **environ, char *path, char *tmp)
{
    free(path);
    tmp = ft_strdup("/bin/");
    path = ft_strjoin(tmp, args[0]);
    free(tmp);
    if (access(path, 0) != -1)
        fsh_execve(path, args, environ);
    else
    {
        free(path);
        tmp = ft_strdup("/usr/bin/");
        path = ft_strjoin(tmp, args[0]);
        free(tmp);
        if (access(path, 0) != -1)
            fsh_execve(path, args, environ);
        else if (!(args[0][0] == '\t'))
            ft_printf("%s: Command not found.\n", args[0]);
    }
    free(path);
}

void    fsh_launch_next(char **args, char **environ)
{
    char    *path;
    char    *tmp;
    
    path = ft_strdup(args[0]);
    if (access(args[0], 0) != -1)
        fsh_execve(path, args, environ);
    else
    {
        free(path);
        path = ft_memalloc(BUFSIZ);
        getcwd(path, BUFSIZ);
        tmp = ft_strjoin(path, "/");
        free(path);
        path = ft_strjoin(tmp, args[0]);
        free(tmp);
        if ((access(path, 0) != -1))
            fsh_execve(path, args, environ);
        else
            fsh_launch_n_next(args, environ, path, tmp);
    }
}

int     fsh_launch(char **args, char **environ)
{
    pid_t   pid;
    pid_t   wpid;
    int     status;

    pid = fork();
    if (pid == 0) 
        fsh_launch_next(args, environ);
    else if (pid < 0)
        ft_printf("fsh: fork error\n");
    else
    {
        g_ctrlc = 1;
        g_pids[g_countpid] = pid;
        if (g_countpid == (BUFSIZ * g_countaloc))
            ft_realloc(g_pids);
        g_countpid++;
        wpid = waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
            wpid = waitpid(pid, &status, WUNTRACED);
    }
    return (1);
}