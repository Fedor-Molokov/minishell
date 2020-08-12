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

char    *fsh_read_line(int fd, char *line)
{
    if ((get_next_line(fd, &line)) < 0)
        ft_error("\nfsh: readline error\n");

    return(line);
}

void    fsh_loop()
{
    char    **args;
    int     status;
    char    *line;

    status = 1;
    while(status)
    {
        ft_printf("$> ");
        line = fsh_read_line(FD, line);                   // read next str
        // args = fsh_split_line(line);             // split args
        // status = fsh_execute(args);              // return stat var
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