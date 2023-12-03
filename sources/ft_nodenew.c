/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:57:34 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 00:47:19 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

t_node	*ft_nodenew(int number, t_struct *list)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		ft_exitbis2(list);
	n->number = number;
	n->next = NULL;
	n->previous = NULL;
	n->pos = 0;
	return (n);
}
