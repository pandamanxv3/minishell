/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:31:05 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 03:42:35 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int	check_unset(int i, char *str)
{
	int	check;

	check = 0;
	if (i == 0 && (ft_isdigit(str[i]) == 1))
	{
		check = 1;
		g_shell.error = 1;
		ft_putstr_fd("unset: `", 2);
		write(2, str, ft_strlen(str));
		ft_putendl_fd("': not a valid identifier", 2);
	}	
	if ((ft_isalnum(str[i]) == 0 && str[i] != '_'))
	{
		check = 1;
		g_shell.error = 127;
		ft_putstr_fd("unset: `", 2);
		write(2, str, ft_strlen(str));
		ft_putendl_fd("': not a valid identifier", 2);
	}
	return (check);
}

static void	unset2(char	*str)
{
	t_env	*temp;

	temp = g_shell.lst_env;
	if (val_strncmp(str, g_shell.lst_env->var, ft_strlen(str)) == 0)
		g_shell.lst_env = g_shell.lst_env->next;
	while (temp->next)
	{
		if (val_strncmp(str, temp->next->var, ft_strlen(str)) == 0)
		{
			temp->next = temp->next->next;
			return ;
		}
		temp = temp->next;
	}
}

void	unset(char *str)
{
	int		i;

	i = 0;
	if (!str[i])
		return ;
	if (!g_shell.lst_env)
		return ;
	if (val_strncmp(str, "PWD", ft_strlen(str)) && g_shell.unset_pwd != -1)
		g_shell.unset_pwd = 1;
	if (val_strncmp(str, "OLDPWD", ft_strlen(str)))
		g_shell.unset_pwd = -1;
	while (str[i])
	{
		if (check_unset(i, str) == 1)
			return ;
		i++;
	}
	unset2(str);
}
