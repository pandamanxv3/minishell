/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:41:48 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/20 15:45:36 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

int	lexer_empty_line(void)
{
	int	i;

	i = 0;
	while (g_shell.line[i] && g_shell.line[i] == ' ')
		i++;
	if (!g_shell.line[i])
		return (1);
	else
		return (0);
}	

static void	print_error_lexer(int return_lexer)
{
	if (return_lexer == 1)
	{
		g_shell.error = 130;
		printf("minishell: syntax error on quotation marks\n");
	}
	if (return_lexer == 2)
	{
		g_shell.error = 2;
		printf("minishell: syntax error near unexpected token `|'\n");
	}
	if (return_lexer == 3)
	{
		g_shell.error = 2;
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
}

int	lexer_prompt(void)
{
	int	return_lexer;

	g_shell.nb_proc = 1;
	if (lexer_empty_line() == 1)
		return (1);
	return_lexer = lexer_quote_and_pipe(0, 0);
	if (return_lexer == 1 || return_lexer == 2 || return_lexer == 3)
	{
		print_error_lexer(return_lexer);
		return (1);
	}
	return (0);
}
