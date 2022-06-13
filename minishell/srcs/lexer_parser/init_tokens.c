/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:07:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/13 14:28:48 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	check_if_quotes(int j, int i)
{
	if (g_shell.tab_proc[j].str[i] == '"')
	{
		i++;
		while (g_shell.tab_proc[j].str[i] != '"')
		{
			i++;
			if (g_shell.tab_proc[j].str[i] == '"')
				break ;
		}
	}
	if (g_shell.tab_proc[j].str[i] == '\'')
	{
		i++;
		while (g_shell.tab_proc[j].str[i] != '\'')
		{
			i++;
			if (g_shell.tab_proc[j].str[i] == '\'')
				break ;
		}
	}
	return (i);
}

static void	increase_tokens(int j, int i)
{
	if (g_shell.tab_proc[j].str[i] == ' '
		|| g_shell.tab_proc[j].str[i] == '\0'
		|| g_shell.tab_proc[j].str[i] == '>'
		|| g_shell.tab_proc[j].str[i] == '<')
		g_shell.tab_proc[j].nb_tokens++;
}

void	find_nb_tokens(int j, int i)
{
	g_shell.tab_proc[j].nb_tokens = 0;
	while (g_shell.tab_proc[j].str[i])
	{
		while (g_shell.tab_proc[j].str[i] == ' ')
			i++;
		if (g_shell.tab_proc[j].str[i] == '>'
			|| g_shell.tab_proc[j].str[i] == '<')
		{
			i++;
			if (g_shell.tab_proc[j].str[i] == '>'
				|| g_shell.tab_proc[j].str[i] == '<')
				i++;
			g_shell.tab_proc[j].nb_tokens++;
		}
		while (g_shell.tab_proc[j].str[i] != ' '
			&& g_shell.tab_proc[j].str[i] != '\0'
			&& g_shell.tab_proc[j].str[i] != '>'
			&& g_shell.tab_proc[j].str[i] != '<')
		{
			i = check_if_quotes(j, i);
			i++;
			increase_tokens(j, i);
		}
	}
}

int	init_tokens(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_shell.nb_proc)
	{
		j = 0;
		g_shell.tab_proc[i].index = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{		
			size_malloc_tokens(i, j, g_shell.tab_proc[i].str);
			if (malloc_tokens(i, j) == 1)
				return (1);
			j++;
		}
		j = 0;
		g_shell.tab_proc[i].index = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			copy_token(i, j, g_shell.tab_proc[i].str);
			j++;
		}
		i++;
	}
	return (0);
}
