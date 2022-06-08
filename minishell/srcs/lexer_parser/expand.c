/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:50:10 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 05:19:05 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	on_simple_quote_var(void)
{
	int	count;

	count = 1;
	g_shell.index_hd++;
	while (g_shell.line[g_shell.index_hd] != '\'')
	{
		count++;
		g_shell.index_hd++;
	}
	g_shell.index_hd++;
	return (count + 1);
}

static int	copy_on_simple_quote_var(char *str)
{
	int	i;

	i = 0;
	str[i++] = g_shell.line[g_shell.index_hd++];
	while (g_shell.line[g_shell.index_hd] != '\'')
	{
		str[i++] = g_shell.line[g_shell.index_hd++];
	}
	str[i++] = g_shell.line[g_shell.index_hd++];
	return (i);
}

static void	size_expand2(int i, int count, char *str)
{
	int		double_quote;

	g_shell.index_hd = 0;
	double_quote = 0;
	while (i < count)
	{
		if (g_shell.line[g_shell.index_hd] == '"')
			double_quote++;
		if (g_shell.line[g_shell.index_hd] == '\'' && double_quote % 2 == 0)
			i += copy_on_simple_quote_var(str + i);
		else if (g_shell.line[g_shell.index_hd] == '$')
			i += setup_copy_var(str + i);
		else
			str[i++] = g_shell.line[g_shell.index_hd++];
	}
	g_shell.line = str;
}

void	size_expand(int i, int count)
{
	char	*str;
	int		double_quote;

	double_quote = 0;
	g_shell.index_hd = 0;
	while (g_shell.line[g_shell.index_hd])
	{
		if (g_shell.line[g_shell.index_hd] == '"')
			double_quote++;
		if (g_shell.line[g_shell.index_hd] == '\'' && double_quote % 2 == 0)
			count += on_simple_quote_var();
		else if (g_shell.line[g_shell.index_hd] == '$')
			count += gestion_var_size(0, 0);
		else
		{
			g_shell.index_hd++;
			count++;
		}
	}
	str = ft_malloc("str", count, "expand malloc failed", g_shell.gc2);
	str[count] = '\0';
	size_expand2(i, count, str);
}
