/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:39:12 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:54 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_rotate(t_node **lst)
{
	int		tmp;
	t_node	*new;

	tmp = (*lst)->number;
	if (!(*lst)->next)
		return ;
	ft_nodefirstremove(lst);
	new = ft_nodenew(tmp);
	ft_nodeadd_back(lst, new);
}
