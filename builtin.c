/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:59:49 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/14 21:00:25 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int     fsh_cd(char **args, char **newenv, char **environ);
int     fsh_help(char **args, char **newenv, char **environ);
int     fsh_echo(char **args, char **newenv, char **environ);
int     fsh_setenv(char **args, char **newenv, char **environ);
int     fsh_unsetenv(char **args, char **newenv, char **environ);
int     fsh_env(char **args, char **newenv, char **environ);
int     fsh_exit(char **args, char **newenv, char **environ);
static int  (*builtin_func[]) (char **, char **, char **) = 
{
    &fsh_cd, &fsh_help, &fsh_exit, &fsh_env, &fsh_setenv
};
static char *builtin_str[] = 
{
    "cd", "help", "exit", "env", "setenv", "unsetenv", "echo"
};

int     fsh_num_builtins()
{
  return (sizeof(builtin_str) / sizeof(char *));
}

int     fsh_launch(char **args)
{
    pid_t pid;
    pid_t wpid;
    int   status;

    pid = fork();
    if (pid == 0) 
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
        perror("fsh");
        }
        exit(EXIT_FAILURE);
    } 
    else if (pid < 0)
    {
        // Error forking
        perror("fsh");
    }
    else
    {
        // Parent process
        do
        {
        wpid = waitpid(pid, &status, WUNTRACED);
        } 
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (1);
}

int     fsh_execute(char **args, char **newenv, char **environ)
{
    int     i;
    int     count;
    
    count = fsh_num_builtins() - 1;
    if (args[0] == NULL)
    {
        // An empty command was entered.
        return (1);
    }
    i = 0;
    while(strcmp(args[0], builtin_str[i]) != 0 && i < count)
        i++;   
    if (strcmp(args[0], builtin_str[i]) == 0)
        return ((*builtin_func[i])(args, newenv, environ));
    return (fsh_launch(args));
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
  if (args[1] == NULL) 
  {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } 
  else 
  {
    if (chdir(args[1]) != 0) 
    {
      perror("fsh");
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
    char    *varname;
        
    if (args[1] == NULL)
        ft_print_env(environ, NULL, 0);
    else if (args[1] != NULL)
    {
        // len = ft_strlen(args[1]);
        len = ft_strnchr(args[1], '=');
        // if ((len = ft_strnchr(args[1], '=') > -1))
        // {
            varname = ft_strdup(args[1]);
            char *arname = ft_strndup(args[1], len);
            ft_printf("%s\n", varname);
            ft_printf("%s\n", arname);
            // ft_print_env(environ, varname, len - 1);
        // }
        // else if ((len = ft_strnchr(args[1], '=') == -1))
        // {
        //     varname = ft_memalloc(len + 1);
        //     varname[len] = '=';
        //     ft_strcpy(varname, args[1]);
        //     ft_print_env(environ, varname, len);
        // }
    }
    (void)newenv;
    return (1);
}

int     fsh_setenv(char **args, char **newenv, char **environ)
{
    int     i;
    int     len;

    i = 0;
    while (newenv[i])
        i++;
    len = ft_strlen(args[1]);
    if (!(newenv[i] = (char *)malloc(sizeof(char) * (len + 2))))
        ft_error("malloc error\n");
    ft_strcpy(newenv[i], args[1]);
    newenv[i][len] = '=';
    newenv[i][len + 1] = '\0';
    newenv[i + 1] = NULL;
    (void)environ;
    return (1);
}