/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:38:31 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/06 20:30:03 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	ft_echo(int i, int n, int j)
{
	int	type;

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
	while (j < g_shell.tab_proc[i].nb_tokens)
	{
		if (type == WORD || type == WORD_N)
			printf("%s", g_shell.tab_proc[i].tab_token[j].word);
		j++;
		if (j < g_shell.tab_proc[i].nb_tokens)
			printf(" ");
		if (j < g_shell.tab_proc[i].nb_tokens)
			type = g_shell.tab_proc[i].tab_token[j].type;
	}
	if (n == 1)
		printf("\n");
}
