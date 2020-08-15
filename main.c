/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:56:15 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/16 00:02:25 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// void    ft_handler(int s)
// {
//     signal(SIGINT, ft_handler);
//     write(1, "\r$>   ", 6);
//     write(1, "\r$> ", 4);
//     write(1, "\n$> ", 4);
// }

void    ft_error(char *str)
{
    ft_printf("%s", str);
    fsh_exit(NULL, NULL, NULL);
}

char    ft_find_split_char(char *line)
{
    char    sym;

    if (ft_strchr(line, ' '))
        sym = ' ';
    else if (ft_strchr(line, '\t'))
        sym = '\t';
    else if (ft_strchr(line, '\r'))
        sym = '\r';
    else if (ft_strchr(line, '\n'))         // ??
        sym = '\n';
    else if (ft_strchr(line, '\a'))
        sym = '\a';
    else
        sym = 0;
    return (sym);
}

char    *fsh_read_line(int fd, char *line)
{
    if ((get_next_line(fd, &line)) < 0)
        ft_error("\nfsh: readline error\n");
    return(line);
}

int     fsh_split_line(char *line, char **args)
{
    char    sym;
    int     i;

    if ((sym = ft_find_split_char(line)))
        args = ft_strsplit(line, sym);          // need to process the argument string normally
    i = 0;
    // while(args[i])                              //
        // ft_printf("%s\n", args[i++]);           // test
    return(EXIT_SUCCESS);
}














#define READ_SIZE 256

// static char line[256]; 

void    ft_null(t_sort *stsort)
{
    sort->flag = 0;
    sort->i = 0;
    sort->j = 0;
    sort->sym = 0;
    sort->sort = NULL;
}


void    ft_sort(char *tmp, char **names, t_sort *stsort)
{
    int     flag;
    int     j;
    int     i;
    int     sym;
    
    j = 0;
    flag = 0;
    stsort->sort = NULL;
    i = 0;
    while(names[i])
    {
        sym = 0;
        while (tmp[sym])
        {
            if (tmp[sym] == names[i][sym])
            {
                stsort->sort[j] = names[i];
                flag == 0 ? j++ : j;
                flag = 1;
            }
            sym++;
        } 
        flag = 0;
        i++;
    }
    stsort->sort[j] = NULL;
    if (names[i + 1] != NULL)
        ft_sort(tmp, stsort->sort, stsort);
}

int     ft_find_sp(char line[READ_SIZE])
{
    int     i;

    i = ft_strlen(line);
    while (i >= 0)
    {
        if (line[i] == ' ')
            return(i + 1);
        i--;
    }
    return(-1);
}

void   ft_autocomplete(int fd, char line[READ_SIZE])
{
    struct  dirent  *dirp;
    DIR             *dp;
    char            **names;
    char            *path;
    char            *tmp;
    int             space;
    int             len;
    int             i;
    t_sort          stsort;
    
    ft_null(&stsort);
    path = ft_memalloc(BUFSIZ);
    if (!(names = (char **)malloc(sizeof(char *) * 1)))
        ft_error("malloc error");
    names[1] = NULL;
    getcwd(path, BUFSIZ);
    dp = opendir(path);
    space = 0;
    i = 0;
    if (!(space = ft_find_sp(line)) != -1)
    {
        len = ft_strlen(line);
        tmp = ft_memalloc(len - space);
        tmp = ft_strdup(&line[space]);   
        while(dirp = readdir(dp))
        {
            names[i] = ft_strdup(dirp->d_name);
            i++;
        }
        names[i] = NULL;
        ft_sort(tmp, names, stsort);
        // i = 0;
        // while(names[i])
        // {
            
        // }
    }
    
} 

void    sig_hand(int sig)
{ 
    (void)sig;
    signal(SIGINT, sig_hand);
    write(1, "\r$>   ", 6);
    write(1, "\r$> ", 4);
    write(1, "\n$> ", 4);
}

void    readline(int fd, char line[READ_SIZE])
{
    struct termios  old_termios;
    struct termios  new_termios;
    int             len;
    
    tcgetattr(0, &old_termios);
    signal(SIGINT, sig_hand);
    new_termios = old_termios;
    new_termios.c_cc[VINTR]  = 3;                                   // ^C
    new_termios.c_cc[VEOF] = 9;                                     // ^tab
    tcsetattr(0, TCSANOW, &new_termios);
    len = 0;
    while(1)
    {
        len = read(0, line, READ_SIZE); 
        line[len] = '\0';
        if(len == 0) 
            continue ;
        if(len > 0)
        {
            if(line[len - 1] == 10)                                     // enter
                break ;
            if(line[len - 1] != 10)                                     // tab
               ft_autocomplete(fd, line);
        }
    }
    tcsetattr(0, TCSANOW, &old_termios);
}

void    fsh_loop(char **newenv, char **environ)
{
    // char    *line;
    char    line[READ_SIZE];
    char    **args;
    int     status;

    status = 1;
    args = malloc(sizeof(char *) * (1 + 1));
    while(status)
    {
        // signal(SIGINT, ft_handler);
        ft_printf("$> ");
        
        status = fsh_read_line(FD_MIN_SHELL, line);             // read next str
        // printf("%s\n", line);
        // fsh_split_line(line, args);                        // split args
        args = ft_strsplit(line, ' ');
        
        // p[0] = ft_strdup("cd");
        // p[1] = ft_strdup("../");
        // p[2] = NULL;
        
        // p[0] = ft_strdup("help");
        // p[0] = ft_strdup("ls");
        // p[1] = NULL;
        
        // int i = 0;
        // while(environ[i])
            // i++;       
        // environ[i] = ft_strdup("QWE=");  

        // args[0] = ft_strdup("cd");
        // args[1] = ft_strdup("~");
        // args[1] = ft_strdup("wergb\"\"qwer");
        // args[3] = NULL;
        // args[1] = ft_strdup("QWE");
        // args[2] = NULL;
        // args[2] = ft_strdup("zxc");
        // args[3] = NULL;
        status = fsh_execute(args, newenv, environ);                           // return status var
    }
}

int     main(int argc, char **argv)
{
    extern char **environ;
    char        **newenv;
    // Load config files
    // newenv = fsh_config((const char **)environ);
    //Run command loop
    (void)argc;
    (void)argv;
    fsh_loop(newenv, environ);
    // exit(0);
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
