/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:23:26 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 16:57:52 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_exit(t_struct **list, char **argv)
{
	free((*list)->tab);
	ft_splitfree(argv);
	free((*list));
	write(2, "Error\n", 6);
	exit(1);
}
