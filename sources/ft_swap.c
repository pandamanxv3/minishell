/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:38:02 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 16:35:08 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_swap(t_node *lst)
{
	int		tmp;
	int		tmp2;
	t_node	*nodetmp;

	if (!(lst->next))
		return ;
	nodetmp = lst;
	tmp = lst->number;
	nodetmp = nodetmp->next;
	tmp2 = nodetmp->number;
	nodetmp->number = tmp;
	nodetmp = nodetmp->previous;
	nodetmp->number = tmp2;
}
