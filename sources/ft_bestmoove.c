/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bestmoove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:41:06 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:47:24 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

int	ft_bestmoove(int ch, int cb, int mix1, int mix2)
{
	int	temp;
	int	typeofmoove;

	temp = ch;
	typeofmoove = 0;
	if (temp >= cb)
	{
		typeofmoove = 1;
		temp = cb;
	}
	if (temp >= mix1)
	{
		typeofmoove = 2;
		temp = mix1;
	}
	if (temp >= mix2)
		typeofmoove = 3;
	return (typeofmoove);
}
