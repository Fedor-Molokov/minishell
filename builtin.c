/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:59:49 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/13 02:17:36 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int     fsh_cd(char **args);
int     fsh_help(char **args);
int     fsh_echo(char **args);
int     fsh_setenv(char **args);
int     fsh_unsetenv(char **args);
int     fsh_env(char **args);
int     fsh_exit(char **args);
static int  (*builtin_func[]) (char **) = 
{
    &fsh_cd, &fsh_help, &fsh_exit
};
static char *builtin_str[] = 
{
    "cd", "help", "echo", "setenv", "unsetenv", "env", "exit"
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
        perror("lsh");
        }
        exit(EXIT_FAILURE);
    } 
    else if (pid < 0)
    {
        // Error forking
        perror("lsh");
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

int     fsh_execute(char **args)
{
    // builtin_str[0] = "cd";
    // builtin_str[1] = "help";
    // builtin_str[2] = "echo";
    // builtin_str[3] = "setenv";
    // builtin_str[4] = "unsetenv";
    // builtin_str[5] = "env";
    // builtin_str[7] = "exit";
    
    // builtin_func[0] = &fsh_cd;
    // builtin_func[1] = &fsh_help;
    // builtin_func[6] = &fsh_exit;
    // // *builtin_func[2] = &lsh_echo;
    // // *builtin_func[3] = &lsh_setenv;
    // // *builtin_func[4] = &lsh_unsetenv;
    // // *builtin_func[5] = &lsh_env;
    int i;

    if (args[0] == NULL)
    {
        // An empty command was entered.
        return 1;
    }
    i = 0;
    while(i < fsh_num_builtins())
    {
        if (strcmp(args[0], builtin_str[i]) == 0) 
            return (*builtin_func[i])(args);
        i++;
    }
  return (fsh_launch(args));
};

int     fsh_exit(char **args)
{
    (void)args;
    return (0);
}

int     fsh_cd(char **args)
{
  if (args[1] == NULL) 
  {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } 
  else 
  {
    if (chdir(args[1]) != 0) 
    {
      perror("lsh");
    }
  }
  return (1);
}

int     fsh_help(char **args)
{
    int i;
    printf("Stephen Brennan's LSH\n");
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
    return (1);
}