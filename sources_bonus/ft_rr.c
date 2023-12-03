/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:41:33 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:19:00 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_rr(t_node **lst, t_node **lst2)
{
	int		tmp;
	t_node	*new;

	tmp = (*lst)->number;
	if (!(*lst)->next)
		return ;
	ft_nodefirstremove(lst);
	new = ft_nodenew(tmp);
	ft_nodeadd_back(lst, new);
	tmp = (*lst2)->number;
	if (!(*lst2)->next)
		return ;
	ft_nodefirstremove(lst2);
	new = ft_nodenew(tmp);
	ft_nodeadd_back(lst2, new);
}
