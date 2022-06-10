/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:46:04 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/10 18:56:55 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	only_n(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (1);
	while (i < ft_strlen(str))
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static void	word_or_word_n(int i, int j)
{
	char	*str;
	int		return_word_n;

	str = g_shell.tab_proc[i].tab_token[j].word;
	return_word_n = only_n(str);
	if (str[0] == '-' && return_word_n == 0)
		g_shell.tab_proc[i].tab_token[j].type = WORD_N;
	else
		g_shell.tab_proc[i].tab_token[j].type = WORD;
}

static void	builtin_or_command(int i, int j)
{
	int	return_builtin;

	return_builtin = is_builtin(i, j);
	if (return_builtin != 1)
		g_shell.tab_proc[i].tab_token[j].type = BUILTIN;
	else
		g_shell.tab_proc[i].tab_token[j].type = COMMAND;
}

void	all_token_types(void)
{
	int	j;
	int	i;
	int	is_command;
	int	return_sep;

	i = 0;
	while (i < g_shell.nb_proc)
	{
		j = 0;
		is_command = 0;
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			return_sep = is_separator(i, j);
			if (return_sep != 1)
			{
				j++;
				file_types(i, j, return_sep);
			}
			else if (is_command == 0)
			{
				is_command = 1;
				builtin_or_command(i, j);
				if (g_shell.tab_proc[i].nb_tokens <= j - 1
					&& g_shell.tab_proc[i].tab_token[j + 1].type == WORD_N)
					j++;
			}
			else
				word_or_word_n(i, j);
			j++;
		}
		i++;
	}
}
