/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:55:17 by aboudjel          #+#    #+#             */
/*   Updated: 2022/06/08 04:31:40 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	ft_create_pipe(int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		write(2, "pipe pas marcher\n", 17);
	g_shell.tab_proc[i].out_fd = pipe_fd[1];
	g_shell.tab_proc[i + 1].in_fd = pipe_fd[0];
}

void	ft_dup(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return ;
	if (dup2(oldfd, newfd) == -1)
		write(2, "dup2 pas marcher\n", 17);
	close(oldfd);
	return ;
}

void	ft_error(char *msg)
{
	perror(msg);
	ft_free(g_shell.gc);
	ft_free(g_shell.gc2);
	exit(1);
}

void	ft_wait(void)
{
	int	i;
	int	val;

	val = 0;
	i = 0;
	while (i < g_shell.nb_proc)
	{
		if (wait(&val) == g_shell.pid[g_shell.nb_proc - 1])
			g_shell.error = WEXITSTATUS(val);
		i++;
	}
}

char	*ft_strjoin_and_replace(char *s1, char *s2, int i)
{
	char	*dst;
	int		j;

	j = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!dst)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	if (s1)
		free(s1);
	return (dst);
}
