/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 02:26:48 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:17:56 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

void	ft_convert(char **argv, t_struct *src, int j)
{
	int			i;
	t_struct	*list;

	list = src;
	i = 0;
	while (argv[j])
	{
		if (!ft_testnum(argv[j]))
			ft_exit(&src, argv);
		list->tab[i] = ft_atoi(argv[j], src, argv);
		i++;
		j++;
	}
	if (!ft_checkdouble(list->tab, list->length))
		ft_exit(&src, argv);
	ft_splitfree(argv);
}
