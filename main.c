/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:56:15 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/18 06:37:30 by dmarsell         ###   ########.fr       */
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
        line = fsh_read_line(FD_MIN_SHELL, line);          
        ft_del_tabs(line);
        if (ft_find_semi_colon(line))
            status = ft_semi_colon_loop(line, args, environ);
        else
        {
            args = ft_strsplit(line, ' ');                     
            status = fsh_execute(args, environ);        
        }
    }
}

int     main()
{
    extern char **environ;
    countaloc = 1;
    countpid = 0;
    pids = ft_memalloc(BUFSIZ);
    prevpath = ft_memalloc(BUFSIZ + 1);
    addpath = ft_memalloc(BUFSIZ + 1);
    fsh_loop(environ);
    return (0);
}




















/*
char    *path;
size_t  size;
                                        //    path;
size = BUFSIZ;  
path = ft_memalloc(size);
getcwd(path, size);
ft_printf("%s", path);
*/
