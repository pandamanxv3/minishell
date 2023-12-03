/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:42:12 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:58 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_rrr(t_node **lst, t_node **lst2)
{
	int		tmp;
	t_node	*new;
	t_node	*tmplst;

	tmplst = ft_nodelast(*lst);
	tmp = tmplst->number;
	ft_nodelastremove(lst);
	new = ft_nodenew(tmp);
	ft_nodeadd_front(lst, new);
	tmplst = ft_nodelast(*lst2);
	tmp = tmplst->number;
	ft_nodelastremove(lst2);
	new = ft_nodenew(tmp);
	ft_nodeadd_front(lst2, new);
}
