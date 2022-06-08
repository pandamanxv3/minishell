/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:38:31 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 05:13:17 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	n_or_not(int i, int n)
{
	int	type;
	int	j;

	j = 0;
	type = g_shell.tab_proc[i].tab_token[j].type;
	g_shell.error = 0;
	while (type != WORD && j < g_shell.tab_proc[i].nb_tokens)
	{
		if (type == WORD_N)
			n = 0;
		j++;
		if (j < g_shell.tab_proc[i].nb_tokens)
			type = g_shell.tab_proc[i].tab_token[j].type;
	}
	return (n);
}

void	ft_echo(int i, int j, int space)
{
	int	type;

	while (j < g_shell.tab_proc[i].nb_tokens
		&& g_shell.tab_proc[i].tab_token[j].type != WORD)
		j++;
	type = g_shell.tab_proc[i].tab_token[j].type;
	while (j < g_shell.tab_proc[i].nb_tokens)
	{
		if (type == WORD || type == WORD_N)
			space += 1;
		if (space == 1)
		{
			space -= 1;
			printf(" ");
		}
		if (type == WORD || type == WORD_N)
			printf("%s", g_shell.tab_proc[i].tab_token[j].word);
		j++;
		if (j < g_shell.tab_proc[i].nb_tokens)
			type = g_shell.tab_proc[i].tab_token[j].type;
	}
	if (n_or_not(i, 1) == 1)
		printf("\n");
}
