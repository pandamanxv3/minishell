/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 03:30:40 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/09 17:34:38 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static void	ft_execve(int i, int j)
{
	if (g_shell.tab_proc[i].tab_token[j].type == COMMAND)
	{
		if (execve(getpath(g_shell.tab_proc[i].tab_token[j].word)
				, get_commandtab(i), get_envtab()) == -1)
		{
			if (g_shell.tab_proc[i].tab_token[j].word[0])
			{
				g_shell.error = 127;
				write(2, "command not found: ", 19);
			}
			else
			{
				g_shell.error = 1;
				write(2, "permission denied:", 18);
			}
			write(2, g_shell.tab_proc[i].tab_token[j].word,
				ft_strlen(g_shell.tab_proc[i].tab_token[j].word));
			write(2, "\n", 1);
			ft_free(g_shell.gc2);
			ft_free(g_shell.gc);
			exit (g_shell.error);
		}
	}
}

void	child(int i)
{
	int	j;

	j = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exec_fd(i, 0, 0);
	if (i < g_shell.nb_proc - 1)
		close(g_shell.tab_proc[i + 1].in_fd);
	if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
		ft_dup(g_shell.tab_proc[i].in_fd, STDIN_FILENO);
	if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
		ft_dup(g_shell.tab_proc[i].out_fd, STDOUT_FILENO);
	while (j + 1 < g_shell.tab_proc[i].nb_tokens
		&& (g_shell.tab_proc[i].tab_token[j].type != BUILTIN
			&& g_shell.tab_proc[i].tab_token[j].type != COMMAND))
		j++;
	if (j < g_shell.tab_proc[i].nb_tokens
		&& g_shell.tab_proc[i].tab_token[j].type == BUILTIN)
	{
		builtin_share(i, j);
		ft_free(g_shell.gc2);
		ft_free(g_shell.gc);
		exit (0);
	}
	ft_execve(i, j);
}

static int	cmd_or_built(int i)
{
	int	j;

	j = 0;
	while (j + 1 < g_shell.tab_proc[i].nb_tokens
		&& g_shell.tab_proc[i].tab_token[j].type != BUILTIN
		&& g_shell.tab_proc[i].tab_token[j].type != COMMAND)
		j++;
	if (g_shell.tab_proc[i].tab_token[j].type == BUILTIN
		|| g_shell.tab_proc[i].tab_token[j].type == COMMAND)
		return (1);
	exec_fd(i, 0, 0);
	ft_free(g_shell.gc2);
	ft_free(g_shell.gc);
	exit (0);
}

static int	dup_builtin(int i, int j, int save_in, int save_out)
{
	if (g_shell.tab_proc[i].tab_token[j].type == COMMAND
		|| val_strncmp("echo", g_shell.tab_proc[i].tab_token[j].word, 4) == 0)
		return (1);
	exec_fd(i, 1, 0);
	if (g_shell.tab_proc[i].in_fd >= 0)
	{
		if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
		{
			save_in = dup(STDIN_FILENO);
			dup2(g_shell.tab_proc[i].in_fd, STDIN_FILENO);
		}
		if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
		{
			save_out = dup(STDOUT_FILENO);
			dup2(g_shell.tab_proc[i].out_fd, STDOUT_FILENO);
		}
		if (g_shell.tab_proc[i].tab_token[j].type == BUILTIN)
			builtin_share(i, j);
		if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
			dup2(save_in, STDIN_FILENO);
		if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
			dup2(save_out, STDOUT_FILENO);
	}
	return (0);
}

void	dispatch_exec(int i, int j)
{
	g_shell.in_prog = 1;
	g_shell.pid = ft_malloc("int", g_shell.nb_proc, "err pid", g_shell.gc2);
	while (i < g_shell.nb_proc)
	{
		if (g_shell.nb_proc > 1 && i < g_shell.nb_proc - 1)
			ft_create_pipe(i);
		if (g_shell.nb_proc == 1)
		{
			while (j < g_shell.tab_proc[i].nb_tokens - 1
				&& g_shell.tab_proc[i].tab_token[j].type != BUILTIN
				&& g_shell.tab_proc[i].tab_token[j].type != COMMAND)
				j++;
			if (dup_builtin(i, j, 0, 0) == 0)
				return ;
		}
		g_shell.pid[i] = fork();
		if (g_shell.pid[i] < 0)
			ft_error("fork failed");
		if (g_shell.pid[i] > 0)
			ft_close(i);
		if (g_shell.pid[i] == 0 && cmd_or_built(i) == 1)
			child(i);
		i++;
	}
	ft_wait();
}
