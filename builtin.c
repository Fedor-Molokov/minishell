/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:59:49 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/19 17:20:29 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_builtin_str[] =
{
	"cd", "help", "exit", "env", "setenv", "unsetenv", "echo", "\t"
};
extern int		g_countpid;
extern int		g_ctrlc;
extern pid_t	*g_pids;

int		fsh_help(char **args, char **environ)
{
	int		i;

	ft_printf("Fedor Molokov's FSH\n");
	ft_printf("Type program names and arguments, and hit enter.\n");
	ft_printf("The following are built in:\n");
	i = 0;
	while (i < fsh_num_builtins())
	{
		ft_printf("  %s\n", g_builtin_str[i]);
		i++;
	}
	ft_printf("Use the man command for information on other programs.\n");
	(void)args;
	(void)environ;
	return (1);
}

int		fsh_exit(char **args, char **environ)
{
	(void)args;
	(void)environ;
	while (g_countpid > 0)
	{
		kill(g_pids[g_countpid], SIGTERM);
		g_countpid--;
	}
	return (0);
}

int		fsh_num_builtins(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
}

int		fsh_execute(char **args, char **environ)
{
	int		i;
	int		count;
	int		(*builtin_func[8]) (char **, char **);

	builtin_func[0] = &fsh_cd;
	builtin_func[1] = &fsh_help;
	builtin_func[2] = &fsh_exit;
	builtin_func[3] = &fsh_env;
	builtin_func[4] = &fsh_setenv;
	builtin_func[5] = &fsh_unsetenv;
	builtin_func[6] = &fsh_echo;
	builtin_func[7] = &fsh_tab;
	if (args[0] && (ft_strcmp(args[0], "g_ctrlc") == 0) && args[1] == NULL)
		g_ctrlc = 1;
	count = fsh_num_builtins() - 1;
	if (args[0] == NULL)
		return (1);
	i = 0;
	while (ft_strcmp(args[0], g_builtin_str[i]) != 0 && i < count)
		i++;
	if (ft_strcmp(args[0], g_builtin_str[i]) == 0)
		return ((*builtin_func[i])(args, environ));
	return (fsh_launch(args, environ));
}
