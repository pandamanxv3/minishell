/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:58:24 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:18:14 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

t_node	*ft_lst2init(void)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		return (n = NULL);
	n->number = 0;
	n->next = NULL;
	n->previous = NULL;
	n->pos = -1;
	return (n);
}
