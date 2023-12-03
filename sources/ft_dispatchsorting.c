/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatchsorting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:43:24 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:47:51 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_dispatchsorting(t_struct	*list, int lowestprice)
{
	t_node	*tmp;
	t_node	*tmp2;

	tmp = list->lst2;
	while (tmp)
	{
		if (lowestprice > tmp->price)
		{
			lowestprice = tmp->price;
			tmp2 = tmp;
		}
		if (!(tmp->next))
			break ;
		tmp = tmp->next;
	}
	if (tmp2->typeofmoove == 0)
		ft_sortingch(list, tmp2, -1);
	else if (tmp2->typeofmoove == 1)
		ft_sortingcb(list, tmp2, -1);
	else if (tmp2->typeofmoove == 2)
		ft_sortingmix1(list, tmp2, -1);
	else
		ft_sortingmix2(list, tmp2, -1);
}
