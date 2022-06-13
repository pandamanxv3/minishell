/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:24:57 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/13 16:50:04 by aboudjel         ###   ########.fr       */
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

static void	check_unset_pwd_status(void)
{
	char	*old_pwd;

	if (g_shell.unset_pwd == 1)
	{
		ft_pwd();
		g_shell.temp_old_dir = g_shell.pwd;
		unset("OLDPWD");
		g_shell.unset_pwd = 2;
		return ;
	}
	if (g_shell.unset_pwd == 2)
	{
		ft_export("OLDPWD=");
		old_pwd = g_shell.temp_old_dir;
		read_and_replace_env_cd("OLDPWD", old_pwd);
		g_shell.unset_pwd = 0;
		return ;
	}	
}

static void	test_return_chdir(char *path)
{
	int	return_chdir;

	if (path)
		return_chdir = chdir(path);
	if (!path || return_chdir == -1)
	{
		if (!path || open(path, O_RDONLY) == -1)
		{
			if (path == NULL)
			{
				printf("cd: HOME variable not set\n");
				g_shell.error = 1;
				return ;
			}
			printf("cd: no such file or directory: %s\n", path);
			g_shell.error = 1;
			return ;
		}
		printf("cd: not a directory: %s\n", path);
		g_shell.error = 1;
		return ;
	}	
}

void	ft_chdir(char *path)
{
	char	*tempo;

	if (path == NULL)
		path = get_home_val();
	if (g_shell.unset_pwd != 1 && g_shell.unset_pwd != 2)
	{
		ft_pwd();
		tempo = g_shell.pwd;
	}
	test_return_chdir(path);
	if (g_shell.unset_pwd == 1 || g_shell.unset_pwd == 2)
	{
		check_unset_pwd_status();
		return ;
	}
	ft_pwd();
	read_and_replace_env_cd("PWD", g_shell.pwd);
	read_and_replace_env_cd("OLDPWD", tempo);
}
