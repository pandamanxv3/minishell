/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lengthstacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:42:13 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:48:10 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_lengthstacks(t_struct	*list)
{
	t_node	*tmp;
	int		i;
	int		j;

	tmp = list->lst;
	i = 0;
	j = 0;
	while (tmp)
	{
		i++;
		if (!(tmp->next))
			break ;
		tmp = tmp->next;
	}
	tmp = list->lst2;
	while (tmp)
	{
		j++;
		if (!(tmp->next))
			break ;
		tmp = tmp->next;
	}
	list->lengtha = i;
	list->lengthb = j;
}
