/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:05:33 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 01:09:12 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static void	builtin_share3(int i, int j, int count)
{
	int		first_word;
	
	first_word = -1;
	g_shell.error = 0;
	if (val_strncmp("cd", g_shell.tab_proc[i].tab_token[j].word, 2) == 0)
	{
		while (j < g_shell.tab_proc[i].nb_tokens)
		{
			if (g_shell.tab_proc[i].tab_token[j].type == WORD
				|| g_shell.tab_proc[i].tab_token[j].type == WORD_N)
			{
				if (first_word == -1)
					first_word = j;
				count++;
			}
			j++;
		}
		if (count == 0)
			ft_chdir(NULL);
		if (first_word != -1 && g_shell.tab_proc[i].tab_token[first_word].word[0] == '-')
		{
			g_shell.error = 2;
			ft_putendl_fd("cd: invalid option", 2);
			return ;
		}
		if (count == 1)
			ft_chdir(g_shell.tab_proc[i].tab_token[first_word].word);
		if (count > 1)
		{
			g_shell.error = 1;
			ft_putendl_fd("cd: too many arguments", 2); 			
		}
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
	{
		ft_pwd();
		printf("%s\n", g_shell.pwd);
	}	
	else if (val_strncmp("echo", builtin, 4) == 0)
		ft_echo(i, 0, -1);
	else if (val_strncmp("env", builtin, 3) == 0)
		print_env(g_shell.lst_env);
	else if (val_strncmp("exit", builtin, 4) == 0)
		ft_exit(i);
	else
	 builtin_share2(i, j, builtin);
}
