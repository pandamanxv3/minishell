/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:07:22 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/25 17:02:03 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

void	find_nb_tokens(int j)
{
	int i;
	
	i = 0;
	g_shell.tab_proc[j].nb_tokens = 0;
	while(g_shell.tab_proc[j].str[i])
	{
		while (g_shell.tab_proc[j].str[i] == ' ')
			i++;
		if (g_shell.tab_proc[j].str[i] == '>' || g_shell.tab_proc[j].str[i] == '<')
		{
			i++;
			if (g_shell.tab_proc[j].str[i] == '>' || g_shell.tab_proc[j].str[i] == '<')
				i++;
			g_shell.tab_proc[j].nb_tokens++;
		}
		while (g_shell.tab_proc[j].str[i] != ' ' && g_shell.tab_proc[j].str[i] != '\0' && g_shell.tab_proc[j].str[i] != '>' && g_shell.tab_proc[j].str[i] != '<')
		{
			if (g_shell.tab_proc[j].str[i] == '"')
			{
				i++;
				while (g_shell.tab_proc[j].str[i] != '"')
				{
					i++;
					if (g_shell.tab_proc[j].str[i] == '"')
						break;
				}
			}
			if (g_shell.tab_proc[j].str[i] == '\'')
			{
				i++;
				while (g_shell.tab_proc[j].str[i] != '\'')
				{
					i++;
					if (g_shell.tab_proc[j].str[i] == '\'')
						break;
				}
			}
			i++;
			if (g_shell.tab_proc[j].str[i] == ' ' || g_shell.tab_proc[j].str[i] == '\0' || g_shell.tab_proc[j].str[i] == '>' || g_shell.tab_proc[j].str[i] == '<')
				g_shell.tab_proc[j].nb_tokens++;		
		}
	}
}

int init_tokens(void)
{
	int i;
	int j;
    
	i = 0;
	while (i < g_shell.nb_proc)
	{
		j = 0;
		g_shell.tab_proc[i].index = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
		
			size_malloc_tokens(i, j, g_shell.tab_proc[i].str);
				//printf("taille TOKEN : %d\n", g_shell.tab_proc[i].tab_token[j].word_malloc_count);
			if (malloc_tokens(i, j) == 1)
				return (1);
			j++;
		}
		j = 0;
		g_shell.tab_proc[i].index = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			copy_token(i, j, g_shell.tab_proc[i].str);
			// printf("INDEX PROC : %d\n", i);
			// printf("INDEX TOKEN : %d\n", j);
			//printf("TOKEN[%d][%d] WORD %s\n", i, j, g_shell.tab_proc[i].tab_token[j].word);
			j++;
		}
		i++;
	}
	return (0);
}
