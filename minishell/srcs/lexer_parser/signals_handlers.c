/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:30:17 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/06 19:19:03 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	sighandler_int(int signum)
{
	if (signum == SIGINT)
	{
		g_shell.error = 130;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", 1);
}

void	sighandler_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		g_shell.error = 130;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", 1);
}
// void	sighandler_quit(int signum)
// {
	
// 	return ;
// }
