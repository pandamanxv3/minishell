/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:23:26 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 16:52:02 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_exitbis4(t_struct *list, int *lis)
{
	ft_nodeclear(&list);
	free(list->tab);
	free(list->actualtab);
	free(list);
	free(lis);
	write(2, "error malloc\n", 13);
	exit(1);
}

void	ft_exitbis3(t_struct *list)
{
	ft_nodeclear(&list);
	free(list->tab);
	free(list->actualtab);
	free(list);
	write(2, "error malloc\n", 13);
	exit(1);
}

void	ft_exitbis2(t_struct *list)
{
	ft_nodeclear(&list);
	free(list->tab);
	free(list);
	write(2, "error malloc\n", 13);
	exit(1);
}

void	ft_exitbis(t_struct *list)
{
	free(list->tab);
	free(list);
	write(2, "error malloc\n", 13);
	exit(1);
}

void	ft_exit(t_struct **list, char **argv)
{
	free((*list)->tab);
	if ((*list)->argv == 1)
		ft_splitfree(argv);
	free((*list));
	write(2, "Error\n", 6);
	exit(1);
}
