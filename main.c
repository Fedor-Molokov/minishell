/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:56:15 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/11 18:36:34 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    ft_error(char *str)
{
    ft_printf("%s", str);
    exit(EXIT_FAILURE);
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
    while(args[i])                              //
        ft_printf("%s\n", args[i++]);           // test
    return(EXIT_SUCCESS);
}

void    fsh_loop()
{
    char    **args = NULL;
    int     status;
    char    *line;

    status = 1;
    while(status)
    {
        ft_printf("$> ");
        line = fsh_read_line(FD_MIN_SHELL, line);             // read next str
        fsh_split_line(line, args);                           // split args
        // status = fsh_execute(args);                        // return status var
    }
}

int     main(int argc, char **argv)
{
    // Load config files

    //Run command loop
    (void)argc;
    (void)argv;
    fsh_loop();
    
    // Perform any shutdown/cleanup
    return (EXIT_SUCCESS);
}