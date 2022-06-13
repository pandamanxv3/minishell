/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:41:48 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/13 16:59:05 by aboudjel         ###   ########.fr       */
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

static int	lexer_redir2(int i, int d)
{
	while (g_shell.line[i] && g_shell.line[i] != '>' && g_shell.line[i] != '<'
		&& g_shell.line[i] != ' ' && g_shell.line[i] != '|')
	{
		if (g_shell.line[i] == '"' || g_shell.line[i] == '\'')
		{
			i = lexer_quote(i);
			if (i == -1)
				return (-1);
		}
		i++;
	}
	if (d == i)
		return (-1);
	if (g_shell.line[i - 1] == '"' || g_shell.line[i] == '\'')
		i = i + 1;
	return (i);
}

static int	lexer_redir(int i)
{
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
	return (lexer_redir2(i, i));
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

int	lexer_quote_and_pipe(int i, int k)
{
	while (g_shell.line[i])
	{
		if (g_shell.line[i] == '>' || g_shell.line[i] == '<')
		{
			i = lexer_redir(i);
			if (i == -1)
				return (3);
			i--;
		}
		if (g_shell.line[i] == '"' || g_shell.line[i] == '\'')
		{
			i = lexer_quote(i);
			if (i == -1)
				return (1);
		}
		if (g_shell.line[i] == '|')
		{
			i = lexer_pipe(i, k++);
			if (i == -1)
				return (2);
			i--;
		}
		i++;
	}
	return (0);
}
