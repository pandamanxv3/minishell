/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:30:17 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/13 17:40:43 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static void	sighandler_int2(int signum)
{
	if (signum == SIGINT && g_shell.in_prog == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_shell.error = 130;
	}
	else if (signum == SIGQUIT && g_shell.in_prog == 0)
		ft_putstr_fd("\b\b  \b\b", 1);
	else if (signum == SIGQUIT && g_shell.in_prog == 1)
	{
		ft_putendl_fd("Quit", 2);
		g_shell.error = 131;
	}
}

void	sighandler_int(int signum)
{
	if (signum == SIGINT && g_shell.is_in_hd == 0 && g_shell.in_prog == 0)
	{
		g_shell.error = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGINT && g_shell.is_in_hd > 0 && g_shell.in_prog == 0)
	{
		g_shell.is_in_hd = 2;
		g_shell.save_in = dup(STDIN_FILENO);
		g_shell.error = 130;
		printf("\n");
		close(STDIN_FILENO);
		rl_replace_line("", 0);
	}
	else
		sighandler_int2(signum);
}
