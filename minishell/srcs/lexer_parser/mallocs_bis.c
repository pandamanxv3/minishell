/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:25:28 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/10 19:29:16 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

int	malloc_processes(void)
{
	g_shell.tab_proc = malloc(sizeof(t_process)
			* (g_shell.nb_proc + 1));
	if (!g_shell.tab_proc)
		mallocreturn_failed(g_shell.gc, g_shell.gc2, "t_process malloc failed");
	else
		ft_gcadd_back(g_shell.gc2, ft_gcnew(g_shell.tab_proc, g_shell.gc2));
	return (0);
}

int	malloc_tokens(int i, int j)
{
	g_shell.tab_proc[i].tab_token[j].word
		= ft_malloc("str", g_shell.tab_proc[i].tab_token[j].word_malloc_count,
			" word token malloc failed", g_shell.gc2);
	return (0);
}
