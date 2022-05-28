/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:52:13 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/28 05:29:05 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

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

int	itoa_remixed(char *dst)
{
	int		length;
	long	nbbis;
	int		i;


	nbbis = g_shell.error;
	length = size_error();
	i = length - 1;
	if (nbbis == 0)
		dst[i] = '0';
	// if (nbbis < 0) SI PAS DERREUR NEGATIF A SUPPRIMER
	// {
	// 	dst[0] = '-';
	// 	nbbis = nbbis * -1;
	// }
	while (nbbis > 0)
	{
		dst[i] = nbbis % 10 + 48;
		nbbis = nbbis / 10;
		i--;
	}
	return (length);
}

int	size_error(void)
{
	int		i;
	int		nb;
	
	nb = g_shell.error;
	i = 0;
	if (nb == 0)
		return (1);
	// if (nb < 0) SI PAS DERREUR NEGATIF A SUPPRIMER
	// { 
	// 	nb = nb * -1;
	// 	i++;
	// }
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	//printf("size_error %d\n", i);
	return (i);
}

int	gestion_var_size(int i, char *str)
{
	int		j;
	int		k;
	t_env	*temp;

	g_shell.tab_proc[i].index++;
	//printf(" ft_gestion_var index = %c %d\n", str[g_shell.tab_proc[i].index], g_shell.tab_proc[i].index);
	j = g_shell.tab_proc[i].index;
	if (str[g_shell.tab_proc[i].index++] == '?')
		return (size_error());
	if (ft_isalpha(str[g_shell.tab_proc[i].index]) == 0
		&& str[g_shell.tab_proc[i].index] != '_')
		return (1);
	g_shell.tab_proc[i].index++;
	//printf(" ft_gestion_var index = %c %d\n", str[g_shell.tab_proc[i].index], g_shell.tab_proc[i].index);
	while (ft_isalnum(str[g_shell.tab_proc[i].index]) == 1
		|| str[g_shell.tab_proc[i].index] == '_')
		g_shell.tab_proc[i].index++;
	// printf(" ft_gestion_var index = %d\n", g_shell.tab_proc[i].index);
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.tab_proc[i].index - j));
		if (k == 0)
		{
			k = ft_strlen(temp->val);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}
