/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:41:33 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:01:27 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_rr(t_node **lst, t_node **lst2, t_struct *list)
{
	int		tmp;
	t_node	*new;

	tmp = (*lst)->number;
	if (!(*lst)->next)
		return ;
	ft_nodefirstremove(lst);
	new = ft_nodenew(tmp, list);
	ft_nodeadd_back(lst, new);
	tmp = (*lst2)->number;
	if (!(*lst2)->next)
		return ;
	ft_nodefirstremove(lst2);
	new = ft_nodenew(tmp, list);
	ft_nodeadd_back(lst2, new);
	write(1, "rr\n", 3);
}
