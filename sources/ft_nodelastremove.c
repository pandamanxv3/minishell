/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodelastremove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:03:59 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:49:04 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_nodelastremove(t_node **lst)
{
	t_node	*tmp;
	t_node	*tmp2;

	tmp = ft_nodelast(*lst);
	tmp2 = tmp->previous;
	free(tmp);
	tmp2->next = NULL;
}
