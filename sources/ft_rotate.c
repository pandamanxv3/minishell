/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:39:12 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 17:58:29 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_rotate(t_node **lst, t_struct *list)
{
	int		tmp;
	t_node	*new;

	if (!((*lst)->next))
		return ;
	tmp = (*lst)->number;
	if (!(*lst)->next)
		return ;
	ft_nodefirstremove(lst);
	new = ft_nodenew(tmp, list);
	ft_nodeadd_back(lst, new);
}
