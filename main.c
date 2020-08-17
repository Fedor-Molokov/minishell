/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:56:15 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/17 20:15:46 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char    *prevpath;
char    *addpath;

void    ft_handler(int s)
{
    signal(SIGINT, ft_handler);
    write(1, "\r$>   ", 6);
    write(1, "\r$> ", 4);
    write(1, "\n$> ", 4);
}

void    ft_error(char *str)
{
    ft_printf("%s", str);
    fsh_exit(NULL, NULL, NULL);
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


//     args = malloc(sizeof(char *) * (2 + 1));
    
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

//     args[0] = ft_strdup("cd");
//     args[1] = ft_strdup("-");
//     // args[1] = ft_strdup("wergb\"\"qwer");
//     // args[3] = NULL;
//     // args[1] = ft_strdup("QWE");
//     args[2] = NULL;
//     // args[2] = ft_strdup("zxc");
//     // args[3] = NULL;
//     status = fsh_execute(args, newenv, environ);                           // return status var
// }

void    fsh_loop(char **newenv, char **environ)
{
    int     status;
    char    *line;
    char    **args;
    // int     count;
    
    // count = 0;
    status = 1;
    while(status)
    {
        signal(SIGINT, ft_handler);
        ft_printf("$> ");

        line = fsh_read_line(FD_MIN_SHELL, line);           // read next str
        // printf("%s\n", line);
        args = ft_strsplit(line, ' ');                      // split args
        // if (count > 0 && args[0][0] == 'i' && args[0][1] == 't')
        // {
        //     ft_bzeroall(args[0]);
        //     ft_bzeroall(args[1]);
        // }
        //     char	*path;
        // FILE	*file;
        // path = ft_memalloc(BUFSIZ);
        // getcwd(path, BUFSIZ);
        // file = fopen(path, "r");
        // fflush(file);
        // free(path);
        status = fsh_execute(args, newenv, environ);        // return status var
        // ft_memdel(args);
        // ft_bzeroall(line);
        // int i = 0;
        // while(args[i])
        // {
        //     ft_bzeroall(args[i]);
        //     i++;
        // }
        // count++;
    }
}





// void    fsh_loop(char **newenv, char **environ)
// {
//     int     status;
//     char    *line;
//     char    **args;
    
//     status = 1;
//     // while(status)
//     // {
//         // signal(SIGINT, ft_handler);
//         // ft_printf("$> ");
        
//         // line = fsh_read_line(FD_MIN_SHELL, line);           // read next str
//         // printf("%s\n", line);
//         // fsh_split_line(line, args);             
//         ft_strcpy(line, "echo it works");          
//         args = ft_strsplit(line, ' ');
//         status = fsh_execute(args, newenv, environ);        
                     
//         ft_strcpy(line, "pwd");          
//         args = ft_strsplit(line, ' ');                      
//         status = fsh_execute(args, newenv, environ);        // return status var
//     // }
// }



int     main(int argc, char **argv)
{
    extern char **environ;
    char        **newenv;
    // Load config files
    // newenv = fsh_config((const char **)environ);
    //Run command loop
    prevpath = ft_memalloc(BUFSIZ + 1);
    addpath = ft_memalloc(BUFSIZ + 1);
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
