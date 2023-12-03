/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortingmix2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:27:21 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 17:59:58 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_sortingmix2(t_struct *list, t_node *best, int sempaiA)
{
	t_node	*tmp;

	tmp = list->lst;
	while (tmp)
	{
		if (tmp->pos == best->sempaipos)
		{
			sempaiA = tmp->number;
			break ;
		}
		tmp = tmp->next;
	}
	while (list->lst->number != sempaiA)
	{
		ft_reverserotate(&list->lst, list);
		write(1, "rra\n", 4);
	}
	while (list->lst2->number != best->number)
	{
		ft_rotate(&list->lst2, list);
		write(1, "rb\n", 3);
	}
	ft_push_a(&list->lst, &list->lst2, list);
}
