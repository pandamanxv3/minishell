/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:00:25 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 04:57:40 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	replace_env(char *word, int i)
{
	t_env	*current;

	current = g_shell.lst_env;
	while (current)
	{
		if (val_strncmp(word, current->var, i) == 0)
		{
			current->val = env_dup(word + i + 1, ft_strlen(word + i),
					g_shell.gc);
			break ;
		}
		current = current->next;
	}
}

int	read_env(char *word, int i)
{
	t_env	*current;

	current = g_shell.lst_env;
	while (current)
	{
		if (val_strncmp(word, current->var, i) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

void	plus_env(char *word, int i)
{
	t_env	*current;

	current = g_shell.lst_env;
	while (current)
	{
		if (val_strncmp(word, current->var, i) == 0)
		{
			current->val = ft_strjoin(current->val, word + i + 2);
			if (!current->val)
				ft_error("error malloc du export +=");
			ft_gcadd_back(g_shell.gc, ft_gcnew(current->val, g_shell.gc));
			return ;
		}
		current = current->next;
	}
	add_env(g_shell.lst_env, get_envlst(word, g_shell.gc));
}

static int	export_while(char *word, int i)
{
	while (word[++i] && word[i] != '=')
	{
		if (i > 0 && word[i] == '+' && word[i + 1] == '=')
		{
			plus_env(word, i);
			return (-1);
		}
		if (i == 0 && ft_isdigit(word[i]))
		{
			g_shell.error = 1;
			ft_putstr_fd("export: '", 2);
			write(2, word, ft_strlen(word));
			ft_putendl_fd("': not a valid identifier", 2);
			return (-1);
		}
		if (ft_isalnum(word[i]) == 0 && word[i] != '_')
		{
			g_shell.error = 127;
			ft_putstr_fd("export: '", 2);
			write(2, word, ft_strlen(word));
			ft_putendl_fd("': not a valid identifier", 2);
			return (-1);
		}
	}
	return (i);
}

void	ft_export(char *word)
{
	int	i;

	if (word[0] == '=')
	{
		g_shell.error = 1;
		ft_putstr_fd("export: `", 2);
		write(2, word, ft_strlen(word));
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	i = export_while(word, -1);
	if (i == -1)
		return ;
	if (word[i] == '=')
	{
		if (!g_shell.lst_env)
			g_shell.lst_env = get_envlst(word, g_shell.gc);
		else if (read_env(word, i) == 0)
			replace_env(word, i);
		else
			add_env(g_shell.lst_env, get_envlst(word, g_shell.gc));
	}
}
