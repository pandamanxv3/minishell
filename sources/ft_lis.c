/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:57:52 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 00:45:50 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_lis(t_struct	*list, int i, int j)
{
	int	*tab2;

	ft_initabforlis(list);
	tab2 = malloc(sizeof(int) * list->length);
	if (!tab2)
		ft_exitbis3(list);
	while (i < list->length)
	{
		tab2[i] = 1;
		i++;
	}
	i = 1;
	while (i < list->length)
	{
		j = 0;
		while (j < i)
		{
			if (tab2[j] >= tab2[i] && list->actualtab[j] < list->actualtab[i])
				tab2[i] = tab2[j] + 1;
			j++;
		}
		i++;
	}
	ft_lististing(tab2, list);
}
