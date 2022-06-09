/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:37:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/09 18:37:49 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	g_shell;

int	parsing_prompt(void)
{
	size_expand(0, 0);
	if (lexer_empty_line() == 1)
		return (1);
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

static void	check_if_parsing_valid(void)
{
	if (lexer_prompt() == 0)
	{
		if (parsing_prompt() == 0)
		{
			dispatch_here_doc(0, 0);
			if (g_shell.is_in_hd != 2)
				dispatch_exec(0, 0);
		}
	}	
}

void	minishell(int i)
{
	signal(SIGINT, sighandler_int);
	signal(SIGQUIT, sighandler_int);
	while (1)
	{
		g_shell.in_prog = 0;
		g_shell.is_in_hd = 0;
		g_shell.line = readline(MINISHELL);
		if (g_shell.line == NULL)
		{
			printf(" exit\n");
			free(g_shell.line);
			ft_free(g_shell.gc);
			exit(0);
		}
		add_history(g_shell.line);
		g_shell.gc2 = ft_gcnew(NULL, NULL);
		ft_gcadd_back(g_shell.gc2, ft_gcnew(g_shell.line, g_shell.gc2));
		if (i++ == 0)
			ft_pwd();
		check_if_parsing_valid();
		ft_free(g_shell.gc2);
	}
}

int	main(int argc, char **argv, char *env[])
{
	char	*str;

	(void)argc;
	(void)argv;
	g_shell.gc = ft_gcnew(NULL, NULL);
	g_shell.gc2 = NULL;
	g_shell.lst_env = get_env(env, g_shell.gc);
	if (!g_shell.lst_env)
	{
		ft_pwd();
		str = ft_strjoin("PWD=", g_shell.pwd);
		if (!str)
			ft_error("error strjoin du main");
		ft_export(str);
		ft_export("SHLVL=1");
	}
	minishell(0);
}
