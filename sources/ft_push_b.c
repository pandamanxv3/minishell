/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:33:14 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 17:58:39 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_push_b(t_node **lst, t_node **lst2, t_struct *list)
{
	int		tmp;
	t_node	*new;

	tmp = (*lst)->number;
	if ((*lst2)->pos == -1)
	{	
		free((*lst2));
		(*lst2) = ft_nodenew(tmp, list);
	}
	else
	{
		new = ft_nodenew(tmp, list);
		ft_nodeadd_front(lst2, new);
	}
	ft_nodefirstremove(lst);
	write(1, "pb\n", 3);
}
