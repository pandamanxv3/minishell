/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:50:10 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/03 20:48:54 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static void	val_strlcpy(char *dst, char *src, int size)
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

static int	val_strncmp(char *stra, char *val, int length)
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

static int copy_var(char *copy)
{
	int		k;
	t_env	*temp;
	int		j;
	
	g_shell.index_hd++;
	if (g_shell.line[g_shell.index_hd] && (ft_isalpha(g_shell.line[g_shell.index_hd]) == 1 
		|| g_shell.line[g_shell.index_hd] == '_' || g_shell.line[g_shell.index_hd] == '?'))
		j = g_shell.index_hd;
	else
	{
		copy[0] = '$';
		return (1);		
	}
	if (g_shell.line[g_shell.index_hd++] == '?')
		return (itoa_remixed(copy));
	while (g_shell.line[g_shell.index_hd] && (ft_isalnum(g_shell.line[g_shell.index_hd]) == 1 || g_shell.line[g_shell.index_hd] == '_'))
		g_shell.index_hd++;
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((g_shell.line + j), temp->var, (g_shell.index_hd - j));

		if (k == 0)
		{
			k = ft_strlen(temp->val);
			val_strlcpy(copy, temp->val, k);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

int	gestion_var_size(int j, int k)
{
	t_env	*temp;

	g_shell.index_hd++;
	j = g_shell.line[g_shell.index_hd];
	if (g_shell.line[g_shell.index_hd] == '?')
		return (size_error());
	if (ft_isalpha(g_shell.line[g_shell.index_hd]) == 0
		&& g_shell.line[g_shell.index_hd] != '_')
		return (1);
	g_shell.index_hd++;
	//printf(" ft_gestion_var index = %c %d\n", g_shell.line[g_shell.index_hd], g_shell.index_hd);
	while (ft_isalnum(g_shell.line[g_shell.index_hd]) == 1
		|| g_shell.line[g_shell.index_hd] == '_')
		g_shell.index_hd++;
	// printf(" ft_gestion_var index = %d\n", g_shell.index_hd);
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((g_shell.line + j), temp->var, (g_shell.index_hd - j));
		if (k == 0)
		{
			k = ft_strlen(temp->val);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

void	size_expand(void)
{
	int     count;
	char    *str;
	int     i;
	
	count = 0;
	i = 0;
	g_shell.index_hd = 0;
	while(g_shell.line[g_shell.index_hd])
	{
		if (g_shell.line[g_shell.index_hd] == '$')
			count += gestion_var_size(0, 0);
		else
		{
			g_shell.index_hd++;
			count++;
		}
	}
	str = ft_malloc("str", count, "expand malloc failed", g_shell.gc2);
	g_shell.index_hd = 0;
	while (g_shell.line[i])
	{
		if (g_shell.line[i] == '$')
			i += copy_var(str + i);
		else
			str[i++] = g_shell.line[g_shell.index_hd++];
	}
	printf("line %s\n", str);
	// free(g_shell.line);
	g_shell.line = str; 
}
