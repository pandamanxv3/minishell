/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:44:28 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/10 19:26:17 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static void	on_simple_quote(int i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '\'')
	{
		g_shell.tab_proc[i].tab_token[j].word_malloc_count++;
		g_shell.tab_proc[i].index++;
	}
	g_shell.tab_proc[i].index++;
}

static void	on_double_quote(int i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '"')
	{
		g_shell.tab_proc[i].tab_token[j].word_malloc_count++;
		g_shell.tab_proc[i].index++;
	}
	g_shell.tab_proc[i].index++;
}

static void	size_malloc_tokens_bis(int i, int j, char *str)
{
	while (str[g_shell.tab_proc[i].index]
		&& str[g_shell.tab_proc[i].index] != ' '
		&& str[g_shell.tab_proc[i].index] != '<'
		&& str[g_shell.tab_proc[i].index] != '>')
	{
		if (str[g_shell.tab_proc[i].index] == '"')
			on_double_quote(i, j, str);
		else if (str[g_shell.tab_proc[i].index] == '\'')
			on_simple_quote(i, j, str);
		else
		{
			g_shell.tab_proc[i].index++;
			g_shell.tab_proc[i].tab_token[j].word_malloc_count++;
		}
	}
}

void	size_malloc_tokens(int i, int j, char *str)
{
	g_shell.tab_proc[i].tab_token[j].word_malloc_count = 0;
	while (str[g_shell.tab_proc[i].index] == ' ')
		g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] == '>'
		|| str[g_shell.tab_proc[i].index] == '<')
	{
		g_shell.tab_proc[i].tab_token[j].word_malloc_count++;
		g_shell.tab_proc[i].index++;
		if (str[g_shell.tab_proc[i].index] != '>'
			&& str[g_shell.tab_proc[i].index] != '<')
			return ;
	}
	size_malloc_tokens_bis(i, j, str);
}
