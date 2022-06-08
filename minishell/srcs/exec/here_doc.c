/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:16:20 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/07 20:24:00 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	copy_var_hd2(char *copy, char *str, int j)
{
	int		k;
	t_env	*temp;

	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.index_hd - j));
		if (k == 0)
		{
			k = ft_strlen(temp->val);
			val_strlcpy(copy, temp->val, k);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

static int	copy_var_hd(char *copy, char *str)
{
	int		j;

	g_shell.index_hd++;
	if (str[g_shell.index_hd] && (ft_isalpha(str[g_shell.index_hd]) == 1
			|| str[g_shell.index_hd] == '_' || str[g_shell.index_hd] == '?'))
		j = g_shell.index_hd;
	else
	{
		copy[0] = '$';
		return (1);
	}
	if (str[g_shell.index_hd++] == '?')
		return (itoa_remixed(copy));
	while ((ft_isalnum(str[g_shell.index_hd]) == 1
			|| str[g_shell.index_hd] == '_') && str[g_shell.index_hd])
		g_shell.index_hd++;
	return (copy_var_hd2(copy, str, j));
}

static int	gestion_var_size_hd(int j, int k, char *str)
{
	t_env	*temp;

	g_shell.index_hd++;
	j = g_shell.index_hd;
	if (str[g_shell.index_hd] == '?')
		return (size_error());
	if (ft_isalpha(str[g_shell.index_hd]) == 0
		&& str[g_shell.index_hd] != '_')
		return (1);
	g_shell.index_hd++;
	while (ft_isalnum(str[g_shell.index_hd]) == 1
		|| str[g_shell.index_hd] == '_')
		g_shell.index_hd++;
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.index_hd - j));
		if (k == 0)
		{
			k = ft_strlen(temp->val);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

static char	*heredoc_replace(char *tmp, int count, int count2)
{
	char	*dst;

	g_shell.index_hd = 0;
	while (tmp[g_shell.index_hd])
	{
		if (tmp[g_shell.index_hd] == '$')
			count += gestion_var_size_hd(0, 0, tmp);
		else
		{
			count++;
			g_shell.index_hd++;
		}
	}
	dst = ft_malloc("str", count, "error malloc here_doc", g_shell.gc2);
	dst[count] = '\0';
	g_shell.index_hd = 0;
	while (tmp[g_shell.index_hd])
	{
		if (tmp[g_shell.index_hd] == '$')
			count2 += copy_var_hd(dst + count2, tmp);
		else
			dst[count2++] = tmp[g_shell.index_hd++];
	}
	free(tmp);
	return (dst);
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
			break ;
		if (ft_strchr(tmp, '$'))
			tmp = heredoc_replace(tmp, 0, 0);
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
		free(tmp);
	}
	free(tmp);
	close(fd);
	if (g_shell.is_in_hd != 2)
		g_shell.tab_proc[i].hd_fd[g_shell.tab_proc[i].index] = ft_open(file_name, 0);
	else
		dup2(g_shell.save_in, STDIN_FILENO);
	g_shell.tab_proc[i].index++;
	free(file_name);
}

int	is_file_created_successfully(char *file_name)
{
	int	fd;

	if (access(file_name, W_OK) != 0)
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