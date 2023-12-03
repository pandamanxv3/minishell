/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowerprice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:39:49 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:48:21 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

int	ft_lowerprice(int ch, int cb, int mix1, int mix2)
{
	int	temp;
	int	price;

	temp = ch;
	price = ch;
	if (temp >= cb)
	{
		price = cb;
		temp = cb;
	}
	if (temp >= mix1)
	{
		price = mix1;
		temp = mix1;
	}
	if (temp >= mix2)
		price = mix2;
	return (price);
}
