/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:33:14 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:20:30 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_push_b(t_node **lst, t_node **lst2)
{
	int		tmp;
	t_node	*new;

	if ((*lst)->pos == -1)
		return ;
	tmp = (*lst)->number;
	if ((*lst2)->pos == -1)
	{	
		free((*lst2));
		(*lst2) = ft_nodenew(tmp);
	}
	else
	{
		new = ft_nodenew(tmp);
		ft_nodeadd_front(lst2, new);
	}
	ft_nodefirstremove(lst);
}
