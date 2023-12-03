/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:55:17 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 16:52:33 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_pushswap.h"

static void	ft_initmain(t_struct *list, char **argv, int argc)
{
	if (argc == 2)
	{
		argv = ft_dispatchsplit(argv[1], list);
		list->tab = malloc(sizeof(int) * list->length);
		if (!list->tab)
		{
			free(list);
			write(2, "error malloc\n", 13);
			exit(1);
		}
		ft_convert(argv, list, 0);
	}
	else
	{
		list->argv = 0;
		list->length = argc - 1;
		list->tab = malloc(sizeof(int) * list->length);
		if (!list->tab)
		{
			free(list);
			write(2, "error malloc\n", 13);
			exit(1);
		}
		ft_convert(argv, list, 1);
	}
}

int	main(int argc, char **argv)
{
	t_struct	*list;

	if (argc == 1)
		exit(1);
	list = malloc(sizeof(t_struct));
	if (!list)
	{
		write(2, "error malloc\n", 13);
		exit(1);
	}
	if (argc == 2)
	{
		list->argv = 1;
		if (!(argv[1][0]))
		{
			free(list);
			exit(1);
		}
		ft_initmain(list, argv, argc);
	}
	if (argc > 2)
		ft_initmain(list, argv, argc);
	ft_dispatch(list);
	return (1);
}
