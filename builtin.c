/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:59:49 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/18 01:13:14 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
int             fsh_cd(char **args, char **newenv, char **environ);
int             fsh_help(char **args, char **newenv, char **environ);
int             fsh_echo(char **args, char **newenv, char **environ);
int             fsh_setenv(char **args, char **newenv, char **environ);
int             fsh_unsetenv(char **args, char **newenv, char **environ);
int             fsh_env(char **args, char **newenv, char **environ);
int             fsh_exit(char **args, char **newenv, char **environ);
int             fsh_tab(char **args, char **newenv, char **environ);
static int  (*builtin_func[]) (char **, char **, char **) = 
{
    &fsh_cd, &fsh_help, &fsh_exit, &fsh_env, &fsh_setenv, &fsh_unsetenv, &fsh_echo, &fsh_tab
};
static char *builtin_str[] = 
{
    "cd", "help", "exit", "env", "setenv", "unsetenv", "echo", "\t"
};
extern char *prevpath;
extern char *addpath;

int     fsh_num_builtins()
{
  return (sizeof(builtin_str) / sizeof(char *));
}

void    fsh_execve(char *path, char **args, char **environ)
{
    if (execve(path, args, environ) == -1)
    {
        perror("fsh");
    }
    exit(EXIT_FAILURE);
}

void    fsh_launch_next(char **args, char **environ)
{
    char    *path;
    
    path = ft_strdup("/usr/bin/");
    path = ft_strjoin(path, args[0]);
    if (access(path, 0) != -1)
        fsh_execve(path, args, environ);
    else
    {
        free(path);
        path = ft_strdup("/bin/");
        path = ft_strjoin(path, args[0]);
        if (access(path, 0) != -1)
            fsh_execve(path, args, environ);
        else
            ft_printf("%s: Command not found.\n", args[0]);
        free(path);
    }
}

int     fsh_launch(char **args, char **environ)
{
    pid_t   pid;
    pid_t   wpid;
    int     status;

    status = 1;
    pid = fork();
    if (pid == 0) 
    {
        fsh_launch_next(args, environ);
        // if (execvp(args[0], args) == -1)
        // {
        // perror("fsh");
        // }
    } 
    else if (pid < 0)
    {
        perror("fsh");
    }
    else
    {
        while (!WIFEXITED(status) && WIFSIGNALED(status))
            wpid = waitpid(pid, &status, WUNTRACED);
        
        // do
        // {
        // wpid = waitpid(pid, &status, WUNTRACED);
        // } 
        // while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (1);
}

int     fsh_execute(char **args, char **newenv, char **environ)
{
    int             i;
    int             count;
    extern int      cat;
    
    if (args[0] && (ft_strcmp(args[0], "cat") == 0) && args[1] == NULL)
        cat = 1;
    count = fsh_num_builtins() - 1;
    if (args[0] == NULL)
        return (1);
    i = 0;
    while(ft_strcmp(args[0], builtin_str[i]) != 0 && i < count)
        i++;   
    if (ft_strcmp(args[0], builtin_str[i]) == 0)
        return ((*builtin_func[i])(args, newenv, environ));
    return (fsh_launch(args, environ));
}

int     fsh_tab(char **args, char **newenv, char **environ)
{
    (void)args;
    (void)newenv;
    (void)environ;
    return (1);
}

int     fsh_exit(char **args, char **newenv, char **environ)
{
    (void)args;
    (void)newenv;
    (void)environ;
    return (0);
}

int     fsh_cd(char **args, char **newenv, char **environ)
{
    char    *tmp = NULL;
    
    if (args[1] == NULL) 
        ft_error("fsh: expected argument to \"cd\"\n");
    else if (args[1][0] == '-' && args[1][1] == '\0')
    {
        if (prevpath[0] == '\0' && addpath[0] == '\0')
        {
            ft_printf("fsh: No such file or directory\n");
            return (1);
        }
        else
        {
            if (addpath[0] != '\0')
            {
                ft_bzeroall(prevpath);
                getcwd(prevpath, BUFSIZ);
                chdir(addpath);
                ft_bzeroall(addpath);
            }
            else
            {
                ft_bzeroall(addpath);
                getcwd(addpath, BUFSIZ);
                chdir(prevpath);
            }
        }
    }
    else
    {
        ft_bzeroall(prevpath);
        ft_bzeroall(addpath);
        getcwd(prevpath, BUFSIZ);
        if (args[1][0] == '~')
        {
            tmp = ft_find_home(environ, tmp);
            if (args[1][1] != '\0')
                tmp = ft_strjoin(tmp, &args[1][1]); 
            chdir(tmp);
            free(tmp);
        }
        else if (chdir(args[1]) != 0)
        {
            ft_error("fsh: expected argument to \"cd\"\n");
            return (1);
        }
    }
    (void)newenv;
    (void)environ;
    return (1);
}

int     fsh_help(char **args, char **newenv, char **environ)
{
    int i;
    printf("Fedor Molokov's FSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");
    i = 0;
    while(i < fsh_num_builtins())
    {
        printf("  %s\n", builtin_str[i]);
        i++;
    }
    printf("Use the man command for information on other programs.\n");
    (void)args;
    (void)newenv;
    (void)environ;
    return (1);
}

int     fsh_env(char **args, char **newenv, char **environ)
{
    int     len;
    int     equally;
    char    *varname;
        
    if (args[1] == NULL)
        ft_print_env(environ, NULL, 0);
    else if (args[1] != NULL)
    {
        len = ft_strlen(args[1]);
        equally = ft_strnchr(args[1], '=');
        if (equally == -1)
        {
            ft_printf("%s: %s: No such file or directory\n",args[0], args[1]);
            return (1);
        }
        if (len == equally)
        {
            varname = ft_strdup(args[1]);
            ft_print_env(environ, varname, len);
        }
        else if (len != equally)
        {
            varname = ft_memalloc(len + 1);
            varname[len] = '=';
            ft_strcpy(varname, args[1]);
            ft_print_env(environ, varname, equally);
        }
    }
    (void)newenv;
    return (1);
}

int     fsh_setenv(char **args, char **newenv, char **environ)
{
    int     i;
    int     len1;
    int     len2;

    i = 0;
    while (environ[i])
        i++;
    args[1] == NULL ? fsh_env(args, newenv, environ) : 1;
    if (args[1] && args[2] == NULL)
    {
        if (ft_strchr(args[1], '='))
        {
            ft_printf("setenv: Variable name must contain alphanumeric characters.\n");
            (void)newenv;
            return (1);
        }
        len1 = ft_strlen(args[1]);
        if (!(environ[i] = (char *)malloc(sizeof(char) * (len1 + 2))))
            ft_error("malloc error\n");
        ft_strcpy(environ[i], args[1]);
        environ[i][len1] = '=';
        environ[i][len1 + 1] = '\0';
        environ[i + 1] = NULL;
    }
    else if (args[1] != NULL && args[2])
    {
        if (ft_compare(args[1], args[2], environ))
        {
            (void)newenv;
            return (1);
        }
        len1 = ft_strlen(args[1]);
        len2 = ft_strlen(args[2]);
        if (!(environ[i] = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
            ft_error("malloc error\n");
        ft_strcpy(environ[i], args[1]);
        ft_strcpy(&environ[i][len1], "=");
        ft_strcpy(&environ[i][len1 + 1], args[2]);
        environ[i][len1 + len2 + 2] = '\0';
        environ[i + 1] = NULL;
    }
    (void)newenv;
    return (1);
}

int     fsh_unsetenv(char **args, char **newenv, char **environ)
{
    if (args[1] == NULL)
        ft_printf("unsetenv: Too few arguments.\n");
    if (ft_strchr(args[1], '='))
        return (1);
    if (args[1])
        ft_find_var(args[1], environ);
    (void)newenv;
    return (1);
}