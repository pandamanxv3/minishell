/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:50:10 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 05:19:12 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	copy_var(char *copy, int j)
{
	t_env	*temp;
	int		k;

	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((g_shell.line + j), temp->var, (g_shell.index_hd - j));
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

int	itoa_remixed(char *dst)
{
	int		length;
	long	nbbis;
	int		i;

	nbbis = g_shell.error;
	length = size_error();
	i = length - 1;
	if (nbbis == 0)
		dst[i] = '0';
	while (nbbis > 0)
	{
		dst[i] = nbbis % 10 + 48;
		nbbis = nbbis / 10;
		i--;
	}
	return (length);
}

int	setup_copy_var(char *copy)
{
	int	j;

	g_shell.index_hd++;
	if (g_shell.line[g_shell.index_hd]
		&& (ft_isalpha(g_shell.line[g_shell.index_hd]) == 1
			|| g_shell.line[g_shell.index_hd] == '_'
			|| g_shell.line[g_shell.index_hd] == '?'))
		j = g_shell.index_hd;
	else
	{
		copy[0] = '$';
		return (1);
	}
	if (g_shell.line[g_shell.index_hd++] == '?')
		return (itoa_remixed(copy));
	while (g_shell.line[g_shell.index_hd]
		&& (ft_isalnum(g_shell.line[g_shell.index_hd]) == 1
			|| g_shell.line[g_shell.index_hd] == '_'))
		g_shell.index_hd++;
	return (copy_var(copy, j));
}

int	gestion_var_size(int j, int k)
{
	t_env	*temp;

	g_shell.index_hd++;
	j = g_shell.index_hd;
	if (g_shell.line[g_shell.index_hd] == '?')
		return (size_error());
	if (ft_isalpha(g_shell.line[g_shell.index_hd]) == 0
		&& g_shell.line[g_shell.index_hd] != '_')
		return (1);
	g_shell.index_hd++;
	while (ft_isalnum(g_shell.line[g_shell.index_hd]) == 1
		|| g_shell.line[g_shell.index_hd] == '_')
		g_shell.index_hd++;
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((g_shell.line + j), temp->var, (g_shell.index_hd - j));
		if (k == 0)
		{
			k = ft_strlen(temp->val);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}
