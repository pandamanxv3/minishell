/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubblesort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:46:40 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:17:16 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_bubblesort(int *src, int argc)
{
	int	i;
	int	j;
	int	tmp;
	int	*tab;

	tab = src;
	j = 1;
	while (j == 1)
	{
		j = 0;
		i = 0;
		while (i < argc)
		{
			if (i != (argc - 1) && tab[i] > tab[i + 1])
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				j = 1;
			}
			i++;
		}
	}
}
