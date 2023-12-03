/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initabforlis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:57:18 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 00:27:32 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_initabforlis(t_struct *list)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = list->lst;
	list->actualtab = malloc(sizeof(int) * list->length);
	if (!list->actualtab)
		ft_exitbis2(list);
	while (i < list->length)
	{
		list->actualtab[i] = tmp->number;
		i++;
		if (tmp->next)
			tmp = tmp->next;
	}
}
