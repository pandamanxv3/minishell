/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:37:24 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/13 16:50:25 by aboudjel         ###   ########.fr       */
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
