/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:36:49 by aboudjel          #+#    #+#             */
/*   Updated: 2022/06/06 17:44:06 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	val_strlcpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return ;
}

int	val_strncmp(char *stra, char *val, int length)
{
	int		i;
	char	*str1;
	char	*str2;

	str1 = stra;
	str2 = val;
	i = 0;
	while (length > i && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (!str2[i])
		return (0);
	else
		return (1);
}

int	size_error(void)
{
	int		i;
	int		nb;

	nb = g_shell.error;
	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}
