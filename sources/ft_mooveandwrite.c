/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mooveandwrite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:42:39 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:08:54 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_mooveandwrite(t_struct *list, int index)
{
	if (index == 0)
	{
		ft_swap(list->lst);
		write(1, "sa\n", 3);
	}
	if (index == 1)
	{
		ft_rotate(&list->lst, list);
		write(1, "ra\n", 3);
	}
	if (index == 2)
	{
		ft_reverserotate(&list->lst, list);
		write(1, "rra\n", 4);
	}
}
