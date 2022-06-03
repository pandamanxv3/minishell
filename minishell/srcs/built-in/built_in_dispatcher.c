/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:05:33 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/03 05:03:50 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static void	builtin_share3(int i, int j, int count)
{
	int	first_word;

	if (val_strncmp("cd", g_shell.tab_proc[i].tab_token[j].word, 2) == 0)
	{
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			if (g_shell.tab_proc[i].tab_token[j].type == WORD)
			{
				first_word = j;
				count++;
			}
			if (g_shell.tab_proc[i].tab_token[j].type == WORD_N)
			{
				ft_putendl_fd("cd: -n: invalid option", 2);
				return ;
			}
			j++;
		}
		if (count == 0)
			ft_chdir(NULL);
		if (count == 1)
			ft_chdir(g_shell.tab_proc[i].tab_token[first_word].word);
		if (count > 1)
			ft_putendl_fd("cd: too many arguments", 2);
	}
}

static void	builtin_share2(int i, int j, char *builtin)
{
	if (val_strncmp("unset", builtin, 5) == 0)
	{
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			if (g_shell.tab_proc[i].tab_token[j].type == WORD)
				unset(g_shell.tab_proc[i].tab_token[j].word);
			j++;
		}	
	}
	else if (val_strncmp("export", builtin, 6) == 0)
	{
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			if (g_shell.tab_proc[i].tab_token[j].type == WORD)
				ft_export(g_shell.tab_proc[i].tab_token[j].word);
			j++;
		}		
	}
	else
		builtin_share3(i, j, 0);
}

void	builtin_share(int i, int j)
{
	char	*builtin;

	builtin = g_shell.tab_proc[i].tab_token[j].word;
	if (val_strncmp("pwd", builtin, 3) == 0)
		ft_pre_pwd(i, j);
	else if (val_strncmp("echo", builtin, 4) == 0)
		ft_echo(i, 1);
	else if (val_strncmp("env", builtin, 3) == 0)
		print_env(g_shell.lst_env);
	else if (val_strncmp("exit", builtin, 4) == 0)
		ft_exit(i);
	else
	 builtin_share2(i, j, builtin);
}
