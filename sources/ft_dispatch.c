/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:54:23 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 17:56:34 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_dispatch(t_struct *list)
{
	int	i;

	i = 0;
	list->lst2 = ft_lst2init();
	if (!list->lst2)
		ft_exitbis(list);
	list->lst = ft_intochained(list->tab, list->length, 1, list);
	ft_check(list, i);
	if (list->length < 6)
		ft_lessthan5(list);
	else if (list->length > 5)
	{
		ft_morethan5(list);
		i = 1;
	}
	ft_check(list, i);
}
