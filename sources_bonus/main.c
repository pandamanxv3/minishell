/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:55:17 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/19 18:25:19 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

int	main(int argc, char **argv)
{
	t_struct	*list;

	if (argc != 2)
		exit(1);
	else
	{
		list = malloc(sizeof(t_struct));
		if (!list)
		{
			write(1, "error malloc\n", 13);
			exit(1);
		}
		argv = ft_dispatchsplit(argv[1], list);
		list->tab = malloc(sizeof(int) * list->length);
		if (!list->tab)
		{
			free(list);
			write(1, "error malloc\n", 13);
			exit(1);
		}
		ft_convert(argv, list, 0);
	}
	ft_dispatch(list);
	return (1);
}
