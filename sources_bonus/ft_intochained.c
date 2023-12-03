/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intochained.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:48:55 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:11 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

t_node	*ft_intochained(int *tab, int argc, int i)
{
	t_node	*lst;
	t_node	*lst2;
	t_node	*tmp;

	lst = ft_nodenew(tab[0]);
	while (i < argc)
	{
		lst2 = ft_nodenew(tab[i]);
		ft_nodeadd_back(&lst, lst2);
		i++;
	}
	ft_bubblesort(tab, argc);
	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (tab[i] != tmp->number)
			i++;
		tmp->number = i;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (lst);
}
