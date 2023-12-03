/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:51:47 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 17:47:40 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

void	ft_check(t_struct *list, int i)
{
	t_struct	*tmp;

	tmp = list;
	while ((tmp->lst->pos == tmp->lst->number) && tmp->lst->next)
		tmp->lst = tmp->lst->next;
	if (tmp->lst->pos == (tmp->length - 1))
	{
		while (tmp->lst->previous)
			tmp->lst = tmp->lst->previous;
		ft_nodeclear(&list);
		free(list->tab);
		if (i == 1)
		{
			free(list->lis);
			free(list->actualtab);
		}
		free(list);
		exit(1);
	}
	while (tmp->lst->previous)
		tmp->lst = tmp->lst->previous;
}
