/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:41:48 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/06 18:34:40 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	lexer_quote(int i)
{
	char	c;

	c = g_shell.line[i];
	i++;
	while (g_shell.line[i] != c)
	{
		if (!g_shell.line[i])
			return (-1);
		i++;
	}
	return (i);
}

static int	lexer_redir(int i)
{
	int	d;

	if ((g_shell.line[i] == '>' && g_shell.line[i + 1] == '<')
		|| (g_shell.line[i] == '<' && g_shell.line[i + 1] == '>'))
		return (-1);
	i++;
	if (g_shell.line[i] == '>' || g_shell.line[i] == '<')
		i++;
	if (g_shell.line[i] == '>' || g_shell.line[i] == '<' || !g_shell.line[i])
		return (-1);
	while (g_shell.line[i] == ' ')
	{
		i++;
		if (g_shell.line[i] == '\0')
			return (-1);			
	}
	d = i;
	while (g_shell.line[i] && g_shell.line[i] != '>' && g_shell.line[i] != '<'
		&& g_shell.line[i] != ' ' && g_shell.line[i] != '|')
	{
		if (g_shell.line[i] == '"' || g_shell.line[i] == '\'')
		{
			// printf("i before = %d\n", i);
			i = lexer_quote(i);
			if (i == -1)
				return (-1);
			// printf("i after = %d\n", i);
		}
		i++;
	}
	// puts("coucou");
	if (d == i)
		return (-1);
	if (g_shell.line[i - 1] == '"' || g_shell.line[i] == '\'')
		i = i + 1;
	// printf("i after = %d\n", i);
	return (i);
}

static int	lexer_pipe(int i, int k)
{
	int	j;

	j = i;
	g_shell.tab_index_pipes[k] = i;
	while (j > 0)
	{
		j--;
		if (g_shell.line[j] != ' ')
			break ;
	}
	if (g_shell.line[j] == ' ' || g_shell.line[j] == '|')
		return (-1);
	i++;
	while (g_shell.line[i])
	{
		if (g_shell.line[i] != ' ')
			break ;
		i++;
	}
	g_shell.nb_proc++;
	if (!g_shell.line[i] || g_shell.line[i] == '|')
		return (-1);
	return (i);
}

static int	lexer_quote_and_pipe(void)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (g_shell.line[i])
	{
		if (g_shell.line[i] == '>' || g_shell.line[i] == '<')
		{
			i = lexer_redir(i);
			if (i == -1)
			{
				g_shell.error = 2;
				return (3);
			}
			i--;
		}
		if (g_shell.line[i] == '"' || g_shell.line[i] == '\'')
		{
			i = lexer_quote(i);
			if (i == -1)
			{
				g_shell.error = 130;
				return (1);
			}
		}
		if (g_shell.line[i] == '|')
		{
			i = lexer_pipe(i, k++);
			if (i == -1)
			{
				g_shell.error = 2;
				return (2);
			}
			i--;
		}
		i++;
	}
	return (0);
}

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

int	lexer_prompt(void)
{
	int	return_lexer;

	g_shell.nb_proc = 1;
	if (lexer_empty_line() == 1)
	{
		g_shell.error = 0;
		return (1);
	}	
	return_lexer = lexer_quote_and_pipe();
	if (return_lexer == 1 || return_lexer == 2 || return_lexer == 3)
	{
		if (return_lexer == 1)
			printf("syntax error on quotation marks\n");
		if (return_lexer == 2)
			printf("syntax error near unexpected token `|'\n");
		if (return_lexer == 3)
			printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}