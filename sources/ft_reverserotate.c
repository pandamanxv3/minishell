/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverserotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:39:49 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 17:58:53 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_reverserotate(t_node **lst, t_struct *list)
{
	int		tmp;
	t_node	*new;
	t_node	*tmplst;

	tmplst = ft_nodelast(*lst);
	tmp = tmplst->number;
	ft_nodelastremove(lst);
	new = ft_nodenew(tmp, list);
	ft_nodeadd_front(lst, new);
}
