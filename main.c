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

char    *fsh_read_line(int fd)
{
    char    *line;
    // int     i;

    // i = 0;
    // while (get_next_line(fd, line))
            // ft_printf("%s\n", line[i++]);
    get_next_line(fd, &line);
    return(line);
}

void    fsh_loop()
{
    // char    **args;
    int     status;
    int     fd;
    int     i;
    char    *line;

    fd = 1;
    i = 0;
    // while (argv[i + 1])
    // {
        // line[i] = ft_strdup(argv[i + 1]);
        // i++;
    // }
    status = 1;
    while(status)
    {
    //     ft_printf("> ");
          
    //     args = fsh_split_line(line);
        line = fsh_read_line(fd);
        ft_printf("%s", line);
        // status = fsh_execute(args);
        // free(line);
        // free(args);
        i++;
        if (i > 3)
            exit(0);
    }
}

int     main(int argc, char **argv)
{
    char    *line;
    // Load config files

    //Run command loop
    line = NULL;
    (void)argc;
    (void)argv;
    fsh_loop();
    
    // Perform any shutdown/cleanup
    return (EXIT_SUCCESS);
}