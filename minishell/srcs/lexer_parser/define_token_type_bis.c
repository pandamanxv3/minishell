/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token_type_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:56:09 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/10 18:57:04 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	is_separator(int i, int j)
{
	char	*str;

	str = g_shell.tab_proc[i].tab_token[j].word;
	if ((str[0] == '<' || str[0] == '>') && str[1] == '\0')
	{
		g_shell.tab_proc[i].tab_token[j].type = SEPARATOR;
		if (str[0] == '<')
			return (0);
		if (str[0] == '>')
			return (2);
	}
	if (str[0] == '<' && str[1] == '<')
	{
		g_shell.tab_proc[i].tab_token[j].type = SEPARATOR;
		return (3);
	}
	if (str[0] == '>' && str[1] == '>')
	{
		g_shell.tab_proc[i].tab_token[j].type = SEPARATOR;
		return (4);
	}
	return (1);
}

static int	is_builtin(int i, int j)
{
	char	*str;

	str = g_shell.tab_proc[i].tab_token[j].word;
	if (val_strncmp("pwd", str, 3) == 0)
		return (0);
	if (val_strncmp("echo", str, 4) == 0)
		return (2);
	if (val_strncmp("cd", str, 2) == 0)
		return (0);
	if (val_strncmp("export", str, 6) == 0)
		return (0);
	if (val_strncmp("unset", str, 5) == 0)
		return (0);
	if (val_strncmp("env", str, 3) == 0)
		return (0);
	if (val_strncmp("exit", str, 4) == 0)
		return (0);
	return (1);
}

static void	file_types(int i, int j, int r)
{
	if (r == 0)
		g_shell.tab_proc[i].tab_token[j].type = INFILE;
	if (r == 2)
		g_shell.tab_proc[i].tab_token[j].type = OUTFILE;
	if (r == 3)
		g_shell.tab_proc[i].tab_token[j].type = HEREDOC;
	if (r == 4)
		g_shell.tab_proc[i].tab_token[j].type = OUTFILE_APPEND;
}
