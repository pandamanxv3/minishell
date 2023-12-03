/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:02:40 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:29:58 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_nodeclear(t_struct **list)
{
	t_node	*tmp;

	while ((*list)->lst)
	{
		tmp = (*list)->lst;
		(*list)->lst = (*list)->lst->next;
		free(tmp);
	}
	(*list)->lst = NULL;
	while ((*list)->lst2)
	{
		tmp = (*list)->lst2;
		(*list)->lst2 = (*list)->lst2->next;
		free(tmp);
	}
	(*list)->lst2 = NULL;
}
