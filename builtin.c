/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:59:49 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 14:20:11 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *g_builtin_str[] = 
{
    "cd", "help", "exit", "env", "setenv", "unsetenv", "echo", "\t"
};
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

int     fsh_exit(char **args, char **environ)
{
    (void)args;
    (void)environ;
    while(g_countpid > 0)
    {
        kill(g_pids[g_countpid], SIGTERM);
        g_countpid--;
    }
    return (0);
}

int     fsh_help(char **args, char **environ)
{
    int i;
    printf("Fedor Molokov's FSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");
    i = 0;
    while(i < fsh_num_builtins())
    {
        printf("  %s\n", g_builtin_str[i]);
        i++;
    }
    printf("Use the man command for information on other programs.\n");
    (void)args;
    (void)environ;
    return (1);
}

// int     fsh_env(char **args, char **environ)
// {
//     int     len;
//     int     equally;
//     char    *varname;
    
//     varname = NULL;
//     if (args[1] == NULL)
//         ft_print_env(environ, NULL, 0);
//     else if (args[1] != NULL)
//     {
//         len = ft_strlen(args[1]);
//         equally = ft_strnchr(args[1], '=');
//         if (equally == -1)
//         {
//             ft_printf("%s: %s: No such file or directory\n",args[0], args[1]);
//             return (1);
//         }
//         if (len == equally)
//         {
//             varname = ft_strdup(args[1]);
//             ft_print_env(environ, varname, len);
//         }
//         else if (len != equally)
//         {
//             varname = ft_memalloc(len + 1);
//             varname[len] = '=';
//             ft_strcpy(varname, args[1]);
//             ft_print_env(environ, varname, equally);
//         }
//         free(varname);
//     }
//     return (1);
// }

// int     fsh_setenv(char **args, char **environ)
// {
//     int     i;
//     int     len1;
//     int     len2;

//     i = 0;
//     while (environ[i])
//         i++;
//     args[1] == NULL ? fsh_env(args, environ) : 1;
//     if (args[1] && args[2] == NULL)
//     {
//         if (ft_strchr(args[1], '='))
//         {
//             ft_printf("setenv: Variable name must contain alphanumeric characters.\n");
//             return (1);
//         }
//         len1 = ft_strlen(args[1]);
//         if (!(environ[i] = (char *)malloc(sizeof(char) * (len1 + 2))))
//             ft_error("malloc error\n");
//         ft_strcpy(environ[i], args[1]);
//         environ[i][len1] = '=';
//         environ[i][len1 + 1] = '\0';
//         environ[i + 1] = NULL;
//     }
//     else if (args[1] != NULL && args[2])
//     {
//         if (ft_compare(args[1], args[2], environ))
//             return (1);
//         len1 = ft_strlen(args[1]);
//         len2 = ft_strlen(args[2]);
//         if (!(environ[i] = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
//             ft_error("malloc error\n");
//         ft_strcpy(environ[i], args[1]);
//         ft_strcpy(&environ[i][len1], "=");
//         ft_strcpy(&environ[i][len1 + 1], args[2]);
//         environ[i][len1 + len2 + 2] = '\0';
//         environ[i + 1] = NULL;
//     }
//     return (1);
// }

int     fsh_unsetenv(char **args, char **environ)
{
    if (args[1] == NULL)
    {
        ft_printf("unsetenv: Too few arguments.\n");
        return (1);
    }
    if (ft_strchr(args[1], '='))
        return (1);
    if (args[1])
        ft_find_var(args[1], environ);
    return (1);
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
        }
    }
    free(path);
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

int     fsh_num_builtins()
{
  return (sizeof(g_builtin_str) / sizeof(char *));
}

int     fsh_execute(char **args, char **environ)
{
    int     i;
    int     count;
    int     (*builtin_func[]) (char **, char **) = 
    {
        &fsh_cd, &fsh_help, &fsh_exit, &fsh_env, &fsh_setenv, &fsh_unsetenv, &fsh_echo, &fsh_tab
    };
    
    if (args[0] && (ft_strcmp(args[0], "g_ctrlc") == 0) && args[1] == NULL)
        g_ctrlc = 1;
    count = fsh_num_builtins() - 1;
    if (args[0] == NULL)
        return (1);
    i = 0;
    while(ft_strcmp(args[0], g_builtin_str[i]) != 0 && i < count)
        i++;   
    if (ft_strcmp(args[0], g_builtin_str[i]) == 0)
        return ((*builtin_func[i])(args, environ));
    return (fsh_launch(args, environ));
}