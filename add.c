/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:38:34 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/16 03:55:28 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    ft_sort(char *tmp, char **names, char **sort)
{
    int     flag;
    int     j;
    int     i;
    int     sym;
    
    if (sort == NULL)
    {
        sort = malloc(sizeof(char *) * 1);
        sort = NULL;
    }
    j = 0;
    flag = 0;
    sort = NULL;
    i = 0;
    while(names[i])
    {
        sym = 0;
        while (tmp[sym])
        {
            if (tmp[sym] == names[i][sym])
            {
                sort[j] = NULL;
                sort[j] = ft_strdup(names[i]);
                flag == 0 ? j++ : j;
                flag = 1;
            }
            sym++;
        } 
        flag = 0;
        i++;
    }
    sort[j] = NULL;
    if (sort[0] && sort[1] != NULL)
        ft_sort(tmp, sort, NULL);
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

void   ft_autocomplete(char line[READ_SIZE])
{
    struct  dirent  *dp;
    DIR             *dirp;
    DIR             *kostyl;
    char            **names;
    char            *path;
    char            *tmp;
    int             space;
    int             len;
    int             i;
    char            **sort;
    
    // ft_null(&stsort);
    sort = malloc(sizeof(char *) * 1);
    // sort = NULL;
    path = ft_memalloc(BUFSIZ);
    if (!(names = (char **)malloc(sizeof(char *) * 1)))
        ft_error("malloc error");
    // names = NULL;
    getcwd(path, BUFSIZ);
    dirp = opendir(path);
    ft_printf("fd-2: %d\n", dirp->__dd_fd);
    space = 0;
    i = 0;
     ft_printf("-2\n");
    if ((space = ft_find_sp(line)) != -1)
    kostyl = dirp;
    {
         ft_printf("-1\n");
        len = ft_strlen(line);
        // tmp = NULL;
        // tmp = ft_memalloc(len - space);
        int a = ft_strlen(&line[space]);
        tmp = (char *)malloc(sizeof(char) * (a + 1));
        // tmp[a] = '\0';
        // tmp = ft_strdup(&line[space]);
        ft_strcpy(tmp, &line[space]);
        // len = ft_strlen(tmp);
        // tmp[len] = '\0';
         ft_printf("0: %s\n", tmp);
         errno = 0;
        ft_printf("fd-1: %d = %d\n", kostyl->__dd_fd,dirp->__dd_fd); 
        while((dp = readdir(dirp)) != NULL)
        {
            if (!(ft_strcmp(dp->d_name, ".git")))
                dirp = kostyl;
            if (dp == NULL)
                perror("readdir" );
            names[i] = NULL;
            ft_printf("fd0: %d = %d\n", kostyl->__dd_fd,dirp->__dd_fd);
             ft_printf("1: %s = %s, %p, %s\n", names[i], dp->d_name, dirp, tmp);
            names[i] = ft_strdup(dp->d_name);
            ft_printf("fd1: %d = %d\n", kostyl->__dd_fd,dirp->__dd_fd);
             ft_printf("2: %s = %s, %p, %s\n", names[i], dp->d_name, dirp, tmp);
            // if(names[i] == NULL)
            // {
            //     perror("error names");
            //     exit(1);
            // }   
            i++;
        }
        // printf("2,5: %s = %s, %p, %s\n", names[i], dp->d_name, dirp, tmp);
        if (dp == NULL)
            perror("readdir" );
        printf("3: %s = %s, %p, %s\n", names[i], dp->d_name, dirp, tmp);
        names[i] = NULL;
        sort = malloc(sizeof(char *) * 1);
        sort = NULL;
        ft_sort(tmp, names, sort);
         ft_printf("4\n");
        closedir(dirp);
        // i = 0;
        // while(names[i])
        // {
            
        // }
    }
    
} 