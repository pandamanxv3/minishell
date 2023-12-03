/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_primesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:59:49 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:06:48 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_primesort(t_struct *list)
{
	t_node	*tmp;
	int		i;

	i = 0;
	ft_lis(list, 0, 0);
	tmp = list->lst;
	while (tmp)
	{
		if (!(ft_isthisfromalis(list->lst->number, list)))
			ft_push_b(&list->lst, &list->lst2, list);
		else if ((ft_isthisfromalis(list->lst->number, list)) \
		&& i < list->lislength)
		{
			ft_rotate(&list->lst, list);
			write(1, "ra\n", 3);
			i++;
		}
		else
			return ;
	}
}
