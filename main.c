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

void    fsh_read_line(int fd, char *line)
{
    while (get_next_line(fd, &line))
            ft_printf("%s\n", line++);             
}

void    fsh_loop(char **argv)
{
    char    *line;
    char    **args;
    int     status;
    int     fd;
    
    fd = 0;
    while(status)
    {
        ft_printf("> ");
          
        args = fsh_split_line(line);
        fsh_read_line(fd, line);
        status = fsh_execute(args);
        free(line);
        free(args);
    }
}

int     main(int argc, char **argv)
{
    // Load config files

    //Run command loop
    fsh_llop(argv);
    
    // Perform any shutdown/cleanup
    return (EXIT_SUCCESS);
}