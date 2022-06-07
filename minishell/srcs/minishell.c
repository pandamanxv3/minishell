/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:37:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/07 11:42:40 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	g_shell;

int	parsing_prompt(void)
{
	size_expand(0, 0);
	if (lexer_empty_line() == 1)
		return (1);
	if (malloc_processes() == 1)
		return (1);
	if (init_processes() == 1)
		return (1);
	if (init_tokens() == 1)
		return (1);
	all_token_types();
	return (0);
}

void	minishell(int i)
{
	while (1)
	{
		signal(SIGINT, sighandler_int);
		signal(SIGQUIT, sighandler_int);
		g_shell.line = readline(MINISHELL);
		if (g_shell.line == NULL)
		{
			printf(" exit\n");
			free(g_shell.line);
			ft_free(g_shell.gc);
			exit(1);
		}
		g_shell.gc2 = ft_gcnew(NULL, NULL);
		ft_gcadd_back(g_shell.gc2, ft_gcnew(g_shell.line, g_shell.gc2));
		if (i++ == 0)
			ft_pwd();
		add_history(g_shell.line);
		if (lexer_prompt() == 0)
		{
			if (parsing_prompt() == 0)
				dispatch_exec(0, 0);
		}
		ft_free(g_shell.gc2);
	}
}

int	main(int argc, char **argv, char *env[])
{
	(void)argc;
	(void)argv;
	g_shell.gc = ft_gcnew(NULL, NULL);
	g_shell.lst_env = get_env(env, g_shell.gc);
	minishell(0);
}
