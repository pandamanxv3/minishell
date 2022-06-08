/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:09:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 04:47:09 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

int	ft_open(char *str, int type)
{
	int	fd;

	if (type == 0)
		fd = open(str, O_RDONLY);
	if (type == 1)
		fd = open(str, O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	if (type == 2)
		fd = open(str, O_APPEND | O_CREAT | O_WRONLY, 0000644);
	if (fd < 0 && type == 0)
	{
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory", 27);
		write(2, "\n", 1);
		return (-1);
	}
	if (fd < 0 && (type == 1 || type == 2))
	{
		write(2, "couldn't open or create: ", 25);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	return (fd);
}

static void	dispatch_fd(int i, int j, char *word)
{
	if (g_shell.tab_proc[i].tab_token[j].type == INFILE)
	{
		if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
			close(g_shell.tab_proc[i].in_fd);
		g_shell.tab_proc[i].in_fd = ft_open(word, 0);
	}
	else if (g_shell.tab_proc[i].tab_token[j].type == OUTFILE)
	{
		if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
			close(g_shell.tab_proc[i].out_fd);
		g_shell.tab_proc[i].out_fd = ft_open(word, 1);
	}
	else if (g_shell.tab_proc[i].tab_token[j].type == HEREDOC)
	{
		if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
			close(g_shell.tab_proc[i].in_fd);
		g_shell.tab_proc[i].in_fd \
		= g_shell.tab_proc[i].hd_fd[g_shell.tab_proc[i].index++];
	}
	else if (g_shell.tab_proc[i].tab_token[j].type == OUTFILE_APPEND)
	{
		if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
			close(g_shell.tab_proc[i].out_fd);
		g_shell.tab_proc[i].out_fd = ft_open(word, 2);
	}
}

void	exec_fd(int i, int child_or_parents, int j)
{
	char	*word;
	int		type;

	while (j < g_shell.tab_proc[i].nb_tokens)
	{
		type = g_shell.tab_proc[i].tab_token[j].type;
		word = g_shell.tab_proc[i].tab_token[j].word;
		if (type == INFILE || type == OUTFILE
			|| type == HEREDOC || type == OUTFILE_APPEND)
			dispatch_fd(i, j, word);
		j++;
		if (g_shell.tab_proc[i].in_fd < 0 || g_shell.tab_proc[i].out_fd < 0)
		{
			if (g_shell.tab_proc[i].in_fd > 0)
				close(g_shell.tab_proc[i].in_fd);
			if (g_shell.tab_proc[i].out_fd > 1)
				close(g_shell.tab_proc[i].out_fd);
			if (child_or_parents == 1)
				return ;
			ft_free(g_shell.gc2);
			ft_free(g_shell.gc);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_close(int i)
{
	if (g_shell.tab_proc[i].in_fd != 0)
		close(g_shell.tab_proc[i].in_fd);
	if (i != g_shell.nb_proc - 1)
		close(g_shell.tab_proc[i].out_fd);
}
