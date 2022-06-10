/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:04:32 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/10 18:52:12 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static void	copy_on_simple_quote(int i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '\'')
	{
		g_shell.tab_proc[i].tab_token[j].word
		[g_shell.tab_proc[i].tab_token[j].word_malloc_count++]
			= str[g_shell.tab_proc[i].index++];
	}
	g_shell.tab_proc[i].index++;
}

static void	copy_on_double_quote(int i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '"')
		g_shell.tab_proc[i].tab_token[j].word
		[g_shell.tab_proc[i].tab_token[j].word_malloc_count++]
			= str[g_shell.tab_proc[i].index++];
	g_shell.tab_proc[i].index++;
}

static void	copy_token_bis(int i, int j, char *str)
{
	while (str[g_shell.tab_proc[i].index]
		&& str[g_shell.tab_proc[i].index] != ' '
		&& str[g_shell.tab_proc[i].index] != '<'
		&& str[g_shell.tab_proc[i].index] != '>')
	{
		if (str[g_shell.tab_proc[i].index] == '"')
			copy_on_double_quote(i, j, str);
		else if (str[g_shell.tab_proc[i].index] == '\'')
			copy_on_simple_quote(i, j, str);
		else
			g_shell.tab_proc[i].tab_token[j].word
			[g_shell.tab_proc[i].tab_token[j].word_malloc_count++]
				= str[g_shell.tab_proc[i].index++];
	}	
}

void	copy_token(int i, int j, char *str)
{
	g_shell.tab_proc[i].tab_token[j].word_malloc_count = 0;
	while (str[g_shell.tab_proc[i].index] == ' ')
		g_shell.tab_proc[i].index++;
	if (str[g_shell.tab_proc[i].index] == '>'
		|| str[g_shell.tab_proc[i].index] == '<')
	{
		while (str[g_shell.tab_proc[i].index] == '>'
			|| str[g_shell.tab_proc[i].index] == '<')
			g_shell.tab_proc[i].tab_token[j].word
			[g_shell.tab_proc[i].tab_token[j].word_malloc_count++]
				= str[g_shell.tab_proc[i].index++];
		g_shell.tab_proc[i].tab_token[j].word
		[g_shell.tab_proc[i].tab_token[j].word_malloc_count]
			= '\0';
		return ;
	}
	copy_token_bis(i, j, str);
	g_shell.tab_proc[i].tab_token[j].word
	[g_shell.tab_proc[i].tab_token[j].word_malloc_count]
		= '\0';
	return ;
}
