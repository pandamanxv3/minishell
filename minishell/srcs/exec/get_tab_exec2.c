/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tab_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 06:52:34 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/03 06:55:06 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static char	*findpath(char *cmd, char **splitpath, int i)
{
	int		returnvalue;
	char	*path;

	path = NULL;
	returnvalue = -1;
	while (returnvalue == -1 && splitpath && splitpath[++i])
	{
		path = ft_strjoin(splitpath[i], "/");
		if (!path)
			ft_error("error malloc ft_strjoin");
		path = ft_strjoin_and_replace(path, cmd, 0);
		if (!path)
			ft_error("error malloc ft_strjoin");
		returnvalue = access(path, F_OK);
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
	return (NULL);
}

char	*getpath(char *cmd)
{
	char	*path;
	char	**splitpath;

	path = extractpath();
	splitpath = ft_dispatchsplit(path, ':', g_shell.gc2);
	path = findpath(cmd, splitpath, -1);
	ft_gcadd_back(g_shell.gc2, ft_gcnew(path, g_shell.gc2));
	return (path);
}
