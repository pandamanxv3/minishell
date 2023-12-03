/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isthisfromalis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:55:43 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:48:06 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

int	ft_isthisfromalis(int a, t_struct *list)
{
	int	i;

	i = 0;
	while (i < list->lislength)
	{
		if (a == list->lis[i])
			return (1);
		i++;
	}
	return (0);
}
