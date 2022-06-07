/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:57:18 by aboudjel          #+#    #+#             */
/*   Updated: 2022/06/07 13:28:11 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

// static int	copy_var_hd2(char *copy, char *str, int j)
// {
// 	int		k;
// 	t_env	*temp;

// 	temp = g_shell.lst_env;
// 	while (temp)
// 	{
// 		k = val_strncmp((str + j), temp->var, (g_shell.index_hd - j));
// 		if (k == 0)
// 		{
// 			k = ft_strlen(temp->val);
// 			val_strlcpy(copy, temp->val, k);
// 			return (k);
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }

// static int	copy_var_hd(char *copy, char *str)
// {
// 	int		j;

// 	g_shell.index_hd++;
// 	if (str[g_shell.index_hd] && (ft_isalpha(str[g_shell.index_hd]) == 1
// 			|| str[g_shell.index_hd] == '_' || str[g_shell.index_hd] == '?'))
// 		j = g_shell.index_hd;
// 	else
// 	{
// 		copy[0] = '$';
// 		return (1);
// 	}
// 	if (str[g_shell.index_hd++] == '?')
// 		return (itoa_remixed(copy));
// 	while ((ft_isalnum(str[g_shell.index_hd]) == 1
// 			|| str[g_shell.index_hd] == '_') && str[g_shell.index_hd])
// 		g_shell.index_hd++;
// 	return (copy_var_hd2(copy, str, j));
// }

// static int	gestion_var_size_hd(int j, int k, char *str)
// {
// 	t_env	*temp;

// 	g_shell.index_hd++;
// 	j = g_shell.index_hd;
// 	if (str[g_shell.index_hd] == '?')
// 		return (size_error());
// 	if (ft_isalpha(str[g_shell.index_hd]) == 0
// 		&& str[g_shell.index_hd] != '_')
// 		return (1);
// 	g_shell.index_hd++;
// 	while (ft_isalnum(str[g_shell.index_hd]) == 1
// 		|| str[g_shell.index_hd] == '_')
// 		g_shell.index_hd++;
// 	temp = g_shell.lst_env;
// 	while (temp)
// 	{
// 		k = val_strncmp((str + j), temp->var, (g_shell.index_hd - j));
// 		if (k == 0)
// 		{
// 			k = ft_strlen(temp->val);
// 			return (k);
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }

// static char	*heredoc_replace(char *tmp, int count, int count2)
// {
// 	char	*dst;

// 	g_shell.index_hd = 0;
// 	while (tmp[g_shell.index_hd])
// 	{
// 		if (tmp[g_shell.index_hd] == '$')
// 			count += gestion_var_size_hd(0, 0, tmp);
// 		else
// 		{
// 			count++;
// 			g_shell.index_hd++;
// 		}
// 	}
// 	dst = ft_malloc("str", count, "error malloc here_doc", g_shell.gc2);
// 	dst[count] = '\0';
// 	g_shell.index_hd = 0;
// 	while (tmp[g_shell.index_hd])
// 	{
// 		if (tmp[g_shell.index_hd] == '$')
// 			count2 += copy_var_hd(dst + count2, tmp);
// 		else
// 			dst[count2++] = tmp[g_shell.index_hd++];
// 	}
// 	free(tmp);
// 	return (dst);
// }

// int	ft_heredoc(char *limiter)
// {
// 	char	*tmp;
// 	int		fd;
// 	int		size;

// 	size = ft_strlen(limiter);
// 	fd = open("./temp/heredoc.tmp", O_TRUNC | O_APPEND
// 			| O_CREAT | O_RDWR, 0000644);
// 	while (1)
// 	{
// 		tmp = readline("> ");
// 		if (!tmp || !val_strncmp(tmp, limiter, size))
// 			break ;
// 		if (ft_strchr(tmp, '$'))
// 			tmp = heredoc_replace(tmp, 0, 0);
// 		write(fd, tmp, ft_strlen(tmp));
// 		write(fd, "\n", 1);
// 		free(tmp);
// 	}
// 	free(tmp);
// 	close(fd);
// 	fd = ft_open("./temp/heredoc.tmp", O_RDONLY);
// 	return (fd);
// }

file_name = new_enumerated_empty_file("/tmp/.minishell_heredoc", 0);

int	is_file_created_successfully(char **file_name)
{
	int	fd;

	if (access(*file_name, W_OK) != 0)
	{
		fd = open(*file_name, O_WRONLY | O_CREAT, 0666);
		if (fd >= 3)
		{
			if (close(fd) == -1)
			{
				free(*file_name);
				file_name = NULL;
				return (1);
			}
			return (1);
		}
	}
	free(*file_name);
	return (0);
}

char	*new_enumerated_empty_file(char *prefix_file_name, int sequence)
{
	char	*file_name;
	char	*suffix_name;

	while (++sequence)
	{
		suffix_name = ft_itoa(sequence);
		file_name = append_str(ft_strdup(prefix_file_name), suffix_name, \
			(int)ft_strlen(suffix_name));
		free(suffix_name);
		if (file_name == NULL)
			break ;
		if (is_file_created_successfully(&file_name))
			return (file_name);
	}
	return (NULL);
}