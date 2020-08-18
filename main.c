/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:56:15 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/18 05:45:41 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char    *prevpath;
char    *addpath;
int     cat;
int     countaloc;
int     countpid;
pid_t   *pids;

void    ft_handler()
{
    signal(SIGINT, ft_handler);
    cat == 0 ? write(1, "\r$>   ", 6) : 1;
    cat == 0 ? write(1, "\n$> ", 4) : 1;
    cat == 0 ? write(1, "\r$> ", 4) : 1;
    cat == 1 ? write(1, "\r", 1) : 1;
    cat == 1 ? cat = 0 : 1;
}

void    ft_error(char *str)
{
    ft_printf("%s", str);
    fsh_exit(NULL, NULL);
}

char    *fsh_read_line(int fd, char *line)
{
    if ((get_next_line(fd, &line)) < 0)
        ft_error("\nfsh: readline error\n");
    return(line);
}

// void    fsh_loop(char **newenv, char **environ)
// {
//     int     status;
//     char    *line;
//     char    **args;

//     args = malloc(sizeof(char *) * (3 + 1));
    
//     // p[0] = ft_strdup("cd");
//     // p[1] = ft_strdup("../");
//     // p[2] = NULL;
    
//     // p[0] = ft_strdup("help");
//     // p[0] = ft_strdup("ls");
//     // p[1] = NULL;
    
//     // int i = 0;
//     // while(environ[i])
//         // i++;       
//     // environ[i] = ft_strdup("QWE=");  

//     args[0] = ft_strdup("\t");
//     args[1] = ft_strdup("\t");
//     args[2] = ft_strdup("\t");
//     // args[3] = NULL;
//     // args[1] = ft_strdup("QWE");
//     args[3] = NULL;
//     // args[2] = ft_strdup("zxc");
//     // args[3] = NULL;
//     status = fsh_execute(args, newenv, environ);                           // return status var
// }

int    ft_semi_colon_loop(char *line, char **args, char **environ)
{
    int     i;
    int     status;
    char    **semcolargs;
    
    status = 1;
    if (line[0] == ';' && line[1] == '\0')
        return(1);
    args = ft_strsplit(line, ';');
    i = 0;
    while(args[i] && status)
    {
        semcolargs = ft_strsplit(args[i], ' ');
        status = fsh_execute(semcolargs, environ);
        i++;
    }
    // free(semcolargs);
    return(status);
}

int     ft_find_semi_colon(char *line)
{
    int     i;

    i = 0;
    while(line[i])
    {
        if (line[i] == ';')
            return (1);
        i++;
    }
    return (0);
}

void    ft_del_tabs(char *line)
{
    int     i;

    i = 0;
    while(line[i])
    {
        if (line[i] == '\t')
            line[i] = ' ';
        i++;
    }
}

void    fsh_loop(char **environ)
{
    int     status;
    char    *line;
    char    **args;

    status = 1;
    while(status)
    {
        cat = 0;
        signal(SIGINT, ft_handler);
        ft_printf("$> ");
        line = fsh_read_line(FD_MIN_SHELL, line);           // read next str
        ft_del_tabs(line);
        if (ft_find_semi_colon(line))
            status = ft_semi_colon_loop(line, args, environ);
        else
        {
            args = ft_strsplit(line, ' ');                      // split args
            status = fsh_execute(args, environ);        // return status var
        }
    }
}

int     main(int argc, char **argv)
{
    extern char **environ;
    // Load config files
    // newenv = fsh_config((const char **)environ);
    //Run command loop
    // cat = 0;
    countaloc = 1;
    countpid = 0;
    // pids = (pid_t *)malloc(sizeof(pid_t) * BUFSIZ);
    pids = ft_memalloc(BUFSIZ);
    prevpath = ft_memalloc(BUFSIZ + 1);
    addpath = ft_memalloc(BUFSIZ + 1);
    (void)argc;
    (void)argv;
    fsh_loop(environ);
    return (0);
}

/*
   #include <unistd.h> 
#include <stdio.h> 
#include <termios.h> 
#include <signal.h> 
                                              //    autocomplete
void sig_hnd(int sig)
{ 
    (void)sig;
    printf("(VINTR)");
}

int main()
{
    struct termios old_termios, new_termios;
    setvbuf(stdout,NULL,_IONBF,0);
    tcgetattr(0,&old_termios);
    signal( SIGINT, sig_hnd );

  new_termios             = old_termios;
  new_termios.c_cc[VEOF]  = 3; // ^C
  new_termios.c_cc[VINTR] = 9; // ^tab
  tcsetattr(0,TCSANOW,&new_termios);

  char line[256]; 
  int len;
  do
  {
    len = read(0, line, 256); 
    line[len]='\0';
    if(len < 0) printf("(len: %i)",len);
    if(len == 0) printf("(VEOF)");
    if(len > 0)
    {
      if( line[len-1] == 10 ) printf("(line:'%.*s')\n",len-1,line);
      if( line[len-1] != 10 ) printf("(partial line:'%s')",line);
    }
  }while( line[0] != 'q' );

  tcsetattr(0,TCSANOW,&old_termios);
}*/




















/*
char    *path;
size_t  size;
                                        //    path;
size = BUFSIZ;  
path = ft_memalloc(size);
getcwd(path, size);
ft_printf("%s", path);
*/
