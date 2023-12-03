/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:54:23 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 00:10:43 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

static void	ft_error(t_struct *list)
{
	ft_nodeclear(&list);
	free(list->tab);
	free(list);
	write(1, "Error\n", 6);
	exit(1);
}

static void	ft_dispatchchecker2(t_struct *list, char *s)
{
	if (ft_strncmp("rr\n", s, 3) == 0)
	{
		ft_rotate(&list->lst);
		ft_rotate(&list->lst2);
	}
	else if (ft_strncmp("ss\n", s, 3) == 0)
	{
		ft_swap(list->lst);
		ft_swap(list->lst2);
	}
	else
		ft_error(list);
}

void	ft_dispatchchecker(t_struct *list, char *s)
{
	if (ft_strncmp("pa\n", s, 3) == 0)
		ft_push_a(&list->lst, &list->lst2);
	else if (ft_strncmp("pb\n", s, 3) == 0)
		ft_push_b(&list->lst, &list->lst2);
	else if (ft_strncmp("sa\n", s, 3) == 0)
		ft_swap(list->lst);
	else if (ft_strncmp("sb\n", s, 3) == 0)
		ft_swap(list->lst2);
	else if (ft_strncmp("ra\n", s, 3) == 0)
		ft_rotate(&list->lst);
	else if (ft_strncmp("rb\n", s, 3) == 0)
		ft_rotate(&list->lst2);
	else if (ft_strncmp("rra\n", s, 4) == 0)
		ft_reverserotate(&list->lst);
	else if (ft_strncmp("rrb\n", s, 4) == 0)
		ft_reverserotate(&list->lst2);
	else if (ft_strncmp("rrr\n", s, 4) == 0)
	{
		ft_reverserotate(&list->lst);
		ft_reverserotate(&list->lst2);
	}
	else
		ft_dispatchchecker2(list, s);
}

void	ft_dispatch(t_struct *list)
{
	char	*s;

	list->lst2 = ft_lst2init();
	if (!list->lst2)
	{
		free(list->tab);
		free(list);
		write(1, "error malloc\n", 13);
	}
	list->lst = ft_intochained(list->tab, list->length, 1);
	s = get_next_line(0);
	while (s != NULL)
	{
		ft_dispatchchecker(list, s);
		free(s);
		s = get_next_line(0);
	}
	ft_check(list);
}
