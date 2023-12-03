/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:58:24 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 17:40:01 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

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
