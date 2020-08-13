/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:59:49 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/13 17:20:45 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int     fsh_cd(char **args, char **newenv);
int     fsh_help(char **args, char **newenv);
int     fsh_echo(char **args, char **newenv);
int     fsh_setenv(char **args, char **newenv);
int     fsh_unsetenv(char **args, char **newenv);
int     fsh_env(char **args, char **newenv);
int     fsh_exit(char **args, char **newenv);
static int  (*builtin_func[]) (char **, char **) = 
{
    &fsh_cd, &fsh_help, &fsh_exit, &fsh_env
};
static char *builtin_str[] = 
{
    "cd", "help", "exit", "env", "echo", "setenv", "unsetenv"
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

int     fsh_execute(char **args, char **newenv)
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
        return ((*builtin_func[i])(args, newenv));
    return (fsh_launch(args));
}

int     fsh_exit(char **args, char **newenv)
{
    (void)args;
    (void)newenv;
    return (0);
}

int     fsh_cd(char **args, char **newenv)
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
  return (1);
}

int     fsh_help(char **args, char **newenv)
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
    return (1);
}

int     fsh_env(char **args, char **newenv)
{
    int     i;
    
    i = 0;
    while(newenv[i])
    {
        ft_printf("%s\n", newenv[i]); 
        i++;
    }
    (void)args;
    return (1);
}