/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:57:34 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:38 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

t_node	*ft_nodenew(int number)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		return (n = NULL);
	n->number = number;
	n->next = NULL;
	n->previous = NULL;
	n->pos = 0;
	return (n);
}
