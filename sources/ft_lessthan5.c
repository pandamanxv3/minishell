/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lessthan5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:52:00 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:06:10 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_lessthan5(t_struct *list)
{
	if (list->length == 2)
		ft_mooveandwrite(list, 0);
	if (list->length == 5)
		ft_sort5(list);
	if (list->length == 4 || list->length == 5)
		ft_sort4(list);
	if (list->length > 2)
		ft_sort3(list);
	if (list->length == 5)
	{
		ft_push_a(&list->lst, &list->lst2, list);
		ft_mooveandwrite(list, 1);
	}
	if (list->length == 4 || list->length == 5)
	{
		ft_push_a(&list->lst, &list->lst2, list);
		ft_mooveandwrite(list, 1);
	}
}
