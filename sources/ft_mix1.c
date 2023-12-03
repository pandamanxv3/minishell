/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:16:02 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:48:31 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

int	ft_mix1(t_struct *list, int a, int posb, long int nbmin)
{
	t_node	*tmp;
	int		posmin;

	tmp = list->lst;
	list->lst2->nb = 2147483648;
	while (tmp)
	{
		if ((a < tmp->number) && (tmp->number < list->lst2->nb))
		{
			list->lst2->sempaipos = tmp->pos;
			list->lst2->nb = tmp->number;
		}
		if (nbmin > tmp->number)
		{
			nbmin = tmp->number;
			posmin = tmp->pos;
		}
		tmp = tmp->next;
	}
	if (list->lst2->nb == 2147483648)
		list->lst2->sempaipos = posmin;
	return (list->lst2->sempaipos + (list->lengthb - posb));
}
