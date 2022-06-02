/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:37:24 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/02 15:42:31 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


extern t_minishell	g_shell;

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
	char	*buffer;
	char	*str;

	buffer = ft_malloc("str", PATH_MAX + 1, "error malloc buffer pwd", g_shell.gc2);
	getcwd(buffer, PATH_MAX + 1);
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
		g_shell.temp_old_dir = ft_pwd(); //a free a un moment
		unset("OLDPWD");
		g_shell.unset_pwd = 2;
		return ;
	}
	if (g_shell.unset_pwd == 2)
	{
		ft_export("OLDPWD=");
		old_pwd = g_shell.temp_old_dir;
		replace_env("OLDPWD", old_pwd, -5000);
		g_shell.unset_pwd = 0;
		return ;
	}
	new_pwd = ft_pwd();
	//printf("NEW PWD %s\n", new_pwd);
	replace_env("PWD",new_pwd, -5000);
	old_pwd = tempo; //j'ai reussi a changer de directory
	//printf("OLD PWD %s\n", old_pwd);
	replace_env("OLDPWD", old_pwd, -5000);
	printf("NEW PWD %s %d return_chrid %d \n", new_pwd, ft_strlen(new_pwd), return_chdir);
	printf("OLD PWD %s %d\n", old_pwd, ft_strlen(old_pwd));
}