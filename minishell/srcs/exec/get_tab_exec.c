/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tab_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:53:28 by aboudjel          #+#    #+#             */
/*   Updated: 2022/06/03 03:29:38 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static char	*findpath(char *cmd, char **splitpath)
{
	int		returnvalue;
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	returnvalue = -1;
	while (returnvalue == -1 && splitpath && splitpath[i])
	{
		path = ft_strjoin(splitpath[i], "/");
		if (!path)
			ft_error("error malloc ft_strjoin");
		path = ft_strjoin_and_replace(path, cmd, 0);
		if (!path)
			ft_error("error malloc ft_strjoin");
		returnvalue = access(path, F_OK);
		i++;
		if (returnvalue == -1)
		{
			free(path);
			path = NULL;
		}
	}
	if (returnvalue == -1)
		path = ft_strjoin_and_replace(path, cmd, 0);
	if (!path)
		ft_error("error malloc ft_strjoin");
	return (path);
}

static char	*extractpath(void)
{
	t_env	*tmp;

	tmp = g_shell.lst_env;
	while (tmp)
	{
		if (val_strncmp(tmp->var, "PATH", 4) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return(NULL);
}

char	*getpath(char *cmd)
{
	char 	*path;
	char	**splitpath;
	path = extractpath();
	splitpath = ft_dispatchsplit(path, ':', g_shell.gc2);
	path = findpath(cmd, splitpath);
	ft_gcadd_back(g_shell.gc2, ft_gcnew(path,g_shell.gc2));
	return (path);
}

char	**get_envtab(void)
{
	char 	**tab;
	t_env	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = g_shell.lst_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		ft_error("error malloc get_env failed");
	tab[i] = NULL;
	i = 0;
	tmp = g_shell.lst_env;
	while (tmp)
	{
		str = ft_strjoin(tmp->var, "=");
		if (!str)
		{
			free(tab);
			ft_error("error malloc ft_strjoin get_env failed");
		}
		tab[i] = ft_strjoin(str, tmp->val);
		if (!tab[i])
			ft_error("error malloc ft_strjoin 2 get_env failed");
		ft_gcadd_back(g_shell.gc2, ft_gcnew(tab[i],g_shell.gc2));
		free(str);
		i++;
		tmp = tmp->next;
	}
	ft_gcadd_back(g_shell.gc2, ft_gcnew(tab,g_shell.gc2));
	return (tab);
}

char	**get_commandtab(int i)
{
	char	**tab;
	int		count;
	int		j;

	j = 0;
	count = 0;
	while (j < g_shell.tab_proc[i].nb_tokens)
	{
		if (g_shell.tab_proc[i].tab_token[j].type == BUILTIN || g_shell.tab_proc[i].tab_token[j].type == COMMAND
			|| g_shell.tab_proc[i].tab_token[j].type == WORD || g_shell.tab_proc[i].tab_token[j].type == WORD_N)
			count++;
		j++;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		ft_error("malloc get_command failed");
	tab[count] = NULL;
	ft_gcadd_back(g_shell.gc2, ft_gcnew(tab,g_shell.gc2));
	j = 0;
	count = 0;
	while (j < g_shell.tab_proc[i].nb_tokens)
	{
		if (g_shell.tab_proc[i].tab_token[j].type == BUILTIN || g_shell.tab_proc[i].tab_token[j].type == COMMAND
			|| g_shell.tab_proc[i].tab_token[j].type == WORD || g_shell.tab_proc[i].tab_token[j].type == WORD_N)
		{
			tab[count] = g_shell.tab_proc[i].tab_token[j].word;
			count ++;
		}
		j++;
	}
		return (tab);
}