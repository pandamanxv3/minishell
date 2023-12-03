/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:04:38 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:19 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_nodeadd_front(t_node **lst, t_node *new)
{
	t_node	*tmp;

	if (!lst || !new)
		return ;
	tmp = (*lst);
	new->next = *lst;
	(*lst)->previous = new;
	while (tmp)
	{
		tmp->pos += 1;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	*lst = new;
}
