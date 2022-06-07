/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:37:24 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/07 11:44:35 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	ft_pwd(void) // PWD ne marche pas dans un dossier suprimer 2/06/2022
{
	char	*buffer;

	buffer = ft_malloc("str", PATH_MAX + 1, "error malloc buffer pwd", g_shell.gc2);
	if (!getcwd(buffer, PATH_MAX + 1))
		return ;
	g_shell.pwd = ft_strdup(buffer);
	if (!g_shell.pwd)
		ft_error("error malloc du ft_pwd");
	ft_gcadd_back(g_shell.gc, ft_gcnew(g_shell.pwd, g_shell.gc));		
}

static void	read_and_replace_envCD(char *var, char *val)
{
	t_env	*current;

	current = g_shell.lst_env;
	while(current)
	{
		if (val_strncmp(var, current->var, ft_strlen(var)) == 0)
			current->val = val;
		current = current->next;
	}
}

static char	*get_home_val(void)
{
	t_env	*current;
	char	*path;

	current = g_shell.lst_env;
	while(current)
	{
		if (val_strncmp("HOME", current->var, 4) == 0)
			path = current->val;
		current = current->next;
	}
	return (path);
}

void	ft_chdir(char *path) // PWD ne marche pas dans un dossier suprimer 2/06/2022
{
	char	*old_pwd;
	char	*tempo;
	int		return_chdir;

	if (path == NULL)
		path = get_home_val();
	if (g_shell.unset_pwd != 1 && g_shell.unset_pwd != 2)
	{
		ft_pwd(); //current directory
		tempo = g_shell.pwd;
	}
	return_chdir = chdir(path); //j'essaie de changer de directory 
	if (return_chdir == -1)
	{
		if (open(path, O_RDONLY) == -1)
		{
			printf("cd: no such file or directory: %s\n", path);
			g_shell.error = 1;
			return ;
		}
		printf("cd: not a directory: %s\n", path);
		g_shell.error = 1;
		return ; //setup echo $? a 1 ss exit(?) perror ou jsais pas quoi
	}
	if (g_shell.unset_pwd == 1) //pwd vient d'etre unset
	{
		ft_pwd();
		g_shell.temp_old_dir = g_shell.pwd; //a free a un moment
		unset("OLDPWD");
		g_shell.unset_pwd = 2;
		return ;
	}
	if (g_shell.unset_pwd == 2)
	{
		ft_export("OLDPWD=");
		old_pwd = g_shell.temp_old_dir;
		read_and_replace_envCD("OLDPWD", old_pwd);
		g_shell.unset_pwd = 0;
		return ;
	}
	ft_pwd();
	read_and_replace_envCD("PWD", g_shell.pwd);
	read_and_replace_envCD("OLDPWD", tempo);
}