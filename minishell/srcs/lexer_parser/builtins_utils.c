/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:24:57 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/10 18:45:15 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	read_and_replace_env_cd(char *var, char *val)
{
	t_env	*current;

	current = g_shell.lst_env;
	while (current)
	{
		if (val_strncmp(var, current->var, ft_strlen(var)) == 0)
			current->val = val;
		current = current->next;
	}
}

char	*get_home_val(void)
{
	t_env	*current;
	char	*path;

	current = g_shell.lst_env;
	path = NULL;
	while (current)
	{
		if (val_strncmp("HOME", current->var, 4) == 0)
			path = current->val;
		current = current->next;
	}
	return (path);
}
