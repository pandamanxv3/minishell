/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:37:24 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/10 18:42:45 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	ft_pwd(void)
{
	char	*buffer;

	buffer = ft_malloc("str", PATH_MAX + 1,
			"error malloc buffer pwd", g_shell.gc);
	if (!getcwd(buffer, PATH_MAX + 1))
		return ;
	g_shell.pwd = ft_strdup(buffer);
	if (!g_shell.pwd)
		ft_error("error malloc du ft_pwd");
	ft_gcadd_back(g_shell.gc, ft_gcnew(g_shell.pwd, g_shell.gc));
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
