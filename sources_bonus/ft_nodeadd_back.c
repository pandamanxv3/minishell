/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:05:02 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:17 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_nodeadd_back(t_node **lst, t_node *new)
{
	t_node	*tmp;

	if (!lst || !new)
		return ;
	tmp = ft_nodelast(*lst);
	tmp->next = new;
	new->previous = tmp;
	new->pos = tmp->pos + 1;
}
