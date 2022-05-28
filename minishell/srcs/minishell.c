/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:37:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/28 06:45:09 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	g_shell;

int	parsing_prompt(void)
{
	if (malloc_processes() == 1)
		return (1);
	if (init_processes() == 1)
		return (1);
	if (init_tokens() == 1)
		return (1);
	all_token_types();
	return (0);	
}

void	minishell(void)
{
	while (1)
	{
		signal(SIGINT, sighandler_int);
		signal(SIGQUIT, sighandler_quit);
		g_shell.line = readline(MINISHELL);
		g_shell.gc2 = ft_gcnew(NULL, NULL);
		if (lexer_prompt() == 0)
		{
			if (parsing_prompt() == 1)
				exit(1); //?
			//printf("%s\n", g_shell.tab_proc[0].tab_token[0].word);
			dispatch_exec();
		}
		add_history(g_shell.line);
		free(g_shell.line);
		ft_free(g_shell.gc2);
	}
}

int	main(int argc, char **argv, char *env[])
{
	(void)argc;
	(void)argv;
	if (env == NULL)
	{
		write(2, "error: no environnements\n", 25);
		exit(EXIT_FAILURE);
	}
	g_shell.gc = ft_gcnew(NULL, NULL);
	g_shell.lst_env = get_env(env, g_shell.gc);
	minishell();
}
