/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:37:27 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:20:39 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_push_a(t_node **lst, t_node **lst2)
{
	int		tmp;
	t_node	*new;

	if ((*lst2)->pos == -1)
		return ;
	tmp = (*lst2)->number;
	if ((*lst)->pos == -1)
	{	
		free((*lst));
		(*lst) = ft_nodenew(tmp);
	}
	else
	{
		new = ft_nodenew(tmp);
		ft_nodeadd_front(lst, new);
	}
	ft_nodefirstremove(lst2);
}
