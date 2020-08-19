/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:56:15 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 17:24:08 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_prevpath;
char	*g_addpath;
int		g_ctrlc;
int		g_countaloc;
int		g_countpid;
pid_t	*g_pids;

void	ft_handler(int g_ctrlc)
{
	signal(SIGINT, ft_handler);
	g_ctrlc == 0 ? write(1, "\r$>   ", 6) : 1;
	g_ctrlc == 0 ? write(1, "\n$> ", 4) : 1;
	g_ctrlc == 0 ? write(1, "\r$> ", 4) : 1;
	g_ctrlc == 1 ? write(1, "\r", 1) : 1;
	g_ctrlc == 1 ? g_ctrlc = 0 : 1;
}

char	*fsh_read_line(int fd, char *line)
{
	if ((get_next_line(fd, &line)) < 0)
		ft_error("\nfsh: readline error\n");
	return (line);
}

int		ft_semi_colon_loop(char *line, char **args, char **environ)
{
	int		i;
	int		status;
	char	**semcolargs;

	status = 1;
	if (line[0] == ';' && line[1] == '\0')
		return (1);
	args = ft_strsplit(line, ';');
	i = 0;
	while (args[i] && status)
	{
		semcolargs = ft_strsplit(args[i], ' ');
		status = fsh_execute(semcolargs, environ);
		i++;
	}
	ft_vectordel(semcolargs);
	return (status);
}

void	fsh_loop(char **environ)
{
	int		status;
	char	*line;
	char	**args;

	status = 1;
	while (status)
	{
		g_ctrlc = 0;
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
		free(line);
		ft_vectordel(args);
	}
}

int		main(void)
{
	extern char **environ;

	g_countaloc = 1;
	g_countpid = 0;
	g_pids = ft_memalloc(BUFSIZ);
	g_prevpath = ft_memalloc(BUFSIZ + 1);
	g_addpath = ft_memalloc(BUFSIZ + 1);
	fsh_loop(environ);
	ft_memdel((void *)g_pids);
	free(g_prevpath);
	free(g_addpath);
	return (0);
}
