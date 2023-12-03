/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:45:43 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:50:31 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_sort3(t_struct *list)
{
	if (list->lst->number == 0 && list->lst->next->number == 2)
	{
		ft_mooveandwrite(list, 0);
		ft_mooveandwrite(list, 1);
	}
	if (list->lst->number == 1 && list->lst->next->number == 2)
		ft_mooveandwrite(list, 2);
	if (list->lst->number == 1 && list->lst->next->number == 0)
		ft_mooveandwrite(list, 0);
	if (list->lst->number == 2 && list->lst->next->number == 0)
		ft_mooveandwrite(list, 1);
	if (list->lst->number == 2 && list->lst->next->number == 1)
	{
		ft_mooveandwrite(list, 1);
		ft_mooveandwrite(list, 0);
	}
}
