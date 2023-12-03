/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lististing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:56:28 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 00:45:05 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_lististing(int *lis, t_struct *list)
{
	int	i;
	int	tempo;

	i = 0;
	tempo = 0;
	while (i < list->length)
	{
		if (lis[i] > tempo)
			tempo = lis[i];
		i++;
	}
	list->lislength = tempo;
	list->lis = malloc(sizeof(int) * tempo);
	if (!list->lis)
		ft_exitbis4(list, lis);
	while (tempo > 0)
	{
		i--;
		if (lis[i] == tempo)
		{
			tempo--;
			list->lis[tempo] = list->actualtab[i];
		}	
	}
	free(lis);
}
