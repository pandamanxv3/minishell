/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortingch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:24:48 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:07:37 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_sortingch(t_struct *list, t_node *best, int sempaiA)
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
		ft_rr(&list->lst, &list->lst2, list);
	while (list->lst->number != sempaiA)
	{
		ft_rotate(&list->lst, list);
		write(1, "ra\n", 3);
	}
	while (list->lst2->number != best->number)
	{
		ft_rotate(&list->lst2, list);
		write(1, "rb\n", 3);
	}
	ft_push_a(&list->lst, &list->lst2, list);
}
