/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redeterminingprice.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:18:52 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:49:47 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_redeterminingprice(t_struct *list)
{
	int	ch;
	int	cb;
	int	mix1;
	int	mix2;

	ft_lengthstacks(list);
	while (list->lst2)
	{
		ch = ft_ch(list, list->lst2->number, list->lst2->pos, 2147483648) + 1;
		cb = ft_cb(list, list->lst2->number, list->lst2->pos, 2147483648) + 1;
		mix1 = ft_mix1(list, list->lst2->number, list->lst2->pos, \
		2147483648) + 1;
		mix2 = ft_mix2(list, list->lst2->number, list->lst2->pos, \
		2147483648) + 1;
		list->lst2->typeofmoove = ft_bestmoove(ch, cb, mix1, mix2);
		list->lst2->price = ft_lowerprice(ch, cb, mix1, mix2);
		if (!(list->lst2->next))
			break ;
		list->lst2 = list->lst2->next;
	}
	while (list->lst2->previous)
		list->lst2 = list->lst2->previous;
}
