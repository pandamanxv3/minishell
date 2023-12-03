/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortingcb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:25:55 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:00:30 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_sortingcb(t_struct *list, t_node *best, int sempaiA)
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
	while (list->lst2->number != best->number && list->lst->number != sempaiA)
		ft_rrr(&list->lst, &list->lst2, list);
	while (list->lst->number != sempaiA)
	{
		ft_reverserotate(&list->lst, list);
		write(1, "rra\n", 4);
	}
	while (list->lst2->number != best->number)
	{
		ft_reverserotate(&list->lst2, list);
		write(1, "rrb\n", 4);
	}
	ft_push_a(&list->lst, &list->lst2, list);
}
