/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:19 by aboudjel          #+#    #+#             */
/*   Updated: 2022/06/08 21:22:10 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	mallocreturn_failed(t_gc *gc, t_gc *gc2, char *msg)
{
	ft_free(gc);
	ft_free(gc2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	*malloc_env(char *errormsg, t_gc *mallocs)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		ft_putstr_fd(errormsg, 2);
		ft_free(mallocs);
		exit(EXIT_FAILURE);
	}
	if (mallocs->data == NULL)
		mallocs->data = env;
	else
		ft_gcadd_back(mallocs, ft_gcnew(env, mallocs));
	return (env);
}
