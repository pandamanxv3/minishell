/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:30:17 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/07 18:17:56 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	sighandler_int(int signum)
{
	if (signum == SIGINT && g_shell.is_in_hd == 0 && g_shell.in_prog == 0)
	{
		g_shell.error = 130;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGINT && g_shell.is_in_hd == 1 && g_shell.in_prog == 0)
	{
		g_shell.is_in_hd = 2;
		g_shell.save_in = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		// dup2(g_shell.save_in, STDIN_FILENO);
		printf("ssss\n");
	}
	else if (signum == SIGINT && g_shell.in_prog == 1)
		ft_putstr_fd("\n", 2);
	else if (signum == SIGQUIT && g_shell.in_prog == 0)
			ft_putstr_fd("\b\b  \b\b", 1);
	else if (signum == SIGQUIT && g_shell.in_prog == 1)
			ft_putendl_fd("Quit (core dumped)", 2);
}
// void	sighandler_quit(int signum)
// {
	
// 	return ;
// }
