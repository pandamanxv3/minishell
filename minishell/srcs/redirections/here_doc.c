/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:16:20 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 19:35:58 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static void	ft_heredoc2(char *file_name, int i)
{
	if (g_shell.is_in_hd != 2)
		g_shell.tab_proc[i].hd_fd[g_shell.tab_proc[i].index] \
			= ft_open(file_name, 0);
	else
		dup2(g_shell.save_in, STDIN_FILENO);
	g_shell.tab_proc[i].index++;
	free(file_name);
}

char	*new_enumerated_empty_file(char *prefix, int sequence)
{
	char	*file_name;
	char	*suffix_name;
	int		fd;

	while (++sequence)
	{
		suffix_name = ft_itoa(sequence);
		if (!suffix_name)
			mallocreturn_failed(g_shell.gc2, g_shell.gc, "mal itoa failed");
		file_name = ft_strjoin(prefix, suffix_name);
		if (!file_name)
			mallocreturn_failed(g_shell.gc2, g_shell.gc, "mal strjoin failed");
		free(suffix_name);
		fd = is_file_created_successfully(file_name);
		if (fd != -5)
		{
			close(fd);
			return (file_name);
		}
		free(file_name);
	}
	return (NULL);
}

void	ft_heredoc(char *limiter, int i)
{
	char	*tmp;
	int		fd;
	int		size;
	char	*file_name;

	size = ft_strlen(limiter);
	file_name = new_enumerated_empty_file("/tmp/tempheredoc", 0);
	fd = ft_open(file_name, 1);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp || !val_strncmp(tmp, limiter, size) || g_shell.is_in_hd == 2)
		{
			if (!tmp)
				printf("warning: here-document closed by EOF\n");
			break ;			
		}
		if (ft_strchr(tmp, '$'))
			tmp = heredoc_replace(tmp, 0, 0);
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
		free(tmp);
	}
	free(tmp);
	close(fd);
	ft_heredoc2(file_name, i);
}

int	is_file_created_successfully(char *file_name)
{
	int	fd;

	if (access(file_name, F_OK) != 0)
	{
		fd = open(file_name, O_WRONLY | O_CREAT, 0666);
		if (fd < 1)
		{
			free(file_name);
			mallocreturn_failed(g_shell.gc2, g_shell.gc, "fd couldn't open");
		}
		return (fd);
	}
	return (-5);
}


void	dispatch_here_doc(int i, int j)
{
	g_shell.is_in_hd = 1;
	while (i < g_shell.nb_proc)
	{
		g_shell.tab_proc[i].index = 0;
		j = 0;
		while (j < 1024)
		{
			g_shell.tab_proc[i].hd_fd[j] = -5;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < g_shell.nb_proc)
	{
		j = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			if (g_shell.tab_proc[i].tab_token[j].type == HEREDOC)
				ft_heredoc(g_shell.tab_proc[i].tab_token[j].word, i);
			j++;
		}
		g_shell.tab_proc[i].index = 0;
		i++;
	}	
}
