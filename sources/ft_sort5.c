/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:50:53 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:00:44 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_sort5(t_struct *list)
{
	int	i;

	i = 0;
	while (list->lst->number != 4)
	{
		i++;
		list->lst = list->lst->next;
	}
	while (list->lst->previous)
		list->lst = list->lst->previous;
	if (i == 1)
		ft_mooveandwrite(list, 0);
	if (i == 2)
	{
		ft_mooveandwrite(list, 1);
		ft_mooveandwrite(list, 0);
	}
	if (i == 3)
	{
		ft_mooveandwrite(list, 2);
		ft_mooveandwrite(list, 2);
	}
	if (i == 4)
		ft_mooveandwrite(list, 2);
	ft_push_b(&list->lst, &list->lst2, list);
}
