/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_in_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:23:05 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/01 14:25:21 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void    builtin_share(int i, int j)
{
	char	*builtin;
	char	*path;

	builtin = g_shell.tab_proc[i].tab_token[j].word;
	if (val_strncmp("pwd", builtin, 3) == 0)
		ft_pre_pwd(i, j);
	if (val_strncmp("echo", builtin, 4) == 0)
		ft_echo(i);
	if (val_strncmp("export", builtin, 6) == 0)
	{
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			if (g_shell.tab_proc[i].tab_token[j].type == WORD)
				ft_export(g_shell.tab_proc[i].tab_token[j].word);
			j++;
		}		
	}
	if (val_strncmp("env", builtin, 3) == 0)
		print_env(g_shell.lst_env);
	if (val_strncmp("unset", builtin, 5) == 0)
	{
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			if (g_shell.tab_proc[i].tab_token[j].type == WORD)
				unset(g_shell.tab_proc[i].tab_token[j].word);
			j++;
		}	
	}
	if (val_strncmp("exit", builtin, 4) == 0)
		ft_exit(i);
	int count;
	int	first_word;
	count = 0;
	if (val_strncmp("cd", builtin, 2) == 0)
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
		{
			path = NULL; //si on m'envoie cd sans aucun autre argument
			ft_chdir(NULL);
		}
		if (count == 1)
			ft_chdir(g_shell.tab_proc[i].tab_token[first_word].word);
		if (count > 1)
			ft_putendl_fd("cd: too many arguments", 2);
	}
}
