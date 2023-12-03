/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverserotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:39:49 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 16:37:41 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_reverserotate(t_node **lst)
{
	int		tmp;
	t_node	*new;
	t_node	*tmplst;

	if (!((*lst)->next))
		return ;
	tmplst = ft_nodelast(*lst);
	tmp = tmplst->number;
	ft_nodelastremove(lst);
	new = ft_nodenew(tmp);
	ft_nodeadd_front(lst, new);
}
