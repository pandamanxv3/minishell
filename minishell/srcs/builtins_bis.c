/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:37:24 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/28 03:36:46 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

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

void	ft_pre_pwd(int i, int j)
{
	int index;
	
	index = j;
	while (index < g_shell.tab_proc[i].nb_tokens)
	{
		if ( g_shell.tab_proc[i].tab_token[index].type == WORD 
		|| g_shell.tab_proc[i].tab_token[index].type == WORD_N)
		{
			if (i == g_shell.nb_proc - 1)
				g_shell.error = 1;
			ft_putstr_fd("pwd: too many arguments\n", 2);
		}
		index++;
	}
	printf("%s\n", ft_pwd());
}

char	*ft_pwd(void)
{
	char	buffer[PATH_MAX + 1];
	char	*str;
	if (getcwd(buffer, PATH_MAX + 1) == NULL)
		return (NULL);
	str = ft_strdup(buffer);
	if (!str)
		ft_error("error malloc du ft_pwd");
	ft_gcadd_back(g_shell.gc2, ft_gcnew(str, g_shell.gc2));
	return (str);
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
void	ft_chdir(char *path)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*tempo;
	int		return_chdir;

	if (path == NULL)
		path = get_home_val();
	if (g_shell.unset_pwd != 1 && g_shell.unset_pwd != 2)
		tempo = ft_pwd(); //current directory
	return_chdir = chdir(path); //j'essaie de changer de directory 
	if (return_chdir == -1)
	{
		printf(" cd: no such file or directory:  %s\n", path);
		g_shell.error = 1;
		return ; //setup echo $? a 1 ss exit(?) perror ou jsais pas quoi
	}
	if (g_shell.unset_pwd == 1) //pwd viet d'etre unset
	{
		g_shell.temp_old_dir = ft_pwd(); //a free a un moment
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
	new_pwd = ft_pwd();
	read_and_replace_envCD("PWD", new_pwd);
	old_pwd = tempo; //j'ai reussi a changer de directory
	read_and_replace_envCD("OLDPWD", old_pwd);
}
