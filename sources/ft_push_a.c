/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:37:27 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 17:58:09 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_push_a(t_node **lst, t_node **lst2, t_struct *list)
{
	int		tmp;
	t_node	*new;

	tmp = (*lst2)->number;
	if ((*lst)->pos == -1)
	{	
		free((*lst));
		(*lst) = ft_nodenew(tmp, list);
	}
	else
	{
		new = ft_nodenew(tmp, list);
		ft_nodeadd_front(lst, new);
	}
	ft_nodefirstremove(lst2);
	write(1, "pa\n", 3);
}
