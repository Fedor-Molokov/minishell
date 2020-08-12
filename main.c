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

# define SIZE   1024

// char    *ft_cpycat(char *s1, char *s2)
// {
//     char    *tmp;

//     tmp = NULL;
//     tmp = ft_memalloc(ft_strlen(s1) + ft_strlen(s2));
//     tmp = ft_strcpy(tmp, s1);
//     tmp = ft_strncat(tmp, s2, ft_strlen(s2));
//     return (tmp);
// }

int     ft_home(char *line, char *tmp)
{

    line = ft_strdup(tmp);
    free(tmp);
    // line = ft_strncat()
    return (EXIT_FAILURE);
}

int     g_n_l(int fd, char **line)
{
    static char *str = NULL;
    char        *tmp;
    char        *buf;
    int         res;

    if (fd < 0)
    {
        ft_printf("error fd gnl\n");
        exit(1);
    }
    if (str == NULL)
        str = ft_memalloc(SIZE);
    tmp = ft_strncpy(ft_memalloc(SIZE), str, SIZE);
    buf = ft_memalloc(SIZE + 1);
    while(!(ft_strchr(tmp, '\n')))
    {
        if ((res = read(fd, buf, SIZE)) < 0)
            return(EXIT_FAILURE);
        if (res == 0)
            return (ft_home(*line, tmp));
        buf[res] = '\n';
        tmp = ft_strjoin(tmp, buf);
        // tmp = ft_cpycat(tmp, buf);
    }
    if (ft_strchr(tmp, '\n'))
        str = ft_strncpy(str, ft_strchr(tmp, '\n') + 1, SIZE);
    *line = ft_strdup(tmp);
    free(tmp);
    free(buf);
    return (EXIT_SUCCESS);
}

char    *fsh_read_line(int fd)
{
    char    *line;
    // int     i;

    // i = 0;
    // while (get_next_line(fd, line))
            // ft_printf("%s\n", line[i++]);

    // get_next_line(fd, &line);

    if (g_n_l(fd, &line))
    {
        ft_printf("Error g_n_l\n");
        exit(EXIT_FAILURE);
    }
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
        free(line);
        // status = fsh_execute(args);
        // free(line);
        // free(args);
        // i++;
        // if (i > 3)
        //     exit(EXIT_SUCCESS);
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