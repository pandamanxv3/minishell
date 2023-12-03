/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:51:47 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:17:20 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

static void	ft_checkko(t_struct *list)
{
	ft_nodeclear(&list);
	free(list->tab);
	free(list);
	write(1, "KO\n", 3);
	exit(1);
}

void	ft_check(t_struct *list)
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
		free(list);
		write(1, "OK\n", 3);
		exit(1);
	}
	while (tmp->lst->previous)
		tmp->lst = tmp->lst->previous;
	ft_checkko(list);
}
