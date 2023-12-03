/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_morethan5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:44:26 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:06:20 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_morethan5(t_struct	*list)
{
	ft_primesort(list);
	while (list->lst2->pos != -1)
	{
		ft_redeterminingprice(list);
		ft_dispatchsorting(list, 1500000000);
	}
	while (list->lst->number != 0)
	{
		if (list->lst->number >= list->length / 2)
		{
			ft_rotate(&list->lst, list);
			write(1, "ra\n", 3);
		}
		else
		{
			ft_reverserotate(&list->lst, list);
			write(1, "rra\n", 4);
		}
	}
}
