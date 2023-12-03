/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodefirstremove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:03:18 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:26 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_nodefirstremove(t_node **lst)
{
	t_node	*tmp;

	if ((*lst)->next)
		tmp = (*lst)->next;
	else
		tmp = ft_lst2init();
	free((*lst));
	*lst = tmp;
	(*lst)->previous = NULL;
	while (tmp && (tmp->pos != -1))
	{
		tmp->pos -= 1;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}
